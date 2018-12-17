/**
 * @file main.c
 * @brief the main entry of demo application for host mode API.
 *
 * This program is just for a demo to test the API of host mode.
 * This sample code is a reference for customers who want to apply the host mode API.
 *
 * @copyright Copyright (c) 2016-2020 Wistron Neweb Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Wistron Neweb Technologies, Inc.
 *
 * @author Ophas
 * @bug No known bugs.
***************************************************************************************************/

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/syscall.h>
#include <pthread.h>

#include <hwlib/hwlib.h>

#define LOGD(fmt, ...)  fprintf( stdout, "TID:%ld, ""%s:"fmt, syscall(__NR_gettid), __FUNCTION__, ##__VA_ARGS__ )
typedef struct {
	gpio_pin_t pin_index;
	char pin_name[8];
} gpio_tbl;

const gpio_tbl const gpio_name_mapping[] = {
	{ GPIO_PIN_1, "GPIO 1" },
	{ GPIO_PIN_2, "GPIO 2" },
	{ GPIO_PIN_3, "GPIO 3" },
	{ GPIO_PIN_4, "GPIO 4" },
	{ GPIO_PIN_5, "GPIO 5" },
	{ GPIO_PIN_6, "GPIO 6" },
	{ GPIO_PIN_7, "GPIO 7" },
	{ GPIO_PIN_8, "GPIO 8" },
	{ GPIO_PIN_46, "GPIO 46" },
	{ GPIO_PIN_47, "GPIO 47" },
	{ GPIO_PIN_48, "GPIO 48" },
	{ GPIO_PIN_49, "GPIO 49" },
	{ GPIO_PIN_92, "GPIO 92" },
	{ GPIO_PIN_93, "GPIO 93" },
	{ GPIO_PIN_94, "GPIO 94" },
	{ GPIO_PIN_95, "GPIO 95" },
	{ GPIO_PIN_96, "GPIO 96" },
	{ GPIO_PIN_97, "GPIO 97" },
	{ GPIO_PIN_98, "GPIO 98" },
	{ GPIO_PIN_101, "GPIO 101" },
	{ GPIO_PIN_102, "GPIO 102" },
	{ GPIO_PIN_103, "GPIO 103" },
};

static int waiting_triggered = 1;
static char *str_gpio_name(gpio_pin_t pin)
{
	int i, found = 0;

	for ( i=0 ; i<GPIO_PIN_MAX ; i++ )
	{
		if ( gpio_name_mapping[i].pin_index == pin )
		{
			found = 1;
			break;
		}
	}
	if ( found )
		return gpio_name_mapping[i].pin_name;

	return NULL;
}

static int gpio98_irq_callback(gpio_pin_t pin_name, gpio_irq_trig_t direction)
{
	if (pin_name != GPIO_PIN_98)
		return 0;

	/* TODO:
	   Please implement what is supposed to be handled here.
	   This example is just change the state of waiting_triggered to make the main thread continue.
	*/
	waiting_triggered = 0;
	LOGD("===> GPIO 98 interrupt.\n");
	return 0;
}

/**
   Please connect GPIO 3 with GPIO 7.
   GPIO 3 is the trigger source of the interrupt of GPIO 7.
*/
int main(int argc, char *argv[])
{
	gpio_handle_t my_interrupt = NULL;
	gpio_handle_t my_output = NULL;
	int ret, countdown = 10000;	// Make sure coutdown is long enough.

	LOGD("Start GPIO test.\n");

	// Set up a trigger source.
	LOGD("Set up output LED for GPIO 101.\n");
	gpio_init(GPIO_PIN_101, &my_output);
	gpio_dir(my_output, GPIO_DIR_OUTPUT);
	gpio_write(my_output, GPIO_LEVEL_HIGH);

	// Create the instance.
	LOGD("Create a control point instances for GPIO 98.\n");
	if ( (ret = gpio_init(GPIO_PIN_98, &my_interrupt)) != 0 )
	{
		LOGD("%s is initialized with failure:%d \n", str_gpio_name(GPIO_PIN_98), ret);
		exit(-1);
	}

	// Set GPIO direction.
	LOGD("Set GPIO 98 to be an input pin.\n");
	if ( (ret = gpio_dir(my_interrupt, GPIO_DIR_INPUT) != 0) )
	{
		LOGD("%s can't be set to be an input pin, ret:%d \n", str_gpio_name(GPIO_PIN_98), ret);
		exit(-1);
	}

	// Set GPIO 7 to be interruptable.
	LOGD("Set up a trigger source from GPIO 98.");
	if ( (ret = gpio_irq_request(my_interrupt, GPIO_IRQ_TRIG_FALLING, gpio98_irq_callback) != 0) )
	{
		LOGD("%s can't be set to be an interrupt pin, ret:%d \n", str_gpio_name(GPIO_PIN_98), ret);
		exit(-1);
	}

	/* TODO:
	   Put the implementation of main function here, such as dispatch of events, event handlings... 
	   This simple example is just waiting a changing state of waiting_triggered
	   without consideration about variable synchronization.
	*/
	while (waiting_triggered)
	{
		LOGD("waiting for the interrupt...\n");
		if (countdown == 0)
		{
			gpio_write(my_output, GPIO_LEVEL_LOW);
		}
		countdown--;
		pause();
	}

	LOGD("Interrupt is coming...\n");

	// Finally, before quiting the main function, release the GPIO resource
	gpio_irq_free(my_interrupt);
	gpio_deinit(&my_interrupt);
	gpio_deinit(&my_output);
	exit(0);
}

