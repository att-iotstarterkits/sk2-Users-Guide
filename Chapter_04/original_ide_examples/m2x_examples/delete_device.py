#!/usr/bin/env python

# Usage:
#   $ API_KEY=<YOUR MASTER API KEY> DEVICE_ID=<TARGET_DEVICE_ID> python delete_device.py

# Note: every M2X resource has a remove() method which can be used to delete the resource from M2X.

import os

from m2x.client import M2XClient

# Instantiate a client
client = M2XClient(key=os.environ['API_KEY'])

# Delete the device device
try:
  device = client.device(os.environ['DEVICE_ID'])
  print "Deleting device with ID {id}".format(id=device.id)
  device.remove()
except Exception:
  pass

if client.last_response.status == 204:
  print "Device removed successfully!"
else:
  print "Error occurred, see printout of API response below for details:"
  print client.last_response.raw
