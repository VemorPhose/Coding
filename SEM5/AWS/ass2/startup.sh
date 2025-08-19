#!/bin/bash
# Update package list
sudo apt update -y

# Install Apache and AWS CLI
sudo apt install -y apache2 awscli

# Ensure Apache starts on boot
sudo systemctl enable apache2

# Copy website files from S3 bucket
# Using --recursive to copy all files in folder
aws s3 cp s3://ungabunga69/ass2/ /var/www/html/ --recursive

# Restart Apache to make sure it serves the new files
sudo systemctl restart apache2
