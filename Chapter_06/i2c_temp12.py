from __future__ import print_function

"""
i2c_temp12.py

Read the 8-bit resolution and 12-bit resolution temperature register from the
LIS2DW12 sensor using the I2C bus.

"""

import iot_hw                                                                   # Required for GPIO and I2C drivers
import time                                                                     # Required for toggling GPIO

class LIS2DW12:                                                                 # Class used to define LIS2DW12 sensor registers & constants
    # LIS2DW12 registers
    OUT_T_L    = 0x0D                                                           # Lower 8-bits of 12-bit temp (lower 4-bits always read as 0)
    OUT_T_H    = 0x0E                                                           # Upper 8-bits of 12-bit temperature
    WHO_AM_I   = 0x0f                                                           # LIS2DW12 identification register (always reads as 0x44)
    CTRL1      = 0x20                                                           # Control Register 1
    CTRL3      = 0x22                                                           # Control Register 3
    OUT_T      = 0x26                                                           # 8-bit temperature value register
    STATUS_DUP = 0x37                                                           # Another status register (this one has temperature status bits)

    # Constants
    ID         = 0x44                                                           # Value read back from WHO_AM_I register

"""
val2hex()

If the input value is negative, its converted to a twos-complement signed
hex value. If the number is positive, the input value is returned.

Background:
    For a given radix (e.g. 8-bit numbers) signed and unsigned numbers provide
    the same resolution, although their min/max values change. For example, an
    8-bit   unsigned number range is 0 to 255, while the signed number range
    is -128 to 127.

    With this in mind, we can convert a negative unsigned number to its
    twos-complement equivelent by adding the range maximum (i.e. 128) to the
    difference between the input value and the maximum value.

Parameters:
    val = signed integer
    len = number of bits for output value

Returns:
    twos complement signed hex number

Note:
    No error handling is implemented in this function
"""
def val2hex(val, len):
    max = 2**(len-1)                                                            # Determine the maximum value based on radix bit length

    if val < 0:
        tc = max + val                                                          # Calculate the difference between the input value and max
        tc = tc + max                                                           # Add max to shift range
        #print('  ----> Value in: {0}; Hex: {1}'.format(val, hex(tc)))
        val = tc
    return val


"""
u2s()

If the input number is greater than the max value (based on the radix length)
then we can assume the number must be negative, in which case we convert it
to its signed value representation.

Parameters:
    uVal = input number
    len  = number of radix bits

Returns:
    twos complement signed hex number

Note:
    No error handling is implemented in this function
"""
def u2s(uVal, len):
    max = 2**len / 2                                                            # Determine the maximum value based on radix bit length
    sVal = uVal                                                                 # Set return value to the input value (in case it's positive)

    if uVal > max:                                                              # Check if number is greater than radix max (if so, it's negative)
        sVal = uVal - (2 * max)                                                 # Calculate the negative representation of the number
        #print('  ----> unsigned input: {0}; signed output: {1}'.format(uVal, sVal))
    return sVal


def Get_Temperature_i2c():
    print('\nGetting temperature from LIS2DW12 via I2C')
    # Define CONSTANTS
    DEV  = 0x19                                                                 # i2c device slave address for LIS2DW12 accelerometer
    HIGH = 0                                                                    # Index for 'high' byte of 12-bit temperature list
    LOW  = 1                                                                    # Index for 'low' byte of 12-bit temperature list

    # Allocate variables
    myi2c     = 0                                                               # Object returned from I2C open API
    i2cClosed = 0                                                               # Return variable from closing i2c bus API

    lis2dw12_id = list()                                                        # List variable for results from "WHO_AM_I" register
    raw_temp_08 = list()                                                        # List variable for reading 8-bit temperature register
    raw_temp_12 = list()                                                        # List variable for reading 12-bit temperature register
    hex_temp_12 = [0, 0]                                                        # Temporary list for holding 12-bit hex values
    str_temp_12 = ['', '']                                                      # Temporary string for holding 12-bit hex-string values
    temp_rdy    = list()                                                        # List variable for polling status register

    x = 0                                                                       # For-loop variable
    r = 0                                                                       # Masked ready bit (is temperature value ready?)
    temp12_string = 0                                                           # String variable to hold full 12-bit (concatenated) temperature
    uTemp12 = 0                                                                 # Temporary variable to hold Unsigned integer conversion
    sTemp12 = 0                                                                 # Temporary variable to hold Signed integer conversion

    tempC08 = 0                                                                 # Variables for 8-bit Celsius and Fahrenheit temperature
    tempF08 = 0
    tempC12 = 0                                                                 # Variables for 12-bit Celsius and Fahrenheit
    tempF12 = 0


    print('  Initializing LIS2DW12 for temperature reading:')
    # Initialize i2c bus
    myi2c = iot_hw.i2c()                                                        # Initialize (i.e. open) the i2c bus protocol
    print('  -> I2C bus initialized')

    # Get device_id from LIS2DW12 WHO_AM_I register (not required, but the first thing we tried when using this sensor
    myi2c.write(DEV, [LIS2DW12.WHO_AM_I], 1, iot_hw.i2c_flag.I2C_NO_STOP)       # Write request to WHO_AM_I register
    myi2c.read(DEV, lis2dw12_id, 1)                                             # Read data from the WHO_AM_I register
    print('  -> WHO_AM_I = {0:#2x} (should be {1:#2x})'.format(lis2dw12_id[0], LIS2DW12.ID))

    # Write configuration Control Register 1 (CTRL1)
    myi2c.write(DEV, [LIS2DW12.CTRL1, 0x6B], 2, iot_hw.i2c_flag.I2C_NO_STOP)    # Write request to CTRL1 register
    print('  -> CTRL1 written - 200Hz, single conversion, LPM4')

    # Trigger temperature sampling/conversion via CTRL3 register
    myi2c.write(DEV, [LIS2DW12.CTRL3, 0x03], 2, iot_hw.i2c_flag.I2C_NO_STOP)    # Write request to CTRL3 register
    print('  -> CTRL3 written - Trigger temperature sampling')

    # Wait until temperature is ready and then read temperature (8b and 12b)
    # Abort if temp not ready after polling ready bit 15 times
    print('\n  Poll temp status bit (looking for 0x4x)')
    for x in range(0, 15):
        myi2c.write(DEV, [LIS2DW12.STATUS_DUP], 1, iot_hw.i2c_flag.I2C_NO_STOP) # Check status of Temperature data
        myi2c.read(DEV, temp_rdy, 1)    # Read data
        print('  -> Read STATUS_DUP reg ({0:#2x}): {1:#2x}'.format(LIS2DW12.STATUS_DUP, temp_rdy[x]))
        r = temp_rdy[x] & 0x40                                                  # if DRDY_T bit is set, read the temperature
        if r > 0:
            # Get 8-bit temperature value (one I2C read)
            myi2c.write(DEV, [LIS2DW12.OUT_T], 1, iot_hw.i2c_flag.I2C_STOP)     # Write request to OUT_T (temperature) register
            myi2c.read(DEV, raw_temp_08, 1)                                     # Read 8-bit temp data from the OUT_T register
            print('\n  The raw 8-bit temp sensor reading is: {0}\n'.format(raw_temp_08[0]))

            # Get 12-bit temperature data (two I2C reads - high byte, then low)
            myi2c.write(DEV, [LIS2DW12.OUT_T_H], 1, iot_hw.i2c_flag.I2C_STOP)   # Write request to OUT_T (temperature) register
            myi2c.read(DEV, raw_temp_12, 1)                                     # Read 12b (high) temp data from the OUT_T_H register
            myi2c.write(DEV, [LIS2DW12.OUT_T_L], 1, iot_hw.i2c_flag.I2C_STOP)   # Write request to OUT_T (temperature) register
            myi2c.read(DEV, raw_temp_12, 1)                                     # Read 12b (low) temp data from the OUT_T_L register
            print('  The raw 12-bit temp sensor reading is: high={0}, low={1}'.format(raw_temp_12[HIGH], raw_temp_12[LOW]))

            # Call val2hex() for both high/low to get back to twos-complement value
            # Note that Python converts the number incorrectly (which can be validated by viewing i2c bus in logic analyzer)
            hex_temp_12[HIGH] = val2hex(raw_temp_12[HIGH], 8)
            hex_temp_12[LOW]  = val2hex(raw_temp_12[LOW],  8)
            print('  --> The 12-bit hex values: high={0:#2x}, low={1:#2x}'.format(hex_temp_12[HIGH], hex_temp_12[LOW]))

            # We convert the hex numbers to string representations
            str_temp_12[HIGH] = str(hex(hex_temp_12[HIGH]))[2:].rjust(2, '0')
            str_temp_12[LOW]  = str(hex(hex_temp_12[LOW]))[2:].rjust(2, '0')
            #print('  The 12-bit str values: high={0}, low={1}'.format(str_temp_12[HIGH], str_temp_12[LOW]))

            # We can easily concatenate the string versions of the two numbers
            temp12_string = '0x{0}{1}'.format(str_temp_12[HIGH], str_temp_12[LOW])
            temp12_string = temp12_string[:5]
            print('  --> Full 12-bit hex value = {0}'.format(temp12_string))

            # Next we change the full 12-bit string value back to integer and pass to u2s() to get back signed value
            uTemp12 = int(temp12_string, 16)
            sTemp12 = u2s(uTemp12, 12)
            print('  --> Full 12-bit unsigned value: {0}; signed value: {1}\n'.format(uTemp12, sTemp12))

            # Here's the calculation of the C and F temperatures for the 8-bit resolution
            tempC08 = raw_temp_08[0] + 25;
            tempF08 = (tempC08 * 9.0)/5.0 + 32;

            # Similarly, the calculation of C/F for the 12-bit number
            # Notice the extra "divide by 16" required to handle the extra 4 bits of precision
            tempC12 = sTemp12/16 + 25;
            tempF12 = (tempC12 * 9.0)/5.0 + 32;

            print('  Temp8 is  = {0} C or {1} F'.format(tempC08, tempF08))
            print('  Temp12 is = {0} C or {1} F'.format(tempC12, tempF12))

            # Break out of the polling loop if we successfully read and printed the temperature
            break

        # If x reaches 14, then we polled 15 times and failed to read the temperature
        if x == 14:
            print('\n(FAIL) Failed to get temperature...')

    i2cClosed = myi2c.close()                                                   # Close the i2c bus
    if i2cClosed:
        print('\n  i2c bus was closed')
    else:
        print('\n  FAILED to close i2c bus')
    print('\n')


def Blink_GPIO():
    print('\nBlink PMOD GPIO 95')

    leds      = {"Pmod95":iot_hw.gpio_pin.GPIO_PIN_95}                          # List of GPIOs to toggle
    myled     = 0                                                               # Object returned from GPIO open API

    for key in leds:                                                            # Sequence through all GPIO in 'leds' list
        myled = iot_hw.gpio(leds[key])                                          # Open each GPIO key
        myled.set_dir(iot_hw.gpio_direction.GPIO_DIR_OUTPUT)                    # Set direction to output
        print('  {} on'.format(key))

        myled.write(iot_hw.gpio_level.GPIO_LEVEL_HIGH)                          # Set GPIO high
        time.sleep(0.5)                                                         # Sleep for 1/2 second
        print('  {} off'.format(key))

        myled.write(iot_hw.gpio_level.GPIO_LEVEL_LOW)                           # Set GPIO low
        time.sleep(0.5)                                                         # Sleep for 1/2 second

        myled.close()                                                           # Close the driver for that GPIO key


def main():
    print('\nNow running file: i2c_temp12.y')
    Blink_GPIO()
    Get_Temperature_i2c()


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
