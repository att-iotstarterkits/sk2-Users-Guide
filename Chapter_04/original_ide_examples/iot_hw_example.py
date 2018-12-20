#!/usr/bin/env python

"""
iot_hw_example.py

provides a test example for the iot_hw module.
It performs the following tests:
- ADC read
- GPIO flash red, green, and blue LEDs
- I2C Read od 'WHO_AM_I' register from accelerometer chip
- SPI transfer
"""

import iot_hw
import time


def test_i2c():
    print('Test I2C')
    dev = 0x19     # i2c address of LIS2DW12 accelerometer
    addr = [0x0f]    # WHO_AM_I register
    data = list()
    myi2c = iot_hw.i2c()
    myi2c.write(dev, addr, 1, iot_hw.i2c_flag.I2C_NO_STOP)
    myi2c.read(dev, data, 1)
    print('  I2C reg {0:#2x} value is: {1:#2x}'.format(addr[0], data[0]))


def test_spi():
    print('Test SPI')
    frequency = 960000
    tx_buffer = [
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0x40, 0x00, 0x00, 0x00, 0x00, 0x95,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xDE, 0xAD, 0xBE, 0xEF, 0xBA, 0xAD,
        0xF0, 0x0D]
    rx_buffer = list()
    myspi = iot_hw.spi(iot_hw.spi_bus.SPI_BUS_2)
    myspi.set_format(iot_hw.spi_mode.SPIMODE_CPOL_0_CPHA_0, iot_hw.spi_bpw.SPI_BPW_8)
    myspi.set_frequency(frequency)
    myspi.transfer(tx_buffer, rx_buffer, len(tx_buffer))
    print('  SPI rx_data value is:{}'.format(rx_buffer))


def test_leds():
    print('Test LEDs')
    leds = {"Red":iot_hw.gpio_pin.GPIO_LED_RED, "Green":iot_hw.gpio_pin.GPIO_LED_GREEN, "Blue":iot_hw.gpio_pin.GPIO_LED_BLUE}

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


def test_adc():
    print('Test ADC')
    myadc = iot_hw.adc()
    result = myadc.read()
    print('  ADC value:{0}'.format(result))
    myadc.close()


def main():
    test_adc()
    test_leds()
    test_i2c()
    test_spi()


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
