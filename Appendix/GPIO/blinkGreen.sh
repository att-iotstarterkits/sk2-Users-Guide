# blinkGreen.sh
#
# This is a simple example for blinking the Green RGB LED five times
# - The For loop executes once per character (a thru e)
# - 'sleep 1' causes the cpu to wait 1 second
# - At the end of the script, the LED is turned off
#
cd /sys/class/gpio

echo 21 > export
echo out > gpio21/direction

for var in a b c d e; do
    echo  0 > gpio21/value
    sleep 1
    echo  1 > gpio21/value
    sleep 1
done
echo 0 > gpio21/value