# TurnOnRedLed.sh
#
# This simple example turns on the Red RGB LED
#
cd /sys/class/gpio

echo 38 > export
echo out > gpio38/direction

echo 1 > gpio38/value
