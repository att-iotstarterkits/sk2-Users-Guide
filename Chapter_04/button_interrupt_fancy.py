###############################################################################
# button_interrupt_fancy.py
# 2018.12.17
#
# After initialization, the routine will continue to blink the WWAN LED
# until the User Button is pressed and held for 3 or more seconds.
#
# Each time the User Button is pressed, the Blue LED is toggled on or off.
###############################################################################
# Import modules
import iot_hw                                               # Needed for GPIO API to use SK2 LEDs and Button
import time                                                 # Needed for time.sleep() function
from wwan_class import wwan                                 # Needed for WWAN LED class

# Global variables
loop = True                                                 # Used for main while loop
blue = 1                                                    # Used when toggling Blue LED
button_pressed = 0                                          # Keeps track of time button is pressed between interrupt callbacks

# A callback function that will turn on the blue LED
def my_callback_fcn(gpio_pin, trigger):
    global loop, blue, button_pressed                       # Give function access to these global variables

    if trigger == 0:                                        # If pushing the button down
        print("--> Falling interrupt occured..." )
        button_pressed = time.time()                        # Store current time to 'button_pressed'

        blue ^= 1
        if blue == 0:
            led.write(iot_hw.gpio_level.GPIO_LEVEL_HIGH)    # Turn on Blue LED
        else:
            led.write(iot_hw.gpio_level.GPIO_LEVEL_LOW)     # Turn off Blue LED

    else:                                                   # If letting up on the button
        print("<-- Rising interrupt occured...")
        button_held = time.time() - button_pressed          # Calculate how long button was held

        if button_held >= 3:
            loop = False                                    # Change while loop's exit condition since button was held long enough
            print("Exiting... because button was held down for more than 3 seconds (" + str(button_held) + " to be exact)\n")
        else:
            print("Button was held down for " + str(button_held) + " seconds\n")

    return 0

# Main code starts here
print("\nStarting up... please wait")
led = iot_hw.gpio(iot_hw.gpio_pin.GPIO_LED_BLUE)            # Allocate Blue LED GPIO pin
led.set_dir(iot_hw.gpio_direction.GPIO_DIR_OUTPUT)          # Set Blue LED GPIO pin to "output"
led.write(iot_hw.gpio_level.GPIO_LEVEL_LOW)                 # Turn off Blue LED

button = iot_hw.gpio(iot_hw.gpio_pin.GPIO_PIN_98)           # Allocate User Button GPIO pin
button.set_dir(iot_hw.gpio_direction.GPIO_DIR_INPUT)        # Configure User BUtton as "input"
button.interrupt_request(
    iot_hw.gpio_irq_trig.GPIO_IRQ_TRIG_BOTH,                # Trigger interrupt when pressing down on button
    my_callback_fcn)                                        # Run my_callback_fcn() after the interrupt is generated

w = wwan()                                                  # Create instances of WWAN LED class and set equal to 'w'
w.off()                                                     # Turn off WWAN LED

print("Ready... feel free to press button\n")
while loop == True:                                         # Loop until 'loop' variable is changed by the interrupt routine
    w.toggle()                                              # Toggle WWAN LED
    time.sleep(1)                                           # Sleep for 1 second

# Don't access this code unless button is pressed and held for 3 or more seconds
print("Freeing resources...\n")
led.write(iot_hw.gpio_level.GPIO_LEVEL_LOW)                 # Turn off Blue LED
button.interrupt_free()                                     # Turn off button interrupt and free IRQ resources
button.close()                                              # Free up User Button's GPIO pin
led.close()                                                 # Free up Blue LED
w.off()                                                     # Make sure the WWAN LED is off
