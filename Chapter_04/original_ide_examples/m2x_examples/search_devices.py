#!/usr/bin/env python

# Usage:
#   $ API_KEY=<YOUR MASTER API KEY> python example.py

import os

from m2x.client import M2XClient
from m2x.v2.devices import Device

client = M2XClient(key=os.environ['API_KEY'])

params = {
    "visibility": "private",
    "status": "enabled",
    "limit": "3"
}

# Use data=... to send also a JSON body in the request
response = Device.search(api=client, data=params)

if len(response) > 0:
    print("Devices Details:\n")
    for device in response:
        print("          Name: {device.name}".format(device=device))
        print("            Id: {device.id}".format(device=device))
        print("    Visibility: {device.visibility}".format(device=device))
        print("        Status: {device.status}\n".format(device=device))
else:
    print("Devices not available in this search criteria")
