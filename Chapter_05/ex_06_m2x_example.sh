echo sh_06_m2x_example.sh
echo
echo This shell script invokes two python scripts from:  /CUSTAPP/iot_files/m2x_examples
echo The first Python example creates an M2X device called 'Current Time Example' and the
echo second example adds a stream called 'stream_name'.
echo
echo Since the 'post_value.py' example does more than just posting a value to a stream,
echo we chose to use cURL to add two values to the M2X device.
#
# Note: Your AT&T IoT Starter Kit (2nd generation) must have the Python image installed
#       for this example to work

M2X_EXAMPLES_PATH="/CUSTAPP/iot_files/m2x_examples"     # Set to location of your m2x_examples directory (only need to change if you moved it)
MY_MASTER_API_KEY=b2762079a8b9115e0f11060b5d73098a      # Replace this value with the Master API Key for your M2X account

echo
my_device_id=$(API_KEY=$MY_MASTER_API_KEY python $M2X_EXAMPLES_PATH/create_device.py)
echo The new device key is: $my_device_id

DEVICE_ID=$my_device_id API_KEY=$MY_MASTER_API_KEY python $M2X_EXAMPLES_PATH/create_stream.py
echo "The 'stream_name' stream was added to the device"

echo
echo "Now the script will add the values '1' and '2' to the stream"
echo
echo "Adding '1'"
echo ---------------------------
curl -i -X PUT http://api-m2x.att.com/v2/devices/$my_device_id/streams/stream_name/value -H "X-M2X-KEY: $MY_MASTER_API_KEY" -H "Content-Type: application/json" -d "{ \"value\": \"1\" }"

echo
echo
echo "Adding '2'"
echo ---------------------------
curl -i -X PUT http://api-m2x.att.com/v2/devices/$my_device_id/streams/stream_name/value -H "X-M2X-KEY: $MY_MASTER_API_KEY" -H "Content-Type: application/json" -d "{ \"value\": \"2\" }"

echo
echo
echo "That's it, we're done!"
echo

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