# blinkBlue.sh
#
# This is a simple example for blinking the Blue RGB LED five times
# - The For loop executes once per character (a thru e)
# - 'sleep 1' causes the cpu to wait 1 second
# - At the end of the script, the LED is turned off
#
cd /sys/class/gpio

echo 22 > export
echo out > gpio22/direction

for var in a b c d e; do
    echo  0 > gpio22/value
    sleep 1
    echo  1 > gpio22/value
    sleep 1
done
echo 0 > gpio22/value