import boto3
import time
import os
from datetime import datetime

current_time = datetime.now().strftime("%Y%m%d%H%M%S")
instance_name = f"ass2-{current_time}"

dir = os.path.dirname(os.path.abspath(__file__))
startup_path = os.path.join(dir, "startup.sh")

region = "ap-south-1"
session = boto3.Session(profile_name="default")
ec2 = session.client("ec2", region_name=region)

with open(startup_path, "r") as file:
    user_data_script = file.read()

# 1. Create or reuse security group
sg_name = "web-sg"

try:
    sg = ec2.create_security_group(GroupName=sg_name, Description="Allow HTTP and SSH")
    sg_id = sg["GroupId"]

    # Add inbound rules: HTTP (80) and SSH (22)
    ec2.authorize_security_group_ingress(
        GroupId=sg_id,
        IpPermissions=[
            {
                "IpProtocol": "tcp",
                "FromPort": 80,
                "ToPort": 80,
                "IpRanges": [{"CidrIp": "0.0.0.0/0"}]  # HTTP open to everyone
            },
            {
                "IpProtocol": "tcp",
                "FromPort": 22,
                "ToPort": 22,
                "IpRanges": [{"CidrIp": "0.0.0.0/0"}]  # SSH open to everyone
            }
        ]
    )
    print(f"Created security group {sg_name} with ID {sg_id}")

except Exception:
    # If it already exists, fetch it
    sg = ec2.describe_security_groups(GroupNames=[sg_name])
    sg_id = sg["SecurityGroups"][0]["GroupId"]
    print(f"Using existing security group {sg_name} ({sg_id})")


# 2. Launch instance (Ubuntu 22.04 LTS AMI in ap-south-1)
ami_id = "ami-03f4878755434977f"
key_pair_name = "test"
response = ec2.run_instances(
    ImageId=ami_id,
    InstanceType="t3.micro",
    MinCount=1,
    MaxCount=1,
    SecurityGroupIds=[sg_id],
    KeyName=key_pair_name,
    UserData=user_data_script,
    TagSpecifications=[
        {
            'ResourceType': 'instance',
            'Tags': [
                {'Key': 'Name', 'Value': instance_name}
            ]
        }
    ]
)

instance_id = response["Instances"][0]["InstanceId"]
print(f"Launching instance {instance_id}...")

# 3. Wait until running and fetch DNS
while True:
    status = ec2.describe_instances(InstanceIds=[instance_id])
    instance = status["Reservations"][0]["Instances"][0]
    state = instance["State"]["Name"]
    if state == "running":
        dns = instance["PublicDnsName"]
        print(f"Instance is running! Access your website at: http://{dns}")
        break
    else:
        print(f"Current state: {state} ... waiting 10s")
        time.sleep(10)