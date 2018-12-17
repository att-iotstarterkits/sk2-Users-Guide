#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define GPIO_EXPORT     "/sys/class/gpio/export"
#define GPIO_UNEXPORT   "/sys/class/gpio/unexport"

#define GPIO_RED        38
#define GPIO_GREEN      21
#define GPIO_BLUE       22

#define FCHECK(f, err)  {                    \
                            if(f == NULL)    \
                            {                \
                               printf(err);  \
                               exit(1);      \
                            }                \
                        }

#define EXPORT(f,g,s)   {                                           \
                            f = fopen(GPIO_EXPORT,"w");             \
                            FCHECK(fptr, "Error opening export!");  \
                            fprintf(f,"%d", g);                     \
                            fclose(f);                              \
                            printf("Exported %s (#%d)\n", s, g);    \
                        }

int main(void)
{
    int num;
    FILE *fptr;

    printf("Which LED to 'export' (0: None, 1: Red, 2: Green; 3: Blue; 4: All): ");
    scanf("%d",&num);

    switch(num) {

       case 1  :
          EXPORT(fptr,GPIO_RED,"Red");
          break;
       case 2  :
          EXPORT(fptr,GPIO_GREEN, "Green");
          break;
       case 3  :
          EXPORT(fptr,GPIO_BLUE, "Blue");
          break;
       case 4  :
          EXPORT(fptr,GPIO_RED, "Red");
          EXPORT(fptr,GPIO_GREEN, "Green");
          EXPORT(fptr,GPIO_BLUE, "Blue");
          break;
    }

    return 0;
}

