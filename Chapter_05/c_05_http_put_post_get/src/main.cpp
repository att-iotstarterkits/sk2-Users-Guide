#include <stdio.h>
#include "mal.hpp"
#include "iot_monitor.h"
#include <unistd.h>                                                             // Needed for sleep(), usleep()
#include "wwan_status.hpp"
#include "http.h"
#include <stdlib.h>

#define URL "https://hookb.in/yDWeM688m0hO7OPzw8MD"                             // "https://hookb.in/0366yL2jz6cQmNBnrdPq"


int c;
sysinfo  mySystem;                                                              // Get system info from MAL
wwanInfo myWwan;                                                                // Get wwan info from MAL
netInfo  myNetw;                                                                // Get network info from MAL
unsigned int dbg_flag = 0;
json_keyval wwanStatus[20];                                                     // Retain JSON key/value pairs for wwan info
json_keyval networkStatus[20];                                                  // Retain JSON key/value pairs for network info

int main(void) {
    // Return variables from function calls
    int  ret;
    char rbuf[ RXMSG_SIZE ];
    char response[10024];                                                       // Response from http_get

    // Buffers for passing parameters to HTTP functions
    char url[100];                                                              // Buffer for dynamically created URLs
    char data[80];                                                              // Buffer for dynamically created data strings

    char hdr0[64];                                                              // Buffers for up to 10 HTTP header strings
    char hdr1[64];
    char hdr2[64];
    char hdr3[64];
    char hdr4[64];
    char hdr5[64];
    char hdr6[64];
    char hdr7[64];
    char hdr8[64];
    char hdr9[64];
    char *h[10]={'\0'};                                                         // Array of HTTP header strings (to pass to functions)

    // Key/value pairs for parsing json
    int  i, p;
    json_keyval om[20];                                                         // JSON key/value pairs for MAL system info

    printf("Hello World\n");

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

    WWANStatus(&myWwan, &myNetw);

    // Create headers for HTTP transaction
    sprintf(hdr0, "Content-Type: application/json");
    sprintf(hdr1, "Example: Header Info");
    h[0] = hdr0;
    h[1] = hdr1;

    // Create data for HTTP Transaction
    sprintf(data, "Connection Time = %s\n", myNetw.connTime.c_str());

    // Do HTTP PUT
    printf("\nNow starting http put...\n");
    ret = do_http_put(URL, 2, h, data);

    // Do HTTP POST
    printf("\nNow starting http post...\n");
    ret = do_http_post(URL, 2, h, data, rbuf);
    printf("%s\n", rbuf);

    // Do HTTP GET
    printf("\nNow starting http get...\n");
    do_http_get(URL, 2, h, data, response, sizeof(response));
    printf("Response: %s\n", response);

    printf("\nProgram is exiting... \n");
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