#!/usr/bin/env python

# Usage:
#   $ DEVICE_ID=<YOUR DEVICE ID> API_KEY=<YOUR APIKEY> python example.py

import os

from m2x.client import M2XClient

# Instantiate a client
client = M2XClient(key=os.environ['API_KEY'])

# Get target device
device = client.device(os.environ['DEVICE_ID'])

# Create a data stream associated with target Device
stream = device.create_stream('stream_name')
