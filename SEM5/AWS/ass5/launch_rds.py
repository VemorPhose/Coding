import boto3
import argparse
import getpass
from botocore.exceptions import ClientError
import time

# --- Configuration ---
REGION_NAME = 'ap-south-1'
DB_INSTANCE_IDENTIFIER_BASE = 'feedback-db'
DB_INSTANCE_CLASS = 'db.t3.micro'
MASTER_USERNAME = 'admin'
RDS_SG_NAME = 'feedback-rds-sg'
WEB_SG_NAME = 'feedback-web-server-sg' # Must match the name in launch_ec2.py

rds_client = boto3.client('rds', region_name=REGION_NAME)
ec2_client = boto3.client('ec2', region_name=REGION_NAME)

def get_or_create_rds_sg():
    """Creates the RDS security group if it doesn't exist."""
    try:
        response = ec2_client.describe_security_groups(GroupNames=[RDS_SG_NAME])
        sg_id = response['SecurityGroups'][0]['GroupId']
        print(f"RDS Security group '{RDS_SG_NAME}' already exists: {sg_id}")
        return sg_id
    except ClientError as e:
        if e.response['Error']['Code'] == 'InvalidGroup.NotFound':
            print(f"RDS Security group '{RDS_SG_NAME}' not found. Creating...")
            sg = ec2_client.create_security_group(
                GroupName=RDS_SG_NAME,
                Description='Allows MySQL access from the web server SG'
            )
            sg_id = sg['GroupId']
            print(f"Created RDS security group '{RDS_SG_NAME}': {sg_id}")
            return sg_id
        else:
            raise e

def create_rds_instance():
    """Creates the RDS instance and configures security."""
    db_password = getpass.getpass("Enter a strong password for the DB master user: ")
    if not db_password:
        print("DB password cannot be empty.")
        return

    # 1. Ensure RDS security group exists
    rds_sg_id = get_or_create_rds_sg()

    # 2. Get the Web Server security group ID to create the rule
    try:
        web_sg_response = ec2_client.describe_security_groups(GroupNames=[WEB_SG_NAME])
        web_sg_id = web_sg_response['SecurityGroups'][0]['GroupId']
        print(f"Found web server SG '{WEB_SG_NAME}' with ID: {web_sg_id}")
    except ClientError:
        print(f"Critical Error: Web server security group '{WEB_SG_NAME}' not found.")
        print("Please run the `launch_ec2.py` script first.")
        return

    # 3. Create RDS Instance
    db_identifier = f"{DB_INSTANCE_IDENTIFIER_BASE}-{int(time.time())}"
    print(f"Creating RDS instance: {db_identifier}...")
    rds_client.create_db_instance(
        DBInstanceIdentifier=db_identifier,
        DBName='feedbackdb',
        AllocatedStorage=20,
        DBInstanceClass=DB_INSTANCE_CLASS,
        Engine='mysql',
        MasterUsername=MASTER_USERNAME,
        MasterUserPassword=db_password,
        VpcSecurityGroupIds=[rds_sg_id]
    )
    print("Waiting for instance to become available (this takes ~10 minutes)...")
    waiter = rds_client.get_waiter('db_instance_available')
    waiter.wait(DBInstanceIdentifier=db_identifier)
    print("RDS instance is available!")

    # 4. Authorize traffic from the web server security group
    print(f"Authorizing access from '{WEB_SG_NAME}' to '{RDS_SG_NAME}'...")
    try:
        ec2_client.authorize_security_group_ingress(
            GroupId=rds_sg_id,
            IpPermissions=[{
                'IpProtocol': 'tcp', 'FromPort': 3306, 'ToPort': 3306,
                'UserIdGroupPairs': [{'GroupId': web_sg_id}]
            }]
        )
        print("Security group rule added successfully.")
    except ClientError as e:
        if "InvalidPermission.Duplicate" in str(e):
            print("Ingress rule already exists.")
        else:
            raise e
            
    instance_details = rds_client.describe_db_instances(DBInstanceIdentifier=db_identifier)['DBInstances'][0]
    endpoint = instance_details['Endpoint']['Address']

    print("\n--- RDS INSTANCE CREATED ---")
    print(f"DB Identifier: {db_identifier}")
    print(f"Endpoint: {endpoint}")
    print("---------------------------------")

def cleanup_rds(db_identifier):
    """Deletes the RDS instance and its security group."""
    if not db_identifier:
        print("DB Identifier is required for cleanup. Use --db-identifier <name>")
        return
        
    try:
        print(f"Deleting RDS instance {db_identifier}...")
        rds_client.delete_db_instance(DBInstanceIdentifier=db_identifier, SkipFinalSnapshot=True)
        waiter = rds_client.get_waiter('db_instance_deleted')
        waiter.wait(DBInstanceIdentifier=db_identifier)
        print("RDS instance deleted.")

        print(f"Deleting security group '{RDS_SG_NAME}'...")
        sg_response = ec2_client.describe_security_groups(GroupNames=[RDS_SG_NAME])
        sg_id = sg_response['SecurityGroups'][0]['GroupId']
        ec2_client.delete_security_group(GroupId=sg_id)
        print("RDS Security group deleted.")
    except ClientError as e:
        print(f"Error during cleanup: {e}")

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description="Create or clean up the RDS database.")
    parser.add_argument('--cleanup', action='store_true', help="Delete the RDS instance and its SG.")
    parser.add_argument('--db-identifier', type=str, help="The identifier of the DB instance to clean up.")
    args = parser.parse_args()

    if args.cleanup:
        cleanup_rds(args.db_identifier)
    else:
        create_rds_instance()

# DB Identifier: feedback-db-1759684949
# Endpoint: feedback-db-1759684949.cpswsa0444dm.ap-south-1.rds.amazonaws.com
# EC2 Public DNS: ec2-65-0-139-8.ap-south-1.compute.amazonaws.com