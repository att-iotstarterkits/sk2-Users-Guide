echo
echo "ex_11_send_twilio_sms.sh"
echo
echo "This shell script sends a SMS message using cURL."
echo "You must set up an account with Twilio before running this script."
echo "At the time of writing, they offered free developer accounts"
echo
echo "Also, you must edit the header information with your own Twilio"
echo "account information."
echo

# Replace URL, SID, and Auth Token with information for your Twilio account
TWILIO_URL='https://api.twilio.com/2010-04-01/Accounts'
TWILIO_SID='ACxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx'
TWILIO_AUTH='xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx'
TWILIO_FROM='+12165551212'

# Specify the number where to send the SMS message
SMS_TO='+12145551212'

# Specify the data to be sent
DATA='Just wanted to say "Hello" from my SK2!'

# Building the CURL string
echo "Sending the SMS message...
echo  ----------------------------------------------
curl -X POST $TWILIO_URL/$TWILIO_SID/Messages.json \
--data-urlencode "From=$TWILIO_FROM" \
--data-urlencode "Body=$DATA" \
--data-urlencode "To=$SMS_TO" \
-u $TWILIO_SID:$TWILIO_AUTH

echo
echo
echo "That's it, we're done!"
echo

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