echo "ex_10_curl_to_flow.sh"
echo
echo "This shell script sends a number to an AT&T Flow iot project using cURL. "
echo "Flow responds by sending back the number along with a color:"
echo
echo "Green if the number is 'odd'"
echo "Blue if the number is 'even'"

# Replace URL with your Endpoint from AT&T Flow
MY_FLOW_URL='https://runm-west.att.io/e9215af2b0eea/8374c4f23615/fa5e6ab1a408526/in/flow/me'

echo
echo
echo "Sending an 'odd' number to Flow"
echo  --------------------------------
curl -X POST $MY_FLOW_URL -d "value=25"

echo
echo
echo "Sending an 'even' number to Flow"
echo  --------------------------------
curl -X POST $MY_FLOW_URL -d "value=320"

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