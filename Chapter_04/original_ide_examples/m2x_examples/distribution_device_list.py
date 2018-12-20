#!/usr/bin/env python

# Usage:
#   $ API_KEY=<YOUR MASTER API KEY> python example.py

import os

from m2x.client import M2XClient

KEY = os.environ['KEY']
DISTRIBUTION_ID = os.environ['DISTRIBUTION_ID']

# Instantiate a client
client = M2XClient(key=KEY)

params = {
    "limit":"3",
    "page":"1"
}

# Get target distribution
distribution = client.distribution(DISTRIBUTION_ID)

# Get list of distribution devices
response = distribution.devices(**params)

if len(response) > 0:
    print("\nDevice Details :")
    for device in response:
        print("Device name: %s Device Id: %s Device Visibility: %s Device Status: %s " % (device.name, device.id, device.visibility, device.status))
else:
    print("Devices not available in this search criteria")
