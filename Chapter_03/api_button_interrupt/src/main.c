#include <stdint.h>
#include <stdio.h>                                                              // Needed for printf()
#include <stdlib.h>                                                             // Needed for exit()
#include <unistd.h>                                                             // Needed for pause()
#include <hwlib/hwlib.h>                                                        // Needed for WNCSDK GPIO API

#define USER_BUTTON     GPIO_PIN_98

int        exitFlag = 0;                                                        // Exit flag
int             ret = 0;                                                        // Return value
gpio_handle_t myBtn = 0;                                                        // handle for button's GPIO pin


//*****  GPIO callback routine  ***********************************************
int myBtn_irq_callback(gpio_pin_t pin_name, gpio_irq_trig_t direction) {
    if (pin_name == USER_BUTTON)
    {
        printf("Button interrupt received\n");
    }
}

//*****  Main  ****************************************************************
int main(void)
{
    printf("\nStarting GPIO Callback Example!\n");
    printf("Please wait while we configure your device...\n");

    // Allocate and configure GPIO pin for User Pushbutton switch
    ret = gpio_init( USER_BUTTON, &myBtn );                                     // Allocate and initialize USER BUTTON
    if (ret != 0) {                                                             // gpio_init() returns '0' upon successful completion
        printf("ABORT: Could not initialize UserButton (ret = %d)\n", ret);
        exit(1);
    }
    gpio_dir(myBtn, GPIO_DIR_INPUT);                                            // Set direction of GPIO pin to 'input'
    gpio_irq_request(myBtn, GPIO_IRQ_TRIG_BOTH, myBtn_irq_callback);            // Register call back for GPIO pin interrupt

    // Now waiting for interrupt to occur
    printf("Device configuration complete.\n");
    printf("Press and release User Button to trigger interrupt.\n");

    pause();                                                                    // Wait for interrupt from user button

    // Release resources and exit
    printf("Releasing GPIO resources...\n");
    gpio_irq_free(myBtn);                                                       // Free the IRQ push button callback
    gpio_deinit( &myBtn );                                                      // Release the button's GPIO resource

    printf("\nGoodbye!\n");
    return 0;
}

