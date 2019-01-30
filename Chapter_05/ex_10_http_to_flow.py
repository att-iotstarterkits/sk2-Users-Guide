###############################################################################
# file: ex_10_http_to_flow.py
#
# "This program sends a number to an AT&T Flow iot project using HTTP. "
# "Flow responds by sending back the same number along with a color:"
#
# "Green if the number is 'odd'"
# "Blue if the number is 'even'"
#
# Note: Using GPIO to control LEDs was discussed in Chapter 4 and the Appendix.
#
# Note: Your AT&T IoT Starter Kit (2nd generation) must have the Python
#       image installed for this example to work
###############################################################################
import iot_mal                                        # Import the Modem Abstraction Layer (MAL) API module
import iot_hw                                         # Allows access to SK2 hardware resources
import requests                                       # A simple HTTP library for Python, built for human beings
from random import *                                  # Module required to generate random number with randint()

# Replace URL with your Endpoint from AT&T Flow
MY_FLOW_URL = r'https://runm-west.att.io/e9215af2b0eea/8374c4f23615/fa5e6ab1a408526/in/flow/me'

#### Setup the MAL and data connection ########################################
network_handler = iot_mal.network()                   # Connect to MAL.network
network_handler.set_connection_mode(
                                     1,               # Mode: 0 - Always, 1 - On-demand
                                    10,               # On-demand Timeout: Disconnect in mins if no access
                                     2)               # Manual Mode: 0 - Disconnect, 1 - Connect (Always/on-demand),
                                                      #              2 - Connect once

#### Initialize the GPIO connected to the RGB LEDs ############################
ON  = iot_hw.gpio_level.GPIO_LEVEL_HIGH
OFF = iot_hw.gpio_level.GPIO_LEVEL_LOW

red_led = iot_hw.gpio(iot_hw.gpio_pin.GPIO_LED_RED)
red_led.set_dir(iot_hw.gpio_direction.GPIO_DIR_OUTPUT)
red_led.write(OFF)

green_led = iot_hw.gpio(iot_hw.gpio_pin.GPIO_LED_GREEN)
green_led.set_dir(iot_hw.gpio_direction.GPIO_DIR_OUTPUT)
green_led.write(OFF)

blue_led = iot_hw.gpio(iot_hw.gpio_pin.GPIO_LED_BLUE)
blue_led.set_dir(iot_hw.gpio_direction.GPIO_DIR_OUTPUT)
blue_led.write(OFF)

#### Pick a number (randomly) to send to Flow #################################
value = randint(1, 100)                               # Pick a random number between 1 and 100.
print("\nSending the random number: " + str(value) + "\n")

#### Use Python 'requests' module to send data over HTTP ######################
url = MY_FLOW_URL                                     # Get URL from flow.att.io

headers = {                                           # List contains required HTTP headers
    #'Content-Type': 'application/json',
}

data = {                                              # Data to be sent
    "value": value
}

r = requests.post(url, headers=headers, json=data)    # Post data to Flow
print("HTTP Response: " + r.text + "\n")              # Print the response from Flow

#### Turn on the appropriate LED ##############################################
if 'blue' in r.text:
    blue_led.write(ON)
    green_led.write(OFF)
    print("Setting the RGB LED to 'blue'\n")
else:
    blue_led.write(OFF)
    green_led.write(ON)
    print("Setting the RGB LED to 'green'\n")

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