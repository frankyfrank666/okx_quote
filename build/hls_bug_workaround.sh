#!/bin/bash

# Check if the script is run as root or with sudo
if [[ $(id -u) != 0 ]]; then
    echo "This script must be run as root or with sudo."
    exit 1
fi

# Set the new system time
new_date="20210101"
new_time="00:00:00"

# Change the system time using the date command
date -s "${new_date} ${new_time}"

# Verify the new system time
echo "New system time:"
date