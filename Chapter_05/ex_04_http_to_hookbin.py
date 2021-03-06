###############################################################################
# file: ex_04_http_to_hookbin.py
#
# This example sends a simple JSON data packet via HTTP to a site
# called Hookbin. This free 3rd party site allows you to view HTTP posts,
# puts, and gets. To try this example, you'll need to replace the HOOKBIN_URL
# address with one you obtain from http://www.hookbin.com
#
# Using GPIO to read the value of the pushbutton was discussed in Chapter 4.
###############################################################################
import iot_mal                                        # Import the Modem Abstraction Layer (MAL) API module
import iot_hw                                         # Allows access to SK2 hardware resources
import requests                                       # A simple HTTP library for Python, built for human beings

HOOKBIN_URL = r'https://hookb.in/PxNBKyBnMOsORjbyw0j6'# Replace URL with one you get from Hookbin.com

#### Setup the MAL and data connection ########################################
network_handler = iot_mal.network()                   # Connect to MAL.network
network_handler.set_connection_mode(
                                     1,               # Mode: 0 - Always, 1 - On-demand
                                    10,               # On-demand Timeout: Disconnect in mins if no access
                                     2)               # Manual Mode: 0 - Disconnect, 1 - Connect (Always/on-demand),
                                                      #              2 - Connect once

#### Initialize the GPIO connected to the SK2 User Button #####################
button = iot_hw.gpio(iot_hw.gpio_pin.GPIO_USER_BUTTON)
button.set_dir(iot_hw.gpio_direction.GPIO_DIR_INPUT)

if button.read():
    button_state = 'up'
else:
    button_state = 'down'

#### Use Python 'requests' module to send data over HTTP ######################
url = HOOKBIN_URL                                     # Get URL from Hookbin.com (free 3rd party service)

headers = {                                           # List contains required HTTP headers
    'Content-Type': 'application/json',
}

data = {                                              # JSON data to be sent
    "button": button_state
}

r = requests.post(url, headers=headers, json=data)    # Post data to Hookbin
print(r.text)                                         # Print the response from Hookbin

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