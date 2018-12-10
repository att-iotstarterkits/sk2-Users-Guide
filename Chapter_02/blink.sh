# blink.sh
#
# This is a simple example for blinking the WWAN LED five times
# - The For loop executes once per character (a thru e)
# - 'sleep 1' causes the cpu to wait 1 second
# - At the end of the script, the LED is turned off
#
for var in a b c d e; do
        echo  0 > /sys/class/leds/wwan/brightness
        sleep 1
        echo  1 > /sys/class/leds/wwan/brightness
        sleep 1
done
echo 0 > /sys/class/leds/wwan/brightness
