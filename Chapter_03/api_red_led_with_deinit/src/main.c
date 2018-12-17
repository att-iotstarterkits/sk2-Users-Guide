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
