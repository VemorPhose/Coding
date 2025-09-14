import boto3
import base64
import time
import sys

# --- Configuration ---
AMI_ID = "ami-0861f4e788f5069dd"
INSTANCE_TYPE = "t3.micro"
KEY_NAME = "test"
REGION = "ap-south-1"
IAM_ROLE_NAME = "ec2-s3-readonly"

# --- Resource Naming ---
SG_NAME = "web-server-sg"
LT_NAME = "web-server-lt"
ASG_NAME = "web-server-asg"

def cleanup_resources(ec2_client, asg_client, cw_client):
    """Deletes the created AWS resources to avoid unnecessary costs."""
    print("\n--- Starting Cleanup ---")
    try:
        asg_client.update_auto_scaling_group(
            AutoScalingGroupName=ASG_NAME,
            MinSize=0,
            DesiredCapacity=0
        )
        print("Waiting for instances to terminate...")
        time.sleep(30)
        
        asg_client.delete_auto_scaling_group(
            AutoScalingGroupName=ASG_NAME,
            ForceDelete=True
        )
        print(f"Deleted Auto Scaling Group: {ASG_NAME}")

        print("Confirming Auto Scaling Group deletion...")
        while True:
            try:
                response = asg_client.describe_auto_scaling_groups(AutoScalingGroupNames=[ASG_NAME])
                if not response['AutoScalingGroups']:
                    print("ASG deletion confirmed.")
                    break
                time.sleep(10)
            except asg_client.exceptions.ClientError as e:
                if "does not exist" in str(e) or "not found" in str(e):
                    print("ASG deletion confirmed.")
                    break
                else:
                    raise e
        
    except asg_client.exceptions.ClientError as e:
        if "does not exist" in str(e) or "not found" in str(e):
            print(f"Auto Scaling Group '{ASG_NAME}' not found. Skipping.")
        else:
            print(f"Error deleting ASG: {e}")
            
    try:
        ec2_client.delete_launch_template(LaunchTemplateName=LT_NAME)
        print(f"Deleted Launch Template: {LT_NAME}")
    except ec2_client.exceptions.ClientError as e:
        if "does not exist" in str(e):
            print(f"Launch Template '{LT_NAME}' not found. Skipping.")
        else:
            print(f"Error deleting Launch Template: {e}")

    try:
        ec2_client.delete_security_group(GroupName=SG_NAME)
        print(f"Deleted Security Group: {SG_NAME}")
    except ec2_client.exceptions.ClientError as e:
        if "does not exist" in str(e):
            print(f"Security Group '{SG_NAME}' not found. Skipping.")
        else:
            print(f"Error deleting Security Group: {e}")
            
    try:
        cw_client.delete_alarms(AlarmNames=["cpu-scale-out-alarm", "cpu-scale-in-alarm"])
        print("Deleted CloudWatch Alarms.")
    except cw_client.exceptions.ClientError as e:
        print(f"Error deleting CloudWatch Alarms: {e}")
        
    print("--- Cleanup Complete ---")


def main():
    """Main function to deploy the auto-scaling infrastructure."""
    ec2 = boto3.resource("ec2", region_name=REGION)
    ec2_client = boto3.client("ec2", region_name=REGION)
    asg_client = boto3.client("autoscaling", region_name=REGION)
    cw_client = boto3.client("cloudwatch", region_name=REGION)
    
    cleanup_resources(ec2_client, asg_client, cw_client)
    print("\n--- Starting Deployment ---\n")

    # 1. Create Security Group
    try:
        sg = ec2.create_security_group(
            GroupName=SG_NAME,
            Description="Allow HTTP traffic"
        )
        sg.authorize_ingress(
            IpPermissions=[{
                "IpProtocol": "tcp",
                "FromPort": 80,
                "ToPort": 80,
                "IpRanges": [{"CidrIp": "0.0.0.0/0"}]
            }]
        )
        print(f"Created Security Group: {sg.id}")
    except ec2_client.exceptions.ClientError as e:
        if "already exists" in str(e):
            sg_response = ec2_client.describe_security_groups(GroupNames=[SG_NAME])
            sg_id = sg_response['SecurityGroups'][0]['GroupId']
            sg = ec2.SecurityGroup(sg_id)
            print(f"Using existing Security Group: {sg.id}")
        else:
            raise e

    # 2. Define User Data Script and Create Launch Template
    user_data_script = """#!/bin/bash
yum update -y
yum install -y httpd aws-cli
systemctl start httpd
systemctl enable httpd
aws s3 cp s3://ungabunga69/ass2/ /var/www/html/ --recursive
INSTANCE_ID=$(curl -s http://169.254.169.254/latest/meta-data/instance-id)
INDEX_FILE="/var/www/html/index.html"
sed -i "s//${INSTANCE_ID}/g" $INDEX_FILE
"""
    
    user_data_b64 = base64.b64encode(user_data_script.encode("utf-8")).decode("utf-8")
    
    lt = ec2_client.create_launch_template(
        LaunchTemplateName=LT_NAME,
        LaunchTemplateData={
            "ImageId": AMI_ID,
            "InstanceType": INSTANCE_TYPE,
            "KeyName": KEY_NAME,
            "SecurityGroupIds": [sg.id],
            "IamInstanceProfile": {"Name": IAM_ROLE_NAME},
            "UserData": user_data_b64
        }
    )
    lt_id = lt["LaunchTemplate"]["LaunchTemplateId"]
    print(f"Created Launch Template: {lt_id}")

    # 3. Create Auto Scaling Group
    availability_zones = [f"{REGION}a", f"{REGION}b", f"{REGION}c"]
    asg_client.create_auto_scaling_group(
        AutoScalingGroupName=ASG_NAME,
        LaunchTemplate={"LaunchTemplateId": lt_id},
        MinSize=1,
        MaxSize=3,
        DesiredCapacity=1,
        AvailabilityZones=availability_zones
    )
    print(f"Created Auto Scaling Group: {ASG_NAME}")

    # 4. Create Scaling Policies
    scale_out_policy = asg_client.put_scaling_policy(
        AutoScalingGroupName=ASG_NAME,
        PolicyName="scale-out-policy",
        PolicyType="SimpleScaling",
        AdjustmentType="ChangeInCapacity",
        ScalingAdjustment=1,
        Cooldown=120
    )
    
    scale_in_policy = asg_client.put_scaling_policy(
        AutoScalingGroupName=ASG_NAME,
        PolicyName="scale-in-policy",
        PolicyType="SimpleScaling",
        AdjustmentType="ChangeInCapacity",
        ScalingAdjustment=-1,
        Cooldown=240
    )
    print("Created Scaling Policies.")
    
    # 5. Create CloudWatch Alarms
    cw_client.put_metric_alarm(
        AlarmName="cpu-scale-out-alarm",
        MetricName="CPUUtilization",
        Namespace="AWS/EC2",
        Statistic="Average",
        Period=60,
        EvaluationPeriods=2,
        Threshold=20.0,
        ComparisonOperator="GreaterThanOrEqualToThreshold",
        AlarmActions=[scale_out_policy["PolicyARN"]],
        Dimensions=[{"Name": "AutoScalingGroupName", "Value": ASG_NAME}],
    )

    cw_client.put_metric_alarm(
        AlarmName="cpu-scale-in-alarm",
        MetricName="CPUUtilization",
        Namespace="AWS/EC2",
        Statistic="Average",
        Period=60,
        EvaluationPeriods=4,
        Threshold=10.0,
        ComparisonOperator="LessThanOrEqualToThreshold",
        AlarmActions=[scale_in_policy["PolicyARN"]],
        Dimensions=[{"Name": "AutoScalingGroupName", "Value": ASG_NAME}],
    )
    print("Created CloudWatch Alarms.")
    
    # --- VERIFICATION STEP ---
    print("\n--- Deployment Complete ---")
    print("Waiting for instance to be provisioned by the Auto Scaling Group...")
    
    instance_id = None
    while not instance_id:
        response = asg_client.describe_auto_scaling_groups(AutoScalingGroupNames=[ASG_NAME])
        if response['AutoScalingGroups']:
            instances = response['AutoScalingGroups'][0]['Instances']
            if instances:
                instance_id = instances[0]['InstanceId']
        time.sleep(10)

    print(f"Instance {instance_id} is being created. Waiting for it to pass status checks...")
    print("(This will take a minute or two...)")

    # WAITER
    waiter = ec2_client.get_waiter('instance_status_ok')
    waiter.wait(InstanceIds=[instance_id])
    
    print("Instance passed status checks! The web server should now be ready.")

    # Public DNS
    instance_description = ec2_client.describe_instances(InstanceIds=[instance_id])
    public_dns = instance_description['Reservations'][0]['Instances'][0]['PublicDnsName']
    
    print("\n--- Verification Info ---")
    print(f"Instance ID: {instance_id}")
    print(f"Public DNS Name: http://{public_dns}")
    print("\nTest your website by opening the Public DNS link in a browser. It should now be accessible.")


if __name__ == "__main__":
    if len(sys.argv) > 1 and sys.argv[1] == 'cleanup':
        ec2_c = boto3.client("ec2", region_name=REGION)
        asg_c = boto3.client("autoscaling", region_name=REGION)
        cw_c = boto3.client("cloudwatch", region_name=REGION)
        cleanup_resources(ec2_c, asg_c, cw_c)
    else:
        main()