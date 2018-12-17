#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

void my_handler(sig_t s){
    printf("\nCaught signal %d\n",s);
    exit(1); 

}

int main(int argc,char** argv)
{
   signal (SIGINT, my_handler);

   while(1);
   return 0;

}

