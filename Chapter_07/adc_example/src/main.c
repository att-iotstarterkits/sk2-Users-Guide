#include <stdint.h>
#include <stdio.h>                                                              // Needed for printf()
#include <unistd.h>                                                             // Needed for usleep()
#include <stdlib.h>                                                             // Needed for exit()
#include <hwlib/hwlib.h>                                                        // Needed for WNCSDK GPIO API

#define LED_RED         GPIO_PIN_92
#define LED_GREEN       GPIO_PIN_101
#define LED_BLUE        GPIO_PIN_102
#define USER_BUTTON     GPIO_PIN_98

#define SECOND          1000000
#define NUM_BLINKS      3

void do_adc(void)
{
    adc_handle_t my_adc=(adc_handle_t)NULL;
    float adc_voltage;
    char str_adc_voltage[16];

    adc_init(&my_adc);
    adc_read(my_adc, &adc_voltage);

    memset(str_adc_voltage, 0, sizeof(str_adc_voltage));
    sprintf(str_adc_voltage, "%f", adc_voltage);

    adc_deinit(&my_adc);
    printf("ADC Data = %s\n", str_adc_voltage);
}

int main(void) {
    int i = 0;                                                                  // loop counter
    int ret;                                                                    // return value
    gpio_handle_t   myGpio;                                                     // GPIO pin handle

    printf("Hello Gpio\n");

    // Initialize GPIO for Red LED
    ret = gpio_init( LED_RED, &myGpio );                                        // GPIO call to initialize RED LED
    if (ret != 0) {                                                             // gpio_init() returns '0' upon successful completion
        printf("ABORT: Could not initialize Red LED (ret = %d)\n", ret);
        exit(1);
    }
    gpio_dir(myGpio, GPIO_DIR_OUTPUT);                                          // Set direction of GPIO pin to 'output'


    do_adc();

    // Blink LED NUM_BLINKS times
    for ( i = 0; i < NUM_BLINKS; i++ )
    {
        gpio_write( myGpio, GPIO_LEVEL_HIGH );                                  // Turn on the Red LED
        usleep( 1 * SECOND );                                                   // Wait 1 second

        gpio_write( myGpio, GPIO_LEVEL_LOW );                                   // Turn off the Red LED
        usleep( 1 * SECOND );                                                   // Wait 1 second
    }

    gpio_deinit( &myGpio );                                                     // Release the GPIO resource

    return 0;
}

