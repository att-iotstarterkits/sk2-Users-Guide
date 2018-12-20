# button_read.py
#
# This script reads the button and prints whether
# the button is up or down

import iot_hw                 # Allows access to SK2 hardware resources

ON  = iot_hw.gpio_level.GPIO_LEVEL_HIGH
OFF = iot_hw.gpio_level.GPIO_LEVEL_LOW

# Initialize the GPIO connected to the SK2 User Button
button = iot_hw.gpio(iot_hw.gpio_pin.GPIO_USER_BUTTON)
button.set_dir(iot_hw.gpio_direction.GPIO_DIR_INPUT)

val = button.read()

if val:
    print("The button is up (" + str(val) + ")")
else:
    print("The button is down (" + str(val) + ")")

