###############################################################################
# button_interrupt.py
# 2018.12.07 
#
# Configure SK2 User Button to generate interrupt, then sleep for 30 seconds.
# If button is pushed within 30 seconds, light the Blue LED and then exit the 
# program. If not pushed, the program will still exit after the 30 second wait.
# Note: If turned on, Blue LED will stay on after program exits.
#
# This example was adapted from the sample code provided in the Python 
# Peripheral API Guide.
###############################################################################
import iot_hw                                               # Needed for GPIO API to use SK2 LEDs and Button
import time                                                 # Needed for time.sleep() function

# A callback function that will turn on the blue LED
def callback_function(gpio_pin, trigger):
    print("Interrupt occured...")
    led = iot_hw.gpio(iot_hw.gpio_pin.GPIO_LED_BLUE)        # Allocate Blue LED GPIO pin
    led.set_dir(iot_hw.gpio_direction.GPIO_DIR_OUTPUT)      # Set Blue LED GPIO pin to "output"
    led.write(iot_hw.gpio_level.GPIO_LEVEL_HIGH)            # Turn on Blue LED
    led.close()
    return 0

print("Starting up...")
button = iot_hw.gpio(iot_hw.gpio_pin.GPIO_PIN_98)           # Allocate User Button GPIO pin
button.set_dir(iot_hw.gpio_direction.GPIO_DIR_INPUT)        # Configure User BUtton as "input"
button.interrupt_request(
    iot_hw.gpio_irq_trig.GPIO_IRQ_TRIG_FALLING,             # Trigger interrupt when pressing down on button
    callback_function)                                      # Run callback_function() after the interrupt is generated

print("Ready to sleep...")
time.sleep(30)                                              # Sleep for 30 seconds
# Press the button here, during the 30 second wait

print("Freeing resources...")
button.interrupt_free()                                     # Turn off button interrupt and free IRQ resources
button.close()                                              # Free up User Button's GPIO pin