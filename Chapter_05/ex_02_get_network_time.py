###############################################################################
# file: ex_02_get_network_time.py
#
# Connect to the Modem Abstraction Layer and access the network time.
# The network time can be accessed in a couple of different ways; this
# example uses the WWAN get_network_time() method.
#
# Along with showing access to MAL, this example demonstrates how to get the
# data value from the returned dictionary string and format it.
#
###############################################################################
import iot_mal                                                         # Import the Modem Abstraction Layer (MAL) API module
from datetime import datetime, timedelta

CST = -6                                                               # Time difference (hours0 between GMT and CST

# Accessing MAL to get system information
mal_wwan = iot_mal.wwan()                                              # Connect to MAL.wwan
raw_time = mal_wwan.get_network_time()                                 # Reads network time over the wireless wide area network

print(raw_time)                                                        # Print the "raw" value for the network time

# Python formatting examples
net_time = raw_time.get('network_time')                                # Use .get() to extract the time from dictionary variable
print('net_time = {0}'.format(net_time))

t = datetime.strptime(net_time, '%Y/%m/%d %H:%M:%S-%f,00')             # Convert unicode string to datetime value
lt = t + timedelta(hours=CST)
print('Local time = {0}'.format(lt))

# Do it all in one line of code
print('Local time = {0}'.format(datetime.strptime(mal_wwan.get_network_time().get('network_time'), '%Y/%m/%d %H:%M:%S-%f,00') + timedelta(hours=CST)))

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