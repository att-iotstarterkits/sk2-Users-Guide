# Note: This example is the "iot_m2x_example.py" file that is part of the
#       SK2 Python IDE, but has been modified to add our example KEY and
#       DEVICE_ID values.

import iot_mal
import iot_hw
from m2x.client import M2XClient

#Before running this example, read the ATT M2X Dashboard section in the Getting Started Guide

KEY = "aedd25d410ac8de9b9383e542078f842"
DEVICE_ID = "293f7c83e3fb261fdbdd8ea7a3b17ff3"
STREAM_NAME = "light_sensor"

#Setup the MAL and data connection
network_handler = iot_mal.network()
network_handler.set_connection_mode(1,10,2)

#Initialize the ADC and read the ambient light level
light_sensor = iot_hw.adc()
light_value = light_sensor.read()
light_sensor.close()

# Setup the M2X stream based on the values input above
client = M2XClient(key=KEY)
device = client.device(DEVICE_ID)
light_sensor_stream = device.stream(STREAM_NAME)

#Add the light sensor value to the data stream
light_sensor_stream.add_value(float(light_value))


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