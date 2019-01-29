# Note: Your AT&T IoT Starter Kit (2nd generation) must have the Python image installed
#       for this example to work

M2X_EXAMPLES_PATH="/CUSTAPP/iot_files/m2x_examples"     # Set to location of your m2x_examples directory (only need to change if you moved it)
MY_MASTER_API_KEY=b2762079a8b9115e0f11060b5d73098a      # Replace this value with the Master API Key for your M2X account
M2X_DEVICE_ID="293f7c83e3fb261fdbdd8ea7a3b17ff3"
echo
DEVICE=$M2X_DEVICE_ID KEY=$MY_MASTER_API_KEY python $M2X_EXAMPLES_PATH/example.py


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