import iot_hw
import time

ON  = iot_hw.gpio_level.GPIO_LEVEL_HIGH
OFF = iot_hw.gpio_level.GPIO_LEVEL_LOW

# Initialize all LEDs
red_led = iot_hw.gpio(iot_hw.gpio_pin.GPIO_LED_RED)
red_led.set_dir(iot_hw.gpio_direction.GPIO_DIR_OUTPUT)

green_led = iot_hw.gpio(iot_hw.gpio_pin.GPIO_LED_GREEN)
green_led.set_dir(iot_hw.gpio_direction.GPIO_DIR_OUTPUT)

blue_led = iot_hw.gpio(iot_hw.gpio_pin.GPIO_LED_BLUE)
blue_led.set_dir(iot_hw.gpio_direction.GPIO_DIR_OUTPUT)

# Cycle all LEDs on and off
# Red on
red_led.write(ON)
time.sleep(1)

# Green on, Red off
green_led.write(ON)
red_led.write(OFF)
time.sleep(1)

# Blue on, Green off
blue_led.write(ON)
green_led.write(OFF)
time.sleep(1)

# Red on (Purple)
red_led.write(ON)
time.sleep(1)

# Blue off, Green on (Yellow)
blue_led.write(OFF)
green_led.write(ON)
time.sleep(1)

# Red off, Blue on (Teal)
blue_led.write(ON)
red_led.write(OFF)
time.sleep(1)

# Red on (White)
red_led.write(ON)
time.sleep(1)

# All LEDs off
red_led.write(OFF)
red_led.close()
green_led.write(OFF)
green_led.close()
blue_led.write(OFF)
blue_led.close()