#include <stdio.h>
#include "mal.hpp"
#include "iot_monitor.h"
#include <unistd.h>                                                             // Needed for sleep(), usleep()
#include "wwan_status.hpp"
#include "http.h"
#include <stdlib.h>

#define M2X_BASE_URL        "http://api-m2x.att.com/v2"
#define M2X_DEVICES_URL     "http://api-m2x.att.com/v2/devices"
#define M2X_API_KEY         "b2762079a8b9115e0f11060b5d73098a"
#define M2X_DEVICE_NAME     "CTEST"
#define M2X_STREAM_NAME     "temp"
#define M2X_DEVICE_DESCR    "Trying CreateDevice() from C program"
#define M2X_VISIBILITY      "private"

typedef struct m2x_device_t {                                                   // Keep track of M2X device information
    char *name;
    char *id;
    char *serial;
    char *status;
    char *key;
    char *visibility;
    char *description;
    char *streamCount;
} m2x_device_t;

typedef struct m2x_stream_t {                                                   // Keep track of M2X stream name
    char *name;
} m2x_stream_t;

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

    // M2X device variables
    m2x_device_t devices[10];                                                   // Only '10' since trial user accounts only allow 10 devices
    int d = -1;                                                                 // Index of active M2X device
    int dev = 0;                                                                // # of M2X devices
    int skipDev = 0;                                                            // Active device has already been created
    char *found;                                                                // Symbolizes a found device or stream in printout

    // M2X stream variables
    m2x_stream_t streams[15];                                                   // Arbitrarily picked '15' streams
    int s = -1;                                                                 // Index of active M2X stream
    int str = 0;                                                                // # of M2X streams
    int skipStream = 0;                                                         // Active stream has already been created

    // Key/value pairs for parsing json
    int  i, p;
    json_keyval om[20];                                                         // JSON key/value pairs for MAL system info
    json_keyval odl[256];                                                       // JSON key/value pairs for M2X device list response
    json_keyval od[256];                                                        // JSON key/value pairs for M2X create device response
    json_keyval osl[256];                                                       // JSON key/value pairs for M2X stream list response
    json_keyval os[256];                                                        // JSON key/value pairs for M2X create stream list

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
    sprintf(hdr1, "X-M2X-KEY: %s", M2X_API_KEY);//68275425291c587c0555ad483de920df
    sprintf(hdr2, "Accept: */*");
    h[0] = hdr0;
    h[1] = hdr1;
    h[2] = hdr2;

    // Create data for HTTP Transaction
    sprintf(data, "Connection Time = %s\n", myNetw.connTime.c_str());

    // Do M2X Get Devices
    printf("\nNow starting 'Get M2x Devices'...\n");
    do_http_get(M2X_DEVICES_URL, 3, h, data, response, sizeof(response));

    i = parse_maljson (response, odl, sizeof(odl));
    if( i > 0 ) {
        for (p = 0; p < i; p++) {
            if (strstr(odl[p].key, "name")) {
                devices[dev].name = odl[p].value;
                if (strstr(devices[dev].name, M2X_DEVICE_NAME))
                    skipDev = 1;
                    d = dev;
            }
            if (strstr(odl[p].key, "id"))
                devices[dev].id = odl[p].value;
            if (strstr(odl[p].key, "status"))
                devices[dev].status = odl[p].value;
            if (strstr(odl[p].key, "key"))
                devices[dev].key = odl[p].value;
            if (strstr(odl[p].key, "visibility"))
                devices[dev].visibility = odl[p].value;
            if (strstr(odl[p].key, "description"))
                devices[dev].description = odl[p].value;
            if (strstr(odl[p].key, "count")) {
                devices[dev].streamCount = odl[p].value;
                dev++;
            }
        }

        printf("\nHere's a list of M2X devices for this account:\n");
        for (p = 0; p < dev; p++) {
            if (p == d)
                found = (char *) " (*)";
            else
                found = (char *) " ";
            printf("M2X Device (%d): %s%s\n", p, devices[p].name, found);
            //printf("M2X Device: %s (%s, %s, %s, %s)\n", devices[p].name, devices[p].id, devices[p].status, devices[p].key, devices[p].streamCount);
        }
    }
    else {
        printf("Parse error - name (%d)\n", i);
        printf("\nDump:\n%s\n", response);
    }


    // Do Create Device
    printf("\nNow starting 'Create M2X Device' (%d)...\n", skipDev);

    if (skipDev) {
        printf("Device %s already exists, so it won't be created (dev=%d)(d=%d)\n", M2X_DEVICE_NAME, dev, d);
    }
    else {
        devices[dev].name =        (char *) M2X_DEVICE_NAME;
        devices[dev].visibility =  (char *) M2X_VISIBILITY;
        devices[dev].description = (char *) M2X_DEVICE_DESCR;

        sprintf(data, "{ \"name\": \"%s\", \"description\": \"%s\", "
                             "\"visibility\":\"%s\" }",  devices[dev].name, devices[dev].description, devices[dev].visibility);
        //printf("%s\n", data);

        ret = do_http_post(M2X_DEVICES_URL, 2, h, data, rbuf);

        i = parse_maljson (rbuf, od, sizeof(od));
        if( i > 0 ) {

            for (p = 0; p < i; p++) {
                if (strstr(od[p].key, "id")) {
                    devices[dev].id = od[p].value;
                    printf("\nNew M2X Device name (id): %s (%s)\n", devices[dev].name, devices[dev].id);
                    d = dev;
                }
            }
        }
        else {
            printf("\nParse error - id\n");
            printf("%s\n", rbuf);
        }

        dev++;
    }

    // Get the device's stream names
    printf("\nNow starting 'Get M2x Streams' (%d)...\n", d);

    memset(url, 0, sizeof(url));
    sprintf(url, "%s/%s/streams", M2X_DEVICES_URL, devices[d].id);
    //printf ("URL: %s\n", url);

    do_http_get(url, 3, h, data, response, sizeof(response));

    i = parse_maljson (response, osl, sizeof(osl));
    if( i > 0 ) {
        for (p = 0; p < i; p++) {
            if (strstr(osl[p].key, "display_name")) {
                //printf("Display name\n");
            } else if (strstr(osl[p].key, "name")) {
                streams[str].name = osl[p].value;
                if (strstr(streams[str].name, M2X_STREAM_NAME)) {
                    skipStream = 1;
                    s = str;
                }
                str++;
            }
        }

        printf("\nHere's a list of streams (%d) for this device (%s):\n", str, devices[d].name);
        for (p = 0; p < str; p++) {
            if (p == s)
                found = (char *) " (*)";
            else
                found = (char *) " ";
            printf("M2X Stream: %s%s\n", streams[p].name, found);
        }
    }
    else {
        printf("Parse error - name (%d)\n", i);
        printf("\nDump:\n%s\n", response);
    }


    // Do Create Stream
    printf("\nNow starting 'Create M2X Stream' (%d)...\n", d);

    if (skipStream) {
        printf("Stream %s (for device=%s) already exists, so it won't be created (str=%d)(d=%d)(s=%d)\n", M2X_STREAM_NAME, devices[d].name, str, d, s );
    }
    else {
        ret = m2x_create_stream( devices[d].id, M2X_API_KEY, M2X_STREAM_NAME);
        printf("Create stream return value: %d\n", ret);
    }

    // Add Value to the Stream
    printf("\nNow starting 'Post Value to M2X Stream'...\n");

    ret = m2x_update_stream_value( devices[d].id, M2X_API_KEY, M2X_STREAM_NAME, "2");  // '2' was chosen arbitrarily
    printf("Return from update stream value: %d\n", ret);

    printf("\nProgram is exiting... \n");
    return 0;
}

/* =====================================================================
   Copyright © 2018, AT&T (R)

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