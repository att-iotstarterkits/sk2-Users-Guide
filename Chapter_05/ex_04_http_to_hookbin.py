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

HOOKBIN_URL = r'https://hookb.in/PxNBKyBnMOsORjbyw0j6'# Replace URL with one you get from

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
