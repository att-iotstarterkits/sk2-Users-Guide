#!/usr/bin/env python

# ex_07_m2x_create_device_stream_value.py
#
# Checks to see if a specific device and stream exist. It they don't exist it
# creates them and then posts data to the stream every 10 seconds (for a minute).
#
# The 'time' values being posted are essentially the current number of seconds
# during the routine, but the even values are inverted just to make the M2X
# data graph look more interesting.

import time
from m2x.client import M2XClient

API_KEY = "b2762079a8b9115e0f11060b5d73098a"                                    # Replace this value with the Master API Key for your M2X account
DEVICE  = 'Example_07'
STREAM  = 'time_values'

my_device = ""
my_stream = ""
sign      = 1
base_time = int(time.time())

print("\nLooking for device '" + DEVICE + "' with stream '" + STREAM + "'.")
client = M2XClient(key=API_KEY)                                                 # Get M2X client

# Find or create the device
devices = client.devices()                                                      # Get list of devices
for device in devices:                                                          # Look for DEVICE in list of devices
    if device.name == DEVICE:
        my_device = device
        print("Found device: " + str(my_device.name))

if my_device == "":                                                             # Did we find the DEVICE?
    print("Creating device: " + DEVICE)
    my_device = client.create_device(                                           # If not, create the DEVICE
        name=DEVICE,
        description='Store current time every 10 seconds for a minute',
        visibility='public'
    )
    print("Created device_id: " + str(my_device.id))

print("\nLooking for stream '" + STREAM + "'")
streams = my_device.streams()                                                   # Get the list of streams from teh device
for stream in streams:
    if stream.name == STREAM:                                                   # Is the STREAM we want to use in the list?
        my_stream = stream
        print("Found stream: " + my_stream.name + "\n")

if my_stream == "":
    my_stream = my_device.create_stream(STREAM)                                 # If STREAM wasn't found, create it
    print("Created stream: " + my_stream.name + "\n")

# And now register the current time every 10 seconds (for about a minute)
for t in range(1, 7):                                                           # Generate 6 values
    my_time = (int(time.time()) - base_time) * sign                             # Get current time and subract start time of program; multiply by sign (1 or -1)
    print("-->Adding value: " + str(my_time))
    my_stream.add_value(my_time)                                                # Add the value to the STREAM
    sign = 1 if t%2 == 0 else -1                                                # Invert the value of sign (based on odd versus even range index)
    time.sleep(10)                                                              # Wait 10 seconds

print("\nExecution complete! \n")

# =============================================================================
#  Copyright (c) 2018, AT&T (R)
#
#  www.att.com 
# 
#  Licensed under the Apache License, Version 2.0 (the "License"); 
#  you may not use this file except in compliance with the License.
#  You may obtain a copy of the License at
#
#   http://www.apache.org/licenses/LICENSE-2.0
#
#  Unless required by applicable law or agreed to in writing, 
#  software distributed under the License is distributed on an 
#  "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, 
#  either express or implied. See the License for the specific 
#  language governing permissions and limitations under the License.
# =============================================================================