###############################################################################
# file: ex_01_mal_api_example.py
#
# Connect to the Modem Abstraction Layer and access the SK2 SIM cards ICCID.
# MAL provides three API groups: System, Network, and WWAN. This example uses
# the "System" API.
#
# Along with showing access to MAL, this example demonstrates how to get the
# data value from the returned dictionary string.
#
###############################################################################
import iot_mal                                                         # Import the Modem Abstraction Layer (MAL) API module

# Accessing MAL to get system information
mal_sys = iot_mal.system()                                             # Connect to MAL.system
raw_iccid = mal_sys.get_iccid()                                        # This method reads the ICCID from the SIM card

print(raw_iccid)                                                       # Print the "raw" output for the iccid and
                                                                       # notice that a Unicode Python dictionary is returned
# Python formatting examples
iccid = raw_iccid.get('iccid')                                         # Use .get() to extract iccid value from dictionary var
print(iccid)

print('Your ICCID is: {0}'.format(iccid))                              # One of many pythy ways to embed data into output string
print('Your ICCID is: {0}'.format(mal_sys.get_iccid().get('iccid')))   # Or do it all in one complex line of code

# =============================================================================
#  Copyright © 2018, AT&T (R)
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