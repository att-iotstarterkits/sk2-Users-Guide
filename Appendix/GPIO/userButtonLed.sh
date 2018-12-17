# userButtonLed.sh
#
# This example reads the value of the user button and turns 
# on either the Green or Red RGB LED depending upon the value
# of the user button
#

# Go to the GPIO directory
cd /sys/class/gpio

# Grant user-space access to all 3 LEDs and the USER button

    # USER button
    echo 23 > export
    echo in > gpio23/direction

    # Green LED
    echo 21 > export
    echo out > gpio21/direction

    # Blue LED
    echo 22 > export 
    echo out > gpio22/direction

    # Red LED
    echo 38 > export 
    echo out > gpio38/direction

# Turn off all three LEDs
echo 0 > gpio38/value 
echo 0 > gpio22/value
echo 0 > gpio21/value

# Read the value of the USER push button into "val"
val=$(cat gpio23/value)
echo $val

# Turn on LED
if [ $val -gt 0 ] 
then
    # If "up" turn on Green LED
    echo 1 > gpio21/value
else
    # If "down" turn on Red LED
    echo 1 > gpio38/value
fi
