# userButtonCat.sh
#
# This is a simple example reads the value of the user button
# and outputs the value (using 'cat') to the command line.
# It then waits 3 seconds and does it again#
cd /sys/class/gpio

echo 23 > export
echo in > gpio23/direction
cat gpio23/value

sleep 3
# now hold-down the USER button and press up-arrow to repeat previous command
cat gpio23/value
