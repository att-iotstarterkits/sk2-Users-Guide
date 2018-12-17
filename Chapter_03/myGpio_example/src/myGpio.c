#include <stdio.h>
#include <stdlib.h>
#include <hwlib/hwlib.h>
#include "myGpio.h"

extern int doExit;

/******************************************************************************
* myGpio_t
*
* This structure indicates how the myGpio_init() routine should allocate and 
* configure the WNC M18Qx GPIO Linux drivers.
*
* hndl: Set to 0; will be initialized in myGpio_init()
* abr:   Used to provide user terminal feedback during myGpio_init()
* nbr:   Number of the GPIO pin being configured
* pin:   WNC SDK enumeration for specified pin
* dir:   Should myGpio_init() configure pin as input or output
* trig:  If using pin as input interrupt, which trigger value enumeration 
*        should be configured
* cback: If using pin as input interrupt, what function should be used 
*        for callback
* val:   Can be used to hold the pin value when reading pin
* ret:   Return from gpio_init() function when called by myGpio_init(); 
*        it should be initialized to -1
* irq:   Return from gpio_irq_request() when called by myGpio_init(); 
*        it should be initialized to -1
*
******************************************************************************/
myGpio_t myGpio[] = {

//  hndl  abr   nbr   pin            dir               trig                    cback                val  ret  irq  comment
//  ----  ---   ---   ------------   ----------------  ----------------------  ------------------   ---  ---  ---  ---------------------
    0,    "R",  92,   GPIO_PIN_92,   GPIO_DIR_OUTPUT,  -1,                     0,                   0,   -1,  -1,  // Red LED
    0,    "G",  101,  GPIO_PIN_101,  GPIO_DIR_OUTPUT,  -1,                     0,                   0,   -1,  -1,  // Green LED
    0,    "B",  102,  GPIO_PIN_102,  GPIO_DIR_OUTPUT,  -1,                     0,                   0,   -1,  -1,  // Blue LED
    0,    "S",  98,   GPIO_PIN_98,   GPIO_DIR_INPUT,   GPIO_IRQ_TRIG_FALLING,  myGpio_irq_callback, 0,   -1,  -1   // User Button Switch
};

#define _MAX_GPIO	    (sizeof(gpio)/sizeof(myGpio_t))
#define _MAX_GPIO_PINS	(sizeof(myGpio)/sizeof(myGpio_t))
const int _max_gpio_pins = _MAX_GPIO_PINS;


// ****  Simple example of a GPIO interrupt callback routine  *****************
//
int myGpio_irq_callback(gpio_pin_t pin_name, gpio_irq_trig_t direction) 
{
    if (pin_name != myGpio[3].pin)
        return 0;

    doExit = 0;
    printf("\nInterrupt occurred on %d! Now exiting...\n\n", myGpio[3].nbr);
}


// **** myGpio_init() *********************************************************
// Initialize all the binary i/o pins in the system
int myGpio_init(void)
{
    int ret;
	int i     = 0;
    int error = 0;

    // Loop thru myGpio[] allocating required pins
    printf("GPIO allocation (%d pins):\n", _max_gpio_pins);

    for ( i=0; i < _max_gpio_pins; i++ )
    {
        myGpio[i].ret = gpio_init( myGpio[i].pin, &myGpio[i].hndl );            // Call GPIO init API function
        printf("  %s=%d\n", myGpio[i].abr, myGpio[i].ret );

        if (myGpio[i].ret !=0)
        {
            printf("      --> ERROR: GPIO resource unavailable\n");
            error = 1;
        }
    }

    // Loop thru pins setting direction and irq
    printf("\nBeginning configuration of GPIO pins:\n");

    for ( i=0; i < _max_gpio_pins; i++ ) 
    {
        if (myGpio[i].ret == 0)
        {
            gpio_dir( myGpio[i].hndl, myGpio[i].dir );                          // We're not checking gpio_dir() return value

            if ((myGpio[i].dir = GPIO_DIR_INPUT) && (myGpio[i].trig != -1)) 
            {
                myGpio[i].irq = gpio_irq_request( myGpio[i].hndl, myGpio[i].trig, myGpio[i].cback );

                if (myGpio[i].irq == 0)
                {
                    printf("IRQ %d enabled\n", myGpio[i].nbr);
                } else
                {
                    printf("ERROR: GPIO %d IRQ unavailable\n\n", myGpio[i].nbr);
                    error = 1;
                }
            }
        } else
        {
            printf("--> Pin configuration skipped for %s (%d) since it failed allocation\n", myGpio[i].abr, myGpio[i].nbr);
        }
    }

    printf("GPIO configuration complete\n\n");
    return error;
}


// **** myGpio_close() ********************************************************
// Release the resources allocated by myGpio_init()
// Skip any resources that failed during allocation/configuration
void myGpio_close(void)
{
    int i = 0;

    printf("Releasing GPIO resources\n\n");

    for ( i=0; i < _max_gpio_pins; i++ ) 
    {
        if (myGpio[i].irq == 0)
        {
	        gpio_irq_free( myGpio[i].hndl );
        }

        if (myGpio[i].ret == 0)
        {
            gpio_deinit( &myGpio[i].hndl);
        }
    }
}



