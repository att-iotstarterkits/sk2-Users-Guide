#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define GPIO_EXPORT     "/sys/class/gpio/export"
#define GPIO_UNEXPORT   "/sys/class/gpio/unexport"

#define GPIO_RED        38
#define GPIO_GREEN      21
#define GPIO_BLUE       22
#define USER_BUTTON     23

#define FCHECK(f, err)  {                    \
                            if(f == NULL)    \
                            {                \
                               printf(err);  \
                               exit(1);      \
                            }                \
                        }

#define UNEXPORT(f,g,s) {                                           \
                            f = fopen(GPIO_UNEXPORT,"w");           \
                            FCHECK(fptr, "Error opening export!");  \
                            fprintf(f,"%d", g);                     \
                            fclose(f);                              \
                            printf("Unexported %s (#%d)\n", s, g);  \
                        }

int main(void)
{
    int num;
    FILE *fptr;

    printf("Which LED to 'unexport' (0: None, 1: Red, 2: Green; 3: Blue; 4: All): ");
    scanf("%d",&num);

    switch(num) {

       case 1  :
          UNEXPORT(fptr,GPIO_RED,"Red");
          break;
       case 2  :
          UNEXPORT(fptr,GPIO_GREEN, "Green");
          break;
       case 3  :
          UNEXPORT(fptr,GPIO_BLUE, "Blue");
          break;
       case 4  :
          UNEXPORT(fptr,GPIO_RED, "Red");
          UNEXPORT(fptr,GPIO_GREEN, "Green");
          UNEXPORT(fptr,GPIO_BLUE, "Blue");
          UNEXPORT(fptr,USER_BUTTON, "Button");
          break;
    }

    return 0;
}

