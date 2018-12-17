#include <stdint.h>
#include <signal.h>																// Needed for signal()/sigaction()
#include <stdlib.h>																// Needed for exit()
#include <stdio.h>                                                              // Needed for printf()
#include <unistd.h>                                                             // Needed for usleep() and pause()
#include <hwlib/hwlib.h>                                                        // Needed for WNCSDK GPIO API
#include "myGpio.h"

#define SECOND      1000000
#define NUM_LEDS    3

int doExit = 1;

// ****  SIGINT Handler for Control-C *****************************************
void my_handler(sig_t s)
{
	doExit = 0; 
	printf("\nCaught signal (%d). Quitting the program...\n",s);
}

// ****  main  ****************************************************************
int main(void) 
{
    int i = 0;                                                                  // Loop counter
	int r = 0;																	// Return value

    printf("\nWelcome to the myGpio example!\n");

	signal (SIGINT, my_handler);                                                // Register SIGINT signal handler

	r = myGpio_init();                                                          // Allocate and initialize the GPIO resources
	if (r)
		printf("Not all requested GPIO resources were allocated.\n");

    gpio_read(myGpio[3].hndl, &myGpio[3].val);                              	// Read and output the value of the User Button
    printf("Checking on the button's value. It is %d.\n", myGpio[3].val);

	printf("\nLED's will blink in color sequence until User Button is pushed.\n");
	printf("Alternatively, you can also press Cntrl-C to quit the program.\n");
    while(doExit)
	{
		// Blink all LEDs in sequence
		for ( i = 0; i < NUM_LEDS; i++ )
		{
			gpio_write( myGpio[i].hndl, GPIO_LEVEL_HIGH );                     	// Turn on LED
		    usleep( 1 * SECOND );                                               // Wait 1 second

			gpio_write( myGpio[i].hndl, GPIO_LEVEL_LOW );                      	// Turn off LED
		    usleep( 1 * SECOND );                                               // Wait 1 second
		}
	}

    myGpio_close();                                                             // Release the GPIO resources

    return 0;
}
