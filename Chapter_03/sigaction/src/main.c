#include <signal.h>                                                             // Needed for sigaction()
#include <stdio.h>                                                              // Needed for printf()
#include <unistd.h>                                                             // Needed for sleep()
#include <stdlib.h>                                                             // Needed for exit()

int flag    = 0;
int lastSig = 0;

void ouch(int sig)                                                              // First pass SIGINT handler
{
    flag    = 1;
    lastSig = sig;
}

void quit(int sig)                                                              // Second pass SIGINT handler
{
    flag    = 3;
}

int main()
{
    struct sigaction act;                                                       // ‘action’ struct for signal

    act.sa_handler = ouch;                                                      // Callback function is 'ouch'
    sigemptyset(&act.sa_mask);                                                  // Don’t block any signals in handler
    act.sa_flags = 0;                                                           // No signal action modifiers

    sigaction(SIGINT, &act, 0);                                                 // Set action for SIGINT signal

    while(1) {
        switch(flag)                                                            // Respond to value of 'flag'
        {
            case 0:
            case 2:
                printf("Hello World!\n");
                sleep(1);
                break;
            case 1:
                printf("\nOUCH! - I got signal %d\n", lastSig);
                act.sa_handler = quit;                                          // Could have also set handler to SIG_DFL rather than using quit()
                sigaction(SIGINT, &act, 0);                                     // Set new action for SIGINT
                flag = 2;
                break;
            case 3:
                printf("\nOUCH again. This time it's Goodbye!\n");
                exit(0);
                break;
            default:
                printf("Don't know how I got here... exiting\n");
                exit(1);
        }
    }
}

