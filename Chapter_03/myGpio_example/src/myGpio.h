
#ifndef __MYGPIO_H__
#define __MYGPIO_H__

// **** myGpio_t **************************************************************
typedef struct _myGpio {
    gpio_handle_t           hndl;       // Set to 0; will be initialized in myGpio_init()
    char                    abr[2];     // Used to provide user terminal feedback during myGpio_init()
    int                     nbr;        // Number of the GPIO pin being configured
    gpio_pin_t              pin;        // WNC SDK enumeration for specified pin
    gpio_direction_t        dir;        // Should myGpio_init() configure pin as input or output
    gpio_irq_trig_t         trig;       // If using pin as input interrupt, which trigger value enumeration should be configured
    gpio_irq_callback_fn_t  cback;      // If using pin as input interrupt, what function should be used for callback
    gpio_level_t            val;        // Can be used to hold the pin value when reading pin
	int			            ret;        // Return from gpio_init() function when called by myGpio_init(); it should be initialized to -1
	int			            irq;        // Return from gpio_irq_request() when called by myGpio_init(); it should be initialized to -1
} myGpio_t;

#ifdef __cplusplus
extern "C" {
#endif

extern myGpio_t myGpio[];
extern const int _max_gpio_pins;

int myGpio_init(void);
void myGpio_close(void);
int myGpio_irq_callback(gpio_pin_t, gpio_irq_trig_t);

#ifdef __cplusplus
}
#endif

#include <sys/types.h>
#include <stdint.h>
#include <nettle/nettle-stdint.h>
#include <hwlib/hwlib.h>

#endif // __MYGPIO_H__


