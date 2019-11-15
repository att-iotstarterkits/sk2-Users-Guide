#red_led_blink.py

import time                   # Needed for time.sleep() function 
import iot_hw                 # Allows access to SK2 hardware resources 
 
# Define 'ON' and 'OFF' 
ON  = iot_hw.gpio_level.GPIO_LEVEL_HIGH 
OFF = iot_hw.gpio_level.GPIO_LEVEL_LOW 
 
# Allocate and configure GPIO as output for Red LED 
red_led = iot_hw.gpio(iot_hw.gpio_pin.GPIO_LED_RED) 
red_led.set_dir(iot_hw.gpio_direction.GPIO_DIR_OUTPUT) 
 
# Red on 
red_led.write(ON) 
time.sleep(1) 
 
# Red off 
red_led.write(OFF) 
 
# Release Red LED resource 
red_led.close()
