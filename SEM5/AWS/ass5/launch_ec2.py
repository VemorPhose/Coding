import boto3
import argparse
from botocore.exceptions import ClientError
import time

# --- Configuration ---
REGION_NAME = 'ap-south-1'
AMI_ID = 'ami-0f9708d1cd2cfee41'
INSTANCE_TYPE = 't3.micro'
KEY_NAME = 'test'
SG_NAME = 'feedback-web-server-sg'
TAG_KEY = 'Name'
TAG_VALUE = 'FeedbackAppServer'

ec2_client = boto3.client('ec2', region_name=REGION_NAME)

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

def launch_instance():
    """Launches the EC2 instance."""
    print("Ensuring security group exists...")
    sg_id = get_or_create_security_group()

    print("Launching EC2 instance...")
    instance = ec2_client.run_instances(
        ImageId=AMI_ID,
        InstanceType=INSTANCE_TYPE,
        KeyName=KEY_NAME,
        SecurityGroupIds=[sg_id],
        TagSpecifications=[{'ResourceType': 'instance', 'Tags': [{'Key': TAG_KEY, 'Value': TAG_VALUE}]}],
        MinCount=1,
        MaxCount=1
    )
    instance_id = instance['Instances'][0]['InstanceId']
    print(f"Waiting for instance {instance_id} to enter 'running' state...")
    
    waiter = ec2_client.get_waiter('instance_running')
    waiter.wait(InstanceIds=[instance_id])
    
    time.sleep(5) 
    
    response = ec2_client.describe_instances(InstanceIds=[instance_id])
    public_dns = response['Reservations'][0]['Instances'][0]['PublicDnsName']

    print("\n--- EC2 INSTANCE LAUNCHED ---")
    print(f"Instance ID: {instance_id}")
    print(f"Key Pair: {KEY_NAME}")
    print(f"Public DNS: {public_dns}")
    print("---------------------------------")


def cleanup():
    """Finds all tagged instances, terminates them, and deletes the security group."""
    try:
        # Find instances by tag
        response = ec2_client.describe_instances(
            Filters=[{'Name': f'tag:{TAG_KEY}', 'Values': [TAG_VALUE]}]
        )
        
        instance_ids = []
        for reservation in response['Reservations']:
            for instance in reservation['Instances']:
                # Ensure we only terminate running or pending instances
                if instance['State']['Name'] in ['pending', 'running']:
                    instance_ids.append(instance['InstanceId'])

        if not instance_ids:
            print("No running instances found with the specified tag. Checking for SG to delete...")
        else:
            print(f"Terminating {len(instance_ids)} instance(s): {', '.join(instance_ids)}...")
            ec2_client.terminate_instances(InstanceIds=instance_ids)
            waiter = ec2_client.get_waiter('instance_terminated')
            waiter.wait(InstanceIds=instance_ids)
            print("Instance(s) terminated.")
            print("Waiting for network interfaces to detach before deleting security group...")
            time.sleep(30)

        # Delete the security group regardless of whether instances were found
        print(f"Deleting security group '{SG_NAME}'...")
        sg_response = ec2_client.describe_security_groups(GroupNames=[SG_NAME])
        sg_id = sg_response['SecurityGroups'][0]['GroupId']
        ec2_client.delete_security_group(GroupId=sg_id)
        print("Security group deleted.")

    except ClientError as e:
        if e.response['Error']['Code'] == 'InvalidGroup.NotFound':
             print(f"Security group '{SG_NAME}' not found. Nothing to delete.")
        else:
            print(f"Error during cleanup: {e}")

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description="Launch or clean up the EC2 feedback server.")
    parser.add_argument('--cleanup', action='store_true', help="Terminate all tagged instances and delete resources.")
    args = parser.parse_args()

    if args.cleanup:
        cleanup()
    else:
        launch_instance()

