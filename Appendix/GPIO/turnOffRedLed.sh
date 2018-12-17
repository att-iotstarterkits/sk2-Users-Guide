# TurnOffRedLed.sh
#
# This simple example turns off the Red RGB LED
#
cd /sys/class/gpio

echo 38 > export
echo out > gpio38/direction

echo 0 > gpio38/value
