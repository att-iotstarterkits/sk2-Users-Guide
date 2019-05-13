#!/usr/bin/env python

"""
i2c_hw_example.py

Taken from the iot_hw_example.py code example, this example toggles two GPIO
pins before reading from the "WHO_AM_I" register of the LIS2DW12 sensor found
on the SK2.

- GPIO flash blue LED and GPIO 95 (found on the PMOD connector)
- I2C Read of 'WHO_AM_I' register from accelerometer chip

"""

import iot_hw
import time


def test_i2c():
    print('Test I2C')
    dev = 0x19                                                                  # i2c slave address of LIS2DW12 accelerometer
    addr = [0x0f]                                                               # WHO_AM_I register
    data = list()                                                               # Create data array to receive results from "WHO_AM_I"

    myi2c = iot_hw.i2c()                                                        # Initialize (i.e. open) the i2c bus protocol
    myi2c.write(dev, addr, 1, iot_hw.i2c_flag.I2C_NO_STOP)                      # Send a request to WHO_AM_I register
    myi2c.read(dev, data, 1)                                                    # Read data from the WHO_AM_I register
    print('  I2C reg {0:#2x} value is: {1:#2x}'.format(addr[0], data[0]))


def test_leds():
    print('Test LEDs')
    #leds = {"Red":iot_hw.gpio_pin.GPIO_LED_RED, "Green":iot_hw.gpio_pin.GPIO_LED_GREEN, "Blue":iot_hw.gpio_pin.GPIO_LED_BLUE}
    leds = {"Blue":iot_hw.gpio_pin.GPIO_LED_BLUE, "Pmod95":iot_hw.gpio_pin.GPIO_PIN_95}

    for key in leds:
        myled = iot_hw.gpio(leds[key])
        myled.set_dir(iot_hw.gpio_direction.GPIO_DIR_OUTPUT)
        print('  {} on'.format(key))
        myled.write(iot_hw.gpio_level.GPIO_LEVEL_HIGH)
        time.sleep(1)
        print('  {} off'.format(key))
        myled.write(iot_hw.gpio_level.GPIO_LEVEL_LOW)
        time.sleep(1)
        myled.close()


def main():
    test_leds()
    test_i2c()


if __name__ == "__main__":
    try:
        main()
    except:
        if False:
            # type, value, tb = sys.exc_info()
            # traceback.print_exc()
            # pdb.post_mortem(tb)
            print('__main__ error')
        else:
            raise
