#!/usr/bin/env python
#
# Usage:
#   $ DEVICE_ID=<YOUR DEVICE ID> API_KEY=<YOUR APIKEY> python example.py

import os
from datetime import datetime

from m2x.client import M2XClient

# Instantiate a client
client = M2XClient(key=os.environ['API_KEY'])

# Get target device
device = client.device(os.environ['DEVICE_ID'])

from_date = "2016-11-18T09:35:19.122Z"
end_date = "2016-11-18T13:15:02.517Z"

response = device.delete_location_history( data = { 
	'from': from_date, 
	'end' : end_date 
})

print("Response status: %s" % response['status'])
