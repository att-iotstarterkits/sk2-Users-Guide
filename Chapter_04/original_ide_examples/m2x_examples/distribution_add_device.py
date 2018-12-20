#!/usr/bin/env python

# Usage:
#   $ API_KEY=<YOUR MASTER API KEY> python distribution_add_device.py

import os

from m2x.client import M2XClient

KEY = os.environ['KEY']
DISTRIBUTION_ID = os.environ['DISTRIBUTION_ID']

# Instantiate a client
client = M2XClient(key=KEY)

params = {
    'name':'Distribution Test',
    'description':'Test device for distribution',
    'visibility':'private',
    'serial':'abc'  # Required param. Must be Unique.
}

# Get target distribution
distribution = client.distribution(DISTRIBUTION_ID)

# Add device to distribution
response = distribution.add_device(params)

print("Response status: %s" % response['status'])
