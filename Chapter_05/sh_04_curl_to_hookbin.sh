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
