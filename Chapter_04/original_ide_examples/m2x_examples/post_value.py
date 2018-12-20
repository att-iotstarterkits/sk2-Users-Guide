#!/usr/bin/env python

# Creates a Device and a Stream associated with the device,
# then posts the current time every 10 seconds.
#
# Usage:
#   $ API_KEY=<YOUR APIKEY> python example.py

import os
import time

from m2x.client import M2XClient

# Instantiate a client
client = M2XClient(key=os.environ['API_KEY'])

# Create a device
device = client.create_device(
    name='Current Time Example',
    description='Store current time every 10 seconds',
    visibility='public'
)

# Create a data stream associated with target Device
stream = device.create_stream('stream_name')

# And now register the current time every 10 seconds (hit ctrl-c to kill)
while True:
    stream.add_value(int(time.time()))
    time.sleep(10)
