#!/usr/bin/env python

# Usage:
#   $ KEY=<YOUR APIKEY> DEVICE=<YOUR DEVICE ID> python example.py

import os
import sys
import pprint

sys.path.append(os.path.join(os.path.dirname(__file__), '..'))

from m2x.client import M2XClient


KEY = os.environ['KEY']
DEVICE_ID = os.environ['DEVICE']

client = M2XClient(key=KEY)
device = client.device(DEVICE_ID)

pprint.pprint(device.data)
