import os
import time
import json
import zipfile
import boto3
import botocore

# ====== Configuration ======
AWS_REGION = "ap-south-1"
APP_NAME = "MyApp"
ENV_NAME = "myapp-env"
VERSION_LABEL = "v1"
S3_BUCKET = "ungabunga69"
ZIP_FILE = "myapp_v1.zip"
WEBAPP_DIR = "webapp"

ROLE_NAME = "NewRole"
SERVICE_ROLE = "aws-elasticbeanstalk-service-role"
EC2_KEY_PAIR = "test"
PLATFORM_BRANCH = "Python 3.12 running on 64bit Amazon Linux 2023"
PLATFORM_VERSION = "4.2.0"

INSTANCE_TYPE = "t3.micro"
AZ = "ap-south-1a"
# ============================

session = boto3.Session(region_name=AWS_REGION)
iam = session.client("iam")
s3 = session.client("s3")
eb = session.client("elasticbeanstalk")
ec2 = session.client("ec2")

def zip_webapp():
    if not os.path.isdir(WEBAPP_DIR):
        raise RuntimeError(f"Directory '{WEBAPP_DIR}' not found.")
    with zipfile.ZipFile(ZIP_FILE, "w", zipfile.ZIP_DEFLATED) as zf:
        for root, dirs, files in os.walk(WEBAPP_DIR):
            for fname in files:
                full = os.path.join(root, fname)
                rel = os.path.relpath(full, WEBAPP_DIR)
                zf.write(full, rel)
    print(f"Created zip: {ZIP_FILE}")

def ensure_iam_role():
    assume_policy = {
        "Version": "2012-10-17",
        "Statement": [
            {
                "Effect": "Allow",
                "Principal": {"Service": "ec2.amazonaws.com"},
                "Action": "sts:AssumeRole"
            }
        ]
    }
    # Create Role if not exists
    try:
        iam.get_role(RoleName=ROLE_NAME)
        print(f"IAM role {ROLE_NAME} exists.")
    except iam.exceptions.NoSuchEntityException:
        print(f"Creating IAM role {ROLE_NAME} …")
        iam.create_role(
            RoleName=ROLE_NAME,
            AssumeRolePolicyDocument=json.dumps(assume_policy),
            Description="Role for EB EC2 instance"
        )
    # Attach AWSElasticBeanstalkWebTier policy
    policy_arn = "arn:aws:iam::aws:policy/AWSElasticBeanstalkWebTier"
    attached = iam.list_attached_role_policies(RoleName=ROLE_NAME)["AttachedPolicies"]
    if not any(p["PolicyArn"] == policy_arn for p in attached):
        print("Attaching AWSElasticBeanstalkWebTier policy")
        iam.attach_role_policy(RoleName=ROLE_NAME, PolicyArn=policy_arn)
    # Instance profile
    profile_name = ROLE_NAME
    try:
        iam.get_instance_profile(InstanceProfileName=profile_name)
        print("Instance profile exists.")
    except iam.exceptions.NoSuchEntityException:
        print("Creating instance profile …")
        iam.create_instance_profile(InstanceProfileName=profile_name)
        # slight wait for consistency
        time.sleep(2)
    # Add role to profile
    prof = iam.get_instance_profile(InstanceProfileName=profile_name)
    roles = [r["RoleName"] for r in prof["InstanceProfile"].get("Roles", [])]
    if ROLE_NAME not in roles:
        iam.add_role_to_instance_profile(InstanceProfileName=profile_name, RoleName=ROLE_NAME)
        print("Role added to instance profile.")
    else:
        print("Role already in instance profile.")
    return profile_name

def upload_to_s3():
    print(f"Uploading {ZIP_FILE} to s3://{S3_BUCKET}/{ZIP_FILE}")
    s3.upload_file(ZIP_FILE, S3_BUCKET, ZIP_FILE)
    print("Upload done.")

def find_platform_arn():
    paginator = eb.get_paginator("list_platform_versions")
    for page in paginator.paginate(Filters=[{"Type": "PlatformBranchName", "Operator": "=", "Values": [PLATFORM_BRANCH]}]):
        for p in page.get("PlatformSummaryList", []):
            if p.get("PlatformVersion") == PLATFORM_VERSION:
                print("Found platform ARN:", p["PlatformArn"])
                return p["PlatformArn"]
    # fallback: first matching branch
    for page in eb.get_paginator("list_platform_versions").paginate():
        for p in page.get("PlatformSummaryList", []):
            if PLATFORM_BRANCH in p.get("PlatformBranchName", ""):
                print("Fallback platform ARN:", p["PlatformArn"])
                return p["PlatformArn"]
    raise RuntimeError("Platform ARN not found.")

def get_vpc_and_subnet():
    vpcs = ec2.describe_vpcs(Filters=[{"Name": "isDefault", "Values": ["true"]}])["Vpcs"]
    if not vpcs:
        raise RuntimeError("No default VPC.")
    vpc_id = vpcs[0]["VpcId"]
    subnets = ec2.describe_subnets(
        Filters=[{"Name": "vpc-id", "Values": [vpc_id]}, {"Name": "availability-zone", "Values": [AZ]}]
    )["Subnets"]
    if not subnets:
        # fallback any subnet in that VPC
        subnets = ec2.describe_subnets(Filters=[{"Name": "vpc-id", "Values": [vpc_id]}])["Subnets"]
    subnet_id = subnets[0]["SubnetId"]
    return vpc_id, subnet_id

def create_application_version():
    print("Ensuring EB application exists …")
    apps = eb.describe_applications(ApplicationNames=[APP_NAME])["Applications"]
    if not apps:
        eb.create_application(ApplicationName=APP_NAME, Description="App for static site")
        print("Application created.")
    else:
        print("Application already exists.")
    print("Creating application version …")
    eb.create_application_version(
        ApplicationName=APP_NAME,
        VersionLabel=VERSION_LABEL,
        SourceBundle={"S3Bucket": S3_BUCKET, "S3Key": ZIP_FILE},
        Process=True
    )
    print("Version created.")

def create_environment(instance_profile_name):
    platform_arn = find_platform_arn()
    vpc_id, subnet_id = get_vpc_and_subnet()

    # Generate unique CNAME prefix
    suffix = time.strftime("%Y%m%d%H%M%S")
    cname = f"{APP_NAME.lower()}-{suffix}"

    option_settings = [
        # Instance launch config
        {"Namespace": "aws:autoscaling:launchconfiguration", "OptionName": "InstanceType", "Value": INSTANCE_TYPE},
        {"Namespace": "aws:autoscaling:launchconfiguration", "OptionName": "IamInstanceProfile", "Value": instance_profile_name},
        {"Namespace": "aws:autoscaling:launchconfiguration", "OptionName": "EC2KeyName", "Value": EC2_KEY_PAIR},
        # disable IMDSv1 (force IMDSv2)
        {"Namespace": "aws:autoscaling:launchconfiguration", "OptionName": "DisableIMDSv1", "Value": "true"},
        # environment type
        {"Namespace": "aws:elasticbeanstalk:environment", "OptionName": "EnvironmentType", "Value": "SingleInstance"},
        # autoscaling settings
        {"Namespace": "aws:autoscaling:asg", "OptionName": "MinSize", "Value": "1"},
        {"Namespace": "aws:autoscaling:asg", "OptionName": "MaxSize", "Value": "1"},
        # proxy server
        {"Namespace": "aws:elasticbeanstalk:environment:proxy", "OptionName": "ProxyServer", "Value": "nginx"},
        # VPC / subnet
        {"Namespace": "aws:ec2:vpc", "OptionName": "VPCId", "Value": vpc_id},
        {"Namespace": "aws:ec2:vpc", "OptionName": "Subnets", "Value": subnet_id},
        # health reporting
        {"Namespace": "aws:elasticbeanstalk:healthreporting:system", "OptionName": "SystemType", "Value": "basic"},
    ]

    print("Creating environment … this will take some time.")
    resp = eb.create_environment(
        ApplicationName=APP_NAME,
        EnvironmentName=ENV_NAME,
        PlatformArn=platform_arn,
        VersionLabel=VERSION_LABEL,
        CNAMEPrefix=cname,
        OptionSettings=option_settings,
        ServiceRole=SERVICE_ROLE
    )
    print("Environment creation invoked:", resp.get("EnvironmentId"))

def wait_until_ready(timeout_min=20):
    deadline = time.time() + timeout_min * 60
    while time.time() < deadline:
        resp = eb.describe_environments(ApplicationName=APP_NAME, EnvironmentNames=[ENV_NAME])
        envs = resp.get("Environments", [])
        if envs:
            e = envs[0]
            print("Status:", e.get("Status"), "Health:", e.get("Health"), "CNAME:", e.get("CNAME"))
            if e.get("Status") == "Ready":
                print("Environment ready at:", e.get("CNAME"))
                return e
        time.sleep(15)
    raise TimeoutError("Environment did not become ready in time.")

def cleanup():
    try:
        eb.terminate_environment(EnvironmentName=ENV_NAME, TerminateResources=True)
        print("Termination requested.")
    except Exception as e:
        print("Error terminating:", e)
    try:
        eb.delete_application(ApplicationName=APP_NAME, TerminateEnvByForce=True)
        print("Delete application requested.")
    except Exception as e:
        print("Error deleting application:", e)
    try:
        s3.delete_object(Bucket=S3_BUCKET, Key=ZIP_FILE)
        print("Deleted S3 object.")
    except Exception as e:
        print("Error deleting S3:", e)

def main():
    zip_webapp()
    ensure_iam_role()
    upload_to_s3()
    create_application_version()
    instance_profile = ROLE_NAME  # same name
    create_environment(instance_profile)
    wait_until_ready()
    print("Deployment finished successfully.")

if __name__ == "__main__":
    main()
