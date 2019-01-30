#include <stdio.h>
#include "iot_monitor.h"
#include "mal.hpp"
#include <unistd.h>                                                             // Needed for sleep(), usleep()
#include "wwan_status.hpp"
#include <stdlib.h>


// Replace URL with your Endpoint from AT&T Flow
#define URL "https://runm-west.att.io/e9215af2b0eea/8374c4f23615/fa5e6ab1a408526/in/flow/me"

// GPIO defines and macros
#define GPIO_EXPORT     "/sys/class/gpio/export"
#define GPIO_UNEXPORT   "/sys/class/gpio/unexport"

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

#define FCHECK(f, err)  {                                           \
                            if(f == NULL)                           \
                            {                                       \
                               printf("%s\n", err);                 \
                               exit(1);                             \
                            }                                       \
                        }

// Set value for LED (c=color, v=value, f=file pointer)
#define LED(c,v,f,e)     {                                          \
                            f = fopen(c,"w");                       \
                            FCHECK(f, e);                           \
                            fprintf(f,"%d", v);                     \
                            fclose(f);                              \
                        }

// Set direction for GPIO (p=pin, d=direction, f=file, e=error)
#define GPIO_DIR(p,d,f,e) {                                         \
                            f = fopen(p,"w");                       \
                            FCHECK(f, e);                           \
                            fprintf(f, d);                          \
                            fclose(f);                              \
                        }

#define EXPORT(f,g,s)   {                                           \
                            f = fopen(GPIO_EXPORT,"w");             \
                            FCHECK(fptr, "Error opening export!");  \
                            fprintf(f,"%d", g);                     \
                            fclose(f);                              \
                            printf("  Exported %s (#%d)\n", s, g);  \
                        }

#define UNEXPORT(f,g,s) {                                           \
                            f = fopen(GPIO_UNEXPORT,"w");           \
                            FCHECK(fptr, "Error opening export!");  \
                            fprintf(f,"%d", g);                     \
                            fclose(f);                              \
                            printf("  Unexported %s (#%d)\n", s, g);\
                        }

int c;
sysinfo  mySystem;                                                              // Get system info from MAL
unsigned int dbg_flag = 0;
json_keyval wwanStatus[20];                                                     // Retain JSON key/value pairs for wwan info
json_keyval networkStatus[20];                                                  // Retain JSON key/value pairs for network info


int main(void) {
     FILE *fp;
     char *command;

    // GPIO initialization objects
    FILE *fptr;

    // Return variables from function calls
    int  ret;
    char rbuf[ RXMSG_SIZE ];

    // Buffers for passing parameters to HTTP functions
    int  value;
    char cmd[512];                                                              // Buffer for curl command to send data to Flow
    char data[80];                                                              // Buffer to hold data being sent to Flow

    // Key/value pairs for parsing json
    int  i, p;
    json_keyval om[20];                                                         // JSON key/value pairs for MAL system info

    printf("Hello World\n");

    // Allocate and initialize hardware resources
    printf("\nAllocating Hardware Resources...\n");
    EXPORT(fptr,GPIO_RED,   "-> Red LED");                                      // Open GPIO #38 (red) for use by exporting to user space
    EXPORT(fptr,GPIO_GREEN, "-> Green LED");
    EXPORT(fptr,GPIO_BLUE,  "-> Blue LED");

    GPIO_DIR(GPIO_RED_DIR,  "out",fptr,"Error: red/dir");                       // Set direction for GPIO #38 (red)
    GPIO_DIR(GPIO_GREEN_DIR,"out",fptr,"Error: blue/dir");                      // Set direction for GPIO #21 (green)
    GPIO_DIR(GPIO_BLUE_DIR, "out",fptr,"Error: green/dir");                     // Set direction for GPIO #22 (blue)

    LED(GPIO_RED_LED,   OFF, fptr, "Error: red/off");                           // Turn off Red LED
    LED(GPIO_GREEN_LED, OFF, fptr, "Error: green/off");
    LED(GPIO_BLUE_LED,  OFF, fptr, "Error: blue/off");

    //  Configure psuedo-random generator
    srand(time(NULL));                                                          // Initialization for rand(); should only be called once

    // Start data service and get system information
    c = start_data_service();

    while ( c < 0 ) {
        printf("WAIT: starting WNC Data Module (%d)\n",c);
        sleep(10);
        c = start_data_service();
    }

    printf("\nData service running\n\n");

    do
        mySystem.model=getModelID(om, sizeof(om));
    while( mySystem.model == "service is not ready");

    mySystem.firmVer   = getFirmwareVersion(om, sizeof(om));
    mySystem.appsVer   = getAppsVersion(om, sizeof(om));
    mySystem.malwarVer = getMALManVer(om, sizeof(om));
    mySystem.ip        = get_ipAddr(om, sizeof(om));
    mySystem.iccid     = getICCID(om, sizeof(om));
    mySystem.imei      = getIMEI(om, sizeof(om));
    mySystem.imsi      = getIMSI(om, sizeof(om));

    printf("System Information \n");
    printf("==============================================================\n");
    printf("WNC: Module   #    = %s\n", mySystem.model.c_str());
    printf("WNC: Apps Ver #    = %s\n", mySystem.appsVer.c_str());
    printf("WNC: Firmware #    = %s\n", mySystem.firmVer.c_str());
    printf("WNC: MAL Ver. #    = %s\n", mySystem.malwarVer.c_str());
    printf("WNC: IP Addr. #    = %s\n", mySystem.ip.c_str());
    printf("SIM: ICCID    #    = %s\n", mySystem.iccid.c_str());
    printf("SIM: IMEA     #    = %s\n", mySystem.imei.c_str());
    printf("SIM: IMSI     #    = %s\n\n",mySystem.imsi.c_str());


    // Create data to send to Flow
    value = rand();                                                             // returns a pseudo-random integer
    printf("Random value = %d\n", value);

    // Create cURL command
    sprintf(cmd, "curl -X POST %s -d \"value=%d\"", URL, value);
    
    // Run the cURL comamnd in a subprocess and pipe the response to rbuf
    printf("\nSending the data to Flow using the following command\ncmd= %s\n", cmd);
    printf("--------------------\n");

    if ((fp = popen(cmd, "r")) != NULL) {
        while (fgets(rbuf, BUFSIZ, fp) != NULL)

        printf("--------------------\n");
        printf("Response = %s\n", rbuf);

        // Turn on correct LED
        if (strstr(rbuf, "blue")) {
            printf("\nTurning on Blue LED...\n");
            LED(GPIO_RED_LED,   OFF, fptr, "Error: red/off");
            LED(GPIO_GREEN_LED, OFF, fptr, "Error: green/off");
            LED(GPIO_BLUE_LED,  ON,  fptr, "Error: blue/on");
        } else if (strstr(rbuf, "green")) {
            printf("\nTurning on Green LED...\n");
            LED(GPIO_RED_LED,   OFF, fptr, "Error: red/off");
            LED(GPIO_GREEN_LED, ON,  fptr, "Error: green/on");
            LED(GPIO_BLUE_LED,  OFF, fptr, "Error: blue/off");
        } else {
            printf("\nError: Turning on Red LED...\n");
            LED(GPIO_RED_LED,   ON,  fptr, "Error: red/on");
            LED(GPIO_GREEN_LED, OFF, fptr, "Error: green/off");
            LED(GPIO_BLUE_LED,  OFF, fptr, "Error: blue/off");
        }
    } else {
        printf("\nError: Turning on Red LED...\n");
        LED(GPIO_RED_LED,   ON,  fptr, "Error: red/on");
        LED(GPIO_GREEN_LED, OFF, fptr, "Error: green/off");
        LED(GPIO_BLUE_LED,  OFF, fptr, "Error: blue/off");
    }

    // Release Hardware Resources
    printf("\nReleasing Hardware Resources...\n");
    UNEXPORT(fptr,GPIO_RED,   "-> Red");
    UNEXPORT(fptr,GPIO_GREEN, "-> Green");
    UNEXPORT(fptr,GPIO_BLUE, "-> Blue");

    printf("\nProgram is exiting... \n\n");
    return 0;
}

/* =====================================================================
   Copyright (c) 2018, AT&T (R)

   www.att.com 
 
   Licensed under the Apache License, Version 2.0 (the "License"); 
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, 
   software distributed under the License is distributed on an 
   "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, 
   either express or implied. See the License for the specific 
   language governing permissions and limitations under the License.
======================================================================== */
