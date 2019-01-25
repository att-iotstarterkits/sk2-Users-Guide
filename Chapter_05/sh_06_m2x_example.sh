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

MY_MASTER_API_KEY=b2762079a8b9115e0f11060b5d73098a      # Replace this value with the Master API Key for your M2X account

echo
my_device_id=$(API_KEY=$MY_MASTER_API_KEY python create_device.py)
echo The new device key is: $my_device_id

DEVICE_ID=$my_device_id API_KEY=$MY_MASTER_API_KEY python create_stream.py
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
