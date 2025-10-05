import boto3
import argparse
from botocore.exceptions import ClientError
import time

# --- Configuration ---
AMI_ID = 'ami-0f9708d1cd2cfee41'  # Amazon Linux 2 AMI (ap-south-1)
INSTANCE_TYPE = 't2.micro'
SG_NAME = 'feedback-web-server-sg'
TAG_KEY = 'Name'
TAG_VALUE = 'FeedbackAppServer'

ec2_client = boto3.client('ec2')

def get_or_create_security_group():
    """Checks for a security group by name and creates it if it doesn't exist."""
    try:
        response = ec2_client.describe_security_groups(GroupNames=[SG_NAME])
        sg_id = response['SecurityGroups'][0]['GroupId']
        print(f"Security group '{SG_NAME}' already exists with ID: {sg_id}")
        return sg_id
    except ClientError as e:
        if e.response['Error']['Code'] == 'InvalidGroup.NotFound':
            print(f"Security group '{SG_NAME}' not found. Creating it...")
            sg = ec2_client.create_security_group(
                GroupName=SG_NAME,
                Description='Allows HTTP, SSH, and App traffic for the feedback server',
            )
            sg_id = sg['GroupId']
            ec2_client.authorize_security_group_ingress(
                GroupId=sg_id,
                IpPermissions=[
                    {'IpProtocol': 'tcp', 'FromPort': 22, 'ToPort': 22, 'IpRanges': [{'CidrIp': '0.0.0.0/0'}]},
                    {'IpProtocol': 'tcp', 'FromPort': 80, 'ToPort': 80, 'IpRanges': [{'CidrIp': '0.0.0.0/0'}]},
                    {'IpProtocol': 'tcp', 'FromPort': 8000, 'ToPort': 8000, 'IpRanges': [{'CidrIp': '0.0.0.0/0'}]},
                ]
            )
            print(f"Created security group '{SG_NAME}' with ID: {sg_id}")
            return sg_id
        else:
            raise e

def launch_instance(key_name):
    """Launches the EC2 instance."""
    if not key_name:
        print("Key pair name is required to launch an instance. Use --key-name YOUR_KEY_NAME")
        return

    print("Ensuring security group exists...")
    sg_id = get_or_create_security_group()

    print("Launching EC2 instance...")
    instance = ec2_client.run_instances(
        ImageId=AMI_ID,
        InstanceType=INSTANCE_TYPE,
        KeyName=key_name,
        SecurityGroupIds=[sg_id],
        TagSpecifications=[{'ResourceType': 'instance', 'Tags': [{'Key': TAG_KEY, 'Value': TAG_VALUE}]}],
        MinCount=1,
        MaxCount=1
    )
    instance_id = instance['Instances'][0]['InstanceId']
    print(f"Waiting for instance {instance_id} to enter 'running' state...")
    
    waiter = ec2_client.get_waiter('instance_running')
    waiter.wait(InstanceIds=[instance_id])
    
    # Allow some time for public DNS to be assigned
    time.sleep(5) 
    
    response = ec2_client.describe_instances(InstanceIds=[instance_id])
    public_dns = response['Reservations'][0]['Instances'][0]['PublicDnsName']

    print("\n--- EC2 INSTANCE LAUNCHED ---")
    print(f"Instance ID: {instance_id}")
    print(f"Key Pair: {key_name}")
    print(f"Public DNS: {public_dns}")
    print("---------------------------------")


def cleanup(instance_id):
    """Terminates the EC2 instance and deletes the security group."""
    if not instance_id:
        print("Instance ID is required for cleanup. Use --instance-id i-xxxxxxxxxxxxxxxxx")
        return

    try:
        print(f"Terminating instance {instance_id}...")
        ec2_client.terminate_instances(InstanceIds=[instance_id])
        waiter = ec2_client.get_waiter('instance_terminated')
        waiter.wait(InstanceIds=[instance_id])
        print("Instance terminated.")

        # Give AWS time to detach the SG from the terminated instance's network interface
        print("Waiting for network interfaces to detach before deleting security group...")
        time.sleep(30)

        print(f"Deleting security group '{SG_NAME}'...")
        sg_response = ec2_client.describe_security_groups(GroupNames=[SG_NAME])
        sg_id = sg_response['SecurityGroups'][0]['GroupId']
        ec2_client.delete_security_group(GroupId=sg_id)
        print("Security group deleted.")

    except ClientError as e:
        print(f"Error during cleanup: {e}")

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description="Launch or clean up the EC2 feedback server.")
    parser.add_argument('--cleanup', action='store_true', help="Terminate the instance and delete its resources.")
    parser.add_argument('--instance-id', type=str, help="The ID of the instance to clean up.")
    parser.add_argument('--key-name', type=str, help="The name of the EC2 key pair to use for launching.")
    args = parser.parse_args()

    if args.cleanup:
        cleanup(args.instance_id)
    else:
        launch_instance(args.key_name)

