###############################################################################
# file: ex_03_get_system_info.py
#
# Connect to the Modem Abstraction Layer and access system and connection info
###############################################################################
import iot_mal                              # Import the Modem Abstraction Layer (MAL) API module

###############################################################################
# function: parse_state(state)
#
# Parses the connection state value and returns descriptive string
###############################################################################
def parse_state(state):
    if state == 0:
        ret = 'Disconnected'
    elif state == 1:
        ret = 'Disconnecting'
    elif state == 2:
        ret = 'Connecting'
    elif state == 3:
        ret = 'Connected'
    elif state == 4:
        ret = 'Disconnected, and PIN locked'
    elif state == 5:
        ret = 'Disconnected, and SIM removed'
    return ret

###############################################################################
# Main code
###############################################################################

# Setup the MAL and data connection
network_handler = iot_mal.network()         # Connect to MAL.network
network_handler.set_connection_mode(
     1,                                     # Mode: 0 - Always, 1 - On-demand
    10,                                     # On-demand Timeout: Disconnect in mins if no access
     2)                                     # Manual Mode: 0 - Disconnect, 1 - Connect (Always/on-demand),
                                            #              2 - Connect once
system_handler = iot_mal.system()           # Connect to MAL.system

# Print out system information
firm  = system_handler.get_firmware_version().get('version')
imei  = system_handler.get_imei().get('imei')
imsi  = system_handler.get_imsi().get('imsi')
iccid = system_handler.get_iccid().get('iccid')

print('System Information')
print('------------------')
print('Firmware version: ' + firm)
print('IMEI            : ' + imei)
print('IMSI            : ' + imsi)
print('ICCID           : ' + iccid)

# Print out connection information
status = network_handler.get_connection_status()

print('\nConnection Information')
print(  '----------------------')
print('Connection State: ' + parse_state(status.get('state')))
print('Connection Time : ' + status.get('connection_time'))
print('Radio Mode      : ' + str(status.get('radio_mode')) + 'G ' + status.get('data_bearer_tech'))
print('My IP address   : ' + status.get('ip'))

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