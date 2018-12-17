#include <stdint.h>
#include <stdio.h>                                                              // Needed for printf()
#include <unistd.h>                                                             // Needed for pause()
#include <stdlib.h>                                                             // Needed for exit()
#include <signal.h>                                                             // Needed for signal()
#include <hwlib/hwlib.h>                                                        // Needed for WNCSDK GPIO API

#define LED_RED         GPIO_PIN_92
#define LED_GREEN       GPIO_PIN_101
#define LED_BLUE        GPIO_PIN_102
#define USER_BUTTON     GPIO_PIN_98

int        exitFlag = 0;                                                        // Exit flag
int             ret = 0;                                                        // Return value
gpio_handle_t myBtn = 0;                                                        // handle for button's GPIO pin
gpio_handle_t myLed = 0;                                                        // Handle for LED's GPIO pin


//*****  GPIO callback routine  ***********************************************
int myBtn_irq_callback(gpio_pin_t pin_name, gpio_irq_trig_t direction) {
    if (pin_name != USER_BUTTON)
    {
        printf("Extraneous irq received (%d)\n", pin_name);
    }
    else
    {
        switch(direction)
        {
            case GPIO_IRQ_TRIG_FALLING:                                         // Falling signal means button was released
                printf("Up\n");
                gpio_write(myLed, GPIO_LEVEL_LOW);                              // Turn off LED
                break;
            case GPIO_IRQ_TRIG_RISING:                                          // Rising signal means button was pushed
                printf("\nDown\n");
                gpio_write(myLed, GPIO_LEVEL_HIGH);                             // Turn on LED
                break;
            default:
                printf("\n\nDon't know how I got here... exiting (dir=%d)\n", direction);
                exit(1);
        }
    }
}

//*****  Control-C Callback   *************************************************
void ctrl_c_handler(sig_t s){
    printf("\n\nCaught SIGINT signal (%d). Now exiting...\n",s);
    exitFlag = 1;
}

//*****  Main  ****************************************************************
int main(void)
{
    printf("\nStarting GPIO Callback Example!\n");
    printf("Please wait while we configure your device...\n");
    signal (SIGINT, ctrl_c_handler);

    // Allocate and configure GPIO pin for Blue LED
    ret = gpio_init( LED_BLUE, &myLed );                                        // Allocate and initialize LED
    if (ret != 0) {                                                             // gpio_init() returns '0' upon successful completion
        printf("ABORT: Could not initialize UserButton (ret = %d)\n", ret);
        exit(1);
    }
    gpio_dir(myLed, GPIO_DIR_OUTPUT);                                           // Set direction of GPIO pin to 'input'
    gpio_write(myLed, GPIO_LEVEL_LOW);                                          // Turn off LED

    // Allocate and configure GPIO pin for User Pushbutton switch
    ret = gpio_init( USER_BUTTON, &myBtn );                                     // Allocate and initialize USER BUTTON
    if (ret != 0) {                                                             // gpio_init() returns '0' upon successful completion
        printf("ABORT: Could not initialize UserButton (ret = %d)\n", ret);
        exit(1);
    }
    gpio_dir(myBtn, GPIO_DIR_INPUT);                                            // Set direction of GPIO pin to 'input'
    gpio_irq_request(myBtn, GPIO_IRQ_TRIG_BOTH, myBtn_irq_callback);            // Register call back for GPIO pin interrupt

    // Now waiting for interrupt to occur
    printf("Device configuration complete.\n\n");
    printf("Press the User Button to turn on the LED, release to turn off.\n");
    printf("Use Ctrl-C to exit the program\n");
    while(exitFlag == 0)
    {
        pause();                                                                // Wait for signal from user button
    }

    // Release resources and exit
    printf("Releasing GPIO resources...\n");
    gpio_irq_free(myBtn);                                                       // Free the IRQ push button callback
    gpio_deinit( &myBtn );                                                      // Release the button's GPIO resource
    gpio_deinit( &myLed );                                                      // Release the LEDs GPIO resource

    printf("\nGoodbye!\n");
    return 0;
}

