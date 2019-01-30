# sh_04_curl_to_hookbin.sh
#
# This example reads the value of the user button and sends
# that value to Hookbin.com using CURL
#

# Go to the GPIO directory
cd /sys/class/gpio

# Grant user-space access to the USER button

    # USER button
    echo 23 > export
    echo in > gpio23/direction

# Read the value of the USER push button into "val"
val=$(cat gpio23/value)
echo Button = $val

echo 23 > unexport

# Turn on LED
if [ $val -gt 0 ]
then
    # If "up"
    data='{"button":"up"}'
else
    # If "down"
    data='{"button":"down"}'
fi

curl https://hookb.in/PxNBKyBnMOsORjbyw0j6 --header "Content-Type: application/json" --request POST --data $data

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