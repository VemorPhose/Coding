import boto3
import time

AMI_ID = "ami-0861f4e788f5069dd"
INSTANCE_TYPE = "t3.micro"
KEY_NAME = "test"                    
SECURITY_GROUP_ID = "sg-024248abcd7de9683"
REGION = "ap-south-1"
IAM_ROLE = "ec2-s3-readonly"                      

USER_DATA = """#!/bin/bash
yum update -y
yum install -y httpd awscli
systemctl start httpd
systemctl enable httpd
aws s3 cp s3://ungabunga69/ass2/ /var/www/html/ --recursive
"""

def main():
    ec2 = boto3.resource("ec2", region_name=REGION)

    print("Launching EC2 instance...")
    instances = ec2.create_instances(
        ImageId=AMI_ID,
        InstanceType=INSTANCE_TYPE,
        KeyName=KEY_NAME,
        SecurityGroupIds=[SECURITY_GROUP_ID],
        MinCount=1,
        MaxCount=1,
        UserData=USER_DATA,
        IamInstanceProfile={"Name": IAM_ROLE}
    )

    instance = instances[0]
    print("Waiting for instance to be running...")
    instance.wait_until_running()
    instance.load()

    print("Waiting for status checks to pass...")
    waiter = boto3.client("ec2", region_name=REGION).get_waiter("instance_status_ok")
    waiter.wait(InstanceIds=[instance.id])

    print("Instance passed status checks.")
    print(f"Public DNS: http://{instance.public_dns_name}")

if __name__ == "__main__":
    main()