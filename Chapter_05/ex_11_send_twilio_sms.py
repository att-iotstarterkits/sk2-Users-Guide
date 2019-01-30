###############################################################################
# file: ex_11_send_twilio_sms.py
#
# This example sends 'data' to an SMS number using the Twilio.com service.
# Twilio supports sending messages via CURL. Without a native CURL Python
# module on the SK2, the example uses the os.system module to call CURL from
# the Linux command line (i.e. shell out to the command line).
#
# Using GPIO to read the value of the pushbutton was discussed in Chapter 4.
###############################################################################
import iot_mal                                        # Import the Modem Abstraction Layer (MAL) API module
import iot_hw                                         # Allows access to SK2 hardware resources
import requests                                       # A simple HTTP library for Python, built for human beings
import os                                             # Needed to call shell commands via 'os.system'

# Replace URL with one you get from your Twilio account
TWILIO_URL  = r'https://api.twilio.com/2010-04-01/Accounts//Messages.json'
TWILIO_SID  = r'ACxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx'
TWILIO_AUTH = r'xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx'
SMS_FROM    = r'+12165551212'
SMS_TO      = r'+12145551212'

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

data = 'Body="button": ' + button_state

curl_url  = " " + TWILIO_URL + "/" + TWILIO_SID + "/Messages.json"
curl_cmd  = " -X POST"
curl_to   = " --data-urlencode 'To=" + SMS_TO + "'"
curl_from = " --data-urlencode 'From=" + SMS_FROM + "'"
curl_data = " --data-urlencode '" + data + "'"
curl_auth = " -u " + TWILIO_SID + ":" + TWILIO_AUTH

curly = 'curl ' + curl_url + curl_cmd + curl_to + curl_from + curl_data + curl_auth
print(curly)

r = os.system(curly)

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