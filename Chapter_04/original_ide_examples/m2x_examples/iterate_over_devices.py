#!/usr/bin/env python

# Usage:
#   $ API_KEY=<YOUR MASTER API KEY> python example.py

import os

from m2x.client import M2XClient
 
client = M2XClient(key=os.environ['API_KEY'])
 
# Make an initial call to List Devices 
# to get the first page & number of pages
# Docs: https://m2x.att.com/developer/documentation/v2/device#List-Devices
page_of_devices = client.devices()
number_of_pages = client.last_response.json['pages']
total_devices = client.last_response.json['total']

print "Total Number of Devices: {t}".format(t=total_devices)

# Iterate over all pages of devices
# using default page limit of 100
# you can request smaller pages of devices by 
# passing the `limit` parameter to the devices() method
for page in range(1, number_of_pages + 1):
  print "{d} devices returned on page {p}".format(d=len(page_of_devices), p=page)
  next_page = page + 1
  page_of_devices = client.devices(page=next_page)
  
