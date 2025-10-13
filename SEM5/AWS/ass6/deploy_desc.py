import boto3
import sys
import os
import zipfile
import time
from io import BytesIO

# --- Configuration Constants ---
REGION_NAME = 'ap-south-1' 
KEY_PAIR_NAME = 'test'
# S3_BUCKET_NAME is only informational, as S3 setup is manual.
S3_BUCKET_NAME = 'ungabunga69'

# --- HARDCODED EXISTING ROLES (Simplified setup) ---
# 1. Instance Profile Role (used by the EC2 instance for permissions)
IAM_ROLE_NAME = 'elastic-beanstalk-webtier'
# 2. Service Role (used by Elastic Beanstalk to manage resources)
EB_SERVICE_ROLE = 'elastic-beanstalk-environment'

EB_APP_NAME = 'MyApp'
EB_ENV_NAME = f'{EB_APP_NAME}-env'
EB_VERSION_LABEL = 'v1'
EB_PLATFORM = 'arn:aws:elasticbeanstalk:ap-south-1::platform/Python 3.12 running on 64bit Amazon Linux 2023/4.2.0'
EB_INSTANCE_TYPE = 't3.micro'

# --- Clients ---
s3_client = boto3.client('s3', region_name=REGION_NAME)
ec2_client = boto3.client('ec2', region_name=REGION_NAME)
eb_client = boto3.client('elasticbeanstalk', region_name=REGION_NAME)

def create_eb_zip_package(zip_filename='application.zip'):
    """
    Creates a temporary ZIP file containing a minimal Flask application
    required for Elastic Beanstalk deployment.
    """
    print(f"Creating Elastic Beanstalk deployment package: {zip_filename}...")
    
    # 1. application.py (minimal Flask app)
    app_code = """
from flask import Flask
application = Flask(__name__)

@application.route('/')
def index():
    # Placeholder for the user's personal website application logic
    return '<h1>Hello from Elastic Beanstalk Deployment!</h1><p>This is your Python (Flask) personal website hosted on AWS.</p>'

if __name__ == '__main__':
    application.run(debug=True)
"""
    # 2. requirements.txt
    requirements = "Flask\n"

    try:
        with zipfile.ZipFile(zip_filename, 'w', zipfile.ZIP_DEFLATED) as zf:
            zf.writestr('application.py', app_code)
            zf.writestr('requirements.txt', requirements)
        print(f"Successfully created {zip_filename}.")
        return zip_filename
    except Exception as e:
        print(f"Error creating deployment package: {e}")
        return None

def wait_for_eb_update(environment_name, desired_status='Ready', timeout=900):
    """Waits for an Elastic Beanstalk environment to reach a desired status."""
    print(f"Waiting for environment {environment_name} to reach status '{desired_status}'...")
    start_time = time.time()
    while time.time() - start_time < timeout:
        try:
            response = eb_client.describe_environments(
                EnvironmentNames=[environment_name]
            )
            env = response['Environments'][0]
            status = env['Status']
            health = env['Health']
            
            print(f"  Current Status: {status}, Health: {health}")

            if status == desired_status and health in ['Green', 'Grey']:
                print(f"Environment reached desired status: {desired_status}")
                return True
            
            if status in ['Terminated', 'Failed', 'Timeout']:
                print(f"Environment reached terminal status: {status}")
                return False

        except Exception as e:
            # Handle case where environment might not exist during cleanup
            if 'Environment not found' in str(e):
                return True 

        time.sleep(30)
    print(f"Timeout while waiting for environment {environment_name} to become {desired_status}.")
    return False

def deploy_eb_website():
    """
    Performs the Elastic Beanstalk application deployment.
    Assumes S3 bucket ('ungabunga69') and IAM roles ('elastic-beanstalk-environment', 'elastic-beanstalk-webtier')
    are pre-configured.
    """

    # 1. Create Deployment Package (ZIP file)
    zip_file = create_eb_zip_package()
    if not zip_file:
        print("Failed to create deployment package. Exiting.")
        return

    print(f"\n--- Elastic Beanstalk Deployment for '{EB_APP_NAME}' ---")

    try:
        # Create application if it doesn't exist
        try:
            eb_client.create_application(ApplicationName=EB_APP_NAME)
            print(f"Application '{EB_APP_NAME}' created.")
        except eb_client.exceptions.ApplicationAlreadyExistsException:
            print(f"Application '{EB_APP_NAME}' already exists. Reusing.")

        # Upload the ZIP file to the default EB S3 storage bucket
        # This storage bucket is automatically created and used by EB for versions
        default_bucket_name = eb_client.create_storage_location()['S3Bucket']
        s3_client.upload_file(zip_file, default_bucket_name, f'{EB_APP_NAME}/{zip_file}')
        print(f"Deployment package uploaded to EB's default S3 bucket '{default_bucket_name}'.")

        # Create Application Version
        eb_client.create_application_version(
            ApplicationName=EB_APP_NAME,
            VersionLabel=EB_VERSION_LABEL,
            SourceBundle={
                'S3Bucket': default_bucket_name,
                'S3Key': f'{EB_APP_NAME}/{zip_file}'
            }
        )
        print(f"Application Version '{EB_VERSION_LABEL}' created.")

        # --- Configure Environment Options ---
        option_settings = [
            {'Namespace': 'aws:autoscaling:launchconfiguration',
             'OptionName': 'InstanceType', 'Value': EB_INSTANCE_TYPE},
            {'Namespace': 'aws:autoscaling:launchconfiguration',
             'OptionName': 'EC2KeyPair', 'Value': KEY_PAIR_NAME},
            # Using the existing EC2 Instance Profile Role
            {'Namespace': 'aws:autoscaling:launchconfiguration',
             'OptionName': 'IamInstanceProfile', 'Value': IAM_ROLE_NAME}, 
            # Using the existing EB Service Role
            {'Namespace': 'aws:elasticbeanstalk:environment',
             'OptionName': 'ServiceRole', 'Value': EB_SERVICE_ROLE},
            {'Namespace': 'aws:elasticbeanstalk:environment',
             'OptionName': 'EnvironmentType', 'Value': 'SingleInstance'},
            {'Namespace': 'aws:elasticbeanstalk:application:environment',
             'OptionName': 'PROXY_SERVER', 'Value': 'nginx'},
        ]
        
        # Fetch default VPC and a subnet (ap-south-1a)
        vpc_response = ec2_client.describe_vpcs(Filters=[{'Name': 'isDefault', 'Values': ['true']}])
        vpc_id = vpc_response['Vpcs'][0]['VpcId']
        
        subnet_response = ec2_client.describe_subnets(
            Filters=[
                {'Name': 'vpc-id', 'Values': [vpc_id]},
                {'Name': 'availability-zone', 'Values': [f'{REGION_NAME}a']}
            ]
        )
        subnet_id = subnet_response['Subnets'][0]['SubnetId']

        option_settings.append({'Namespace': 'aws:ec2:vpc', 'OptionName': 'VPCId', 'Value': vpc_id})
        option_settings.append({'Namespace': 'aws:ec2:vpc', 'OptionName': 'Subnets', 'Value': subnet_id})
        

        # Create Environment
        eb_client.create_environment(
            ApplicationName=EB_APP_NAME,
            EnvironmentName=EB_ENV_NAME,
            VersionLabel=EB_VERSION_LABEL,
            SolutionStackName=EB_PLATFORM.split(':')[-1],
            OptionSettings=option_settings,
        )
        print(f"Environment '{EB_ENV_NAME}' creation started...")

        # Wait for deployment to complete
        if wait_for_eb_update(EB_ENV_NAME):
            env_info = eb_client.describe_environments(EnvironmentNames=[EB_ENV_NAME])['Environments'][0]
            print("\nDeployment successful!")
            print(f"EB Environment URL: {env_info['CNAME']}")
        else:
            print("Deployment failed or timed out.")

    except Exception as e:
        print(f"Error during Elastic Beanstalk deployment: {e}")
    finally:
        # Clean up local ZIP file
        if os.path.exists(zip_file):
            os.remove(zip_file)
            print(f"Cleaned up local file: {zip_file}")


def cleanup_all():
    """Deletes only the created Elastic Beanstalk resources."""
    print("\n\n--- Starting AWS Resource Cleanup (EB only) ---")
    
    # 1. Terminate Elastic Beanstalk Environment
    try:
        eb_client.terminate_environment(EnvironmentName=EB_ENV_NAME)
        print(f"Termination of environment '{EB_ENV_NAME}' initiated.")
        wait_for_eb_update(EB_ENV_NAME, desired_status='Terminated')
    except Exception as e:
        print(f"EB Environment termination error (may not exist): {e}")

    # 2. Delete Elastic Beanstalk Application
    try:
        eb_client.delete_application(ApplicationName=EB_APP_NAME)
        print(f"Application '{EB_APP_NAME}' deleted.")
    except Exception as e:
        print(f"EB Application deletion error (may not exist): {e}")
        
    print(f"\nCleanup complete. IAM Roles '{IAM_ROLE_NAME}' and '{EB_SERVICE_ROLE}' and S3 Bucket '{S3_BUCKET_NAME}' were left untouched.")


if __name__ == '__main__':
    if '--cleanup' in sys.argv:
        cleanup_all()
    else:
        deploy_eb_website()
