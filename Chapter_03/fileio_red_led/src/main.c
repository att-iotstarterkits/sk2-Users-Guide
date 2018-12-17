#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define GPIO_EXPORT     "/sys/class/gpio/export"

#define GPIO_RED        38
#define GPIO_RED_DIR    "/sys/class/gpio/gpio38/direction"
#define GPIO_RED_LED    "/sys/class/gpio/gpio38/value"

#define GPIO_GREEN      21
#define GPIO_GREEN_DIR  "/sys/class/gpio/gpio21/direction"
#define GPIO_GREEN_LED  "/sys/class/gpio/gpio21/value"

#define GPIO_BLUE       22
#define GPIO_BLUE_DIR   "/sys/class/gpio/gpio22/direction"
#define GPIO_BLUE_LED   "/sys/class/gpio/gpio22/value"

#define OFF             0
#define ON              1

#define SECOND          1000000

#define FCHECK(f, err)  {                    \
                            if(f == NULL)    \
                            {                \
                               printf(err);  \
                               exit(1);      \
                            }                \
                        }

int main(void)
{
    int count;
    int max = 4;
    FILE *fptr;

    // Open GPIO #38 (red) for use by exporting to user space
    fptr = fopen(GPIO_EXPORT,"w");
    FCHECK(fptr, "Error opening export!");
    fprintf(fptr,"%d", GPIO_RED);
    fclose(fptr);

    // Set direction for GPIO #38 (red)
    fptr = fopen(GPIO_RED_DIR,"w");
    FCHECK(fptr, "Error opening direction!");
    fprintf(fptr,"out");
    fclose(fptr);

    // Turn off Red LED
    fptr = fopen(GPIO_RED_LED,"w");
    FCHECK(fptr, "Error opening LED 'value'");
    fprintf(fptr,"%d", OFF);
    fclose(fptr);

    // Blink Red LED 'count' times
    for(count = 1; count <= max; ++count)
    {
        printf("On\n");
        fptr = fopen(GPIO_RED_LED,"w");
        FCHECK(fptr, "Error opening LED 'value'");
        fprintf(fptr,"%d", ON);
        fclose(fptr);
        usleep(1 * SECOND);

        printf("Off\n");
        fptr = fopen(GPIO_RED_LED,"w");
        FCHECK(fptr, "Error opening LED 'value'");
        fprintf(fptr,"%d", OFF);
        fclose(fptr);
        usleep(1 * SECOND);
    }

    return 0;
}

