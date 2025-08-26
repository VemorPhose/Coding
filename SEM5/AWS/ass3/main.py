import boto3
import time

REGION = "ap-south-1"
KEY_NAME = "test"
SECURITY_GROUP_ID = "sg-024248abcd7de9683"
IAM_ROLE = "ec2-s3-readonly"

AMI_AMAZON_LINUX = "ami-0861f4e788f5069dd"
AMI_UBUNTU = "ami-02d26659fd82cf299"

INSTANCE_TYPE = "t3.micro"

USER_DATA_HTTPD = """#!/bin/bash
yum update -y
yum install -y httpd
systemctl start httpd
systemctl enable httpd
echo '<h1>Hello from Amazon Linux EC2!</h1>' > /var/www/html/index.html
"""

ec2 = boto3.resource("ec2", region_name=REGION)
ec2_client = boto3.client("ec2", region_name=REGION)

def launch_instances():
    """Launch 1 Amazon Linux + 2 Ubuntu instances."""
    print("Launching instances...")

    instances = ec2.create_instances(
        ImageId=AMI_AMAZON_LINUX,
        InstanceType=INSTANCE_TYPE,
        KeyName=KEY_NAME,
        SecurityGroupIds=[SECURITY_GROUP_ID],
        MinCount=1,
        MaxCount=1,
        UserData=USER_DATA_HTTPD,
        IamInstanceProfile={"Name": IAM_ROLE},
        TagSpecifications=[{
            "ResourceType": "instance",
            "Tags": [{"Key": "Name", "Value": "AmazonLinux-Micro"}]
        }]
    )

    ubuntu_instances = ec2.create_instances(
        ImageId=AMI_UBUNTU,
        InstanceType=INSTANCE_TYPE,
        KeyName=KEY_NAME,
        SecurityGroupIds=[SECURITY_GROUP_ID],
        MinCount=2,
        MaxCount=2,
        IamInstanceProfile={"Name": IAM_ROLE},
        TagSpecifications=[{
            "ResourceType": "instance",
            "Tags": [{"Key": "Name", "Value": "Ubuntu-Micro"}]
        }]
    )

    all_instances = instances + ubuntu_instances
    for inst in all_instances:
        print(f"  - Launched {inst.id}")
    return all_instances


def wait_for_running(instances):
    """Wait for instances to be running."""
    for inst in instances:
        print(f"Waiting for {inst.id} to be running...")
        inst.wait_until_running()
        inst.reload()
        print(f"{inst.id} is running at {inst.public_dns_name}")


def list_running_instances():
    """List all running instances."""
    print("\nRunning instances:")
    for inst in ec2.instances.all():
        if inst.state["Name"] == "running":
            print(f"{inst.id} | {inst.instance_type} | {inst.public_dns_name}")


def check_health(instances):
    """Check instance health status."""
    ids = [i.id for i in instances]
    print("\nChecking health...")
    waiter = ec2_client.get_waiter("instance_status_ok")
    waiter.wait(InstanceIds=ids)
    print("All instances passed status checks")


def stop_instances(instances):
    ids = [i.id for i in instances]
    print("\nStopping instances...")
    ec2_client.stop_instances(InstanceIds=ids)
    waiter = ec2_client.get_waiter("instance_stopped")
    waiter.wait(InstanceIds=ids)
    print("Instances stopped.")


def terminate_instances(instances):
    ids = [i.id for i in instances]
    print("\nTerminating instances...")
    ec2_client.terminate_instances(InstanceIds=ids)
    waiter = ec2_client.get_waiter("instance_terminated")
    waiter.wait(InstanceIds=ids)
    print("Instances terminated.")


if __name__ == "__main__":
    launched = launch_instances()
    wait_for_running(launched)
    list_running_instances()
    check_health(launched)

    print("\nAccess the Amazon Linux web server at:")
    print(f"  http://{launched[0].public_dns_name}")

    time.sleep(60)

    stop_instances(launched)
    terminate_instances(launched)
