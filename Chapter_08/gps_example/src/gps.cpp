#include <cctype>
#include <cstddef>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <functional>
#include <math.h>

#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>

#include "gps.hpp"
#include "mal.hpp"

#include "iot_monitor.h"

// ***** Global Variables *****************************************************
int GPS_TO = 120;                                                               // GPS Time Out default is 120 seconds wait time to get GPS fix
struct timeval gps_start, gps_end;                                              // Used to measure duration of get_gps() call

// ****************************************************************************
// ascii_to_epoch()
//
// This function was copied from "demo.c" found in Avnet's IoT Monitor example
// because it was used by their GPS example code, but we didn't need the
// remaining parts of demo.c.
// ****************************************************************************
unsigned int ascii_to_epoch(char *epoch_ascii)
{
    unsigned long long int lepoch=0;
    unsigned long long int tens=1;
    unsigned int epoch;
    int asciilen, nbr;
    for( asciilen=strlen(epoch_ascii)-1; asciilen>=0; asciilen-- ) {
        nbr = epoch_ascii[asciilen] - 0x30;
        lepoch += (tens * nbr);
        tens *= 10;
        }
    return lepoch/1000;
}

// ****************************************************************************
// get_gps()
//
// Parameter: *gps - This gps_t structure (defined in gps.hpp) is passed into
//                   the function by reference. It is filled out with the GPS
//                   information and returned to the calling function.
//
// Return: val     - The function returns an integer indicating:
//                     -- returns 0 if successful
//                     -- reterns 1 if not successful
//
// The get_gps() function accesses the SK2 modem adaption layer (MAL) to get
// the location information. The data is printed to the console and passed
// back to the calling function via the pointer argument. The function returns
// an integer based on the success (or lack thereof) of the call.
//
// This function was adapted from two files found in Avnet's IoT Monitor
// example:
//                 - command_gps() from commands.cpp
//                 - GSP timeout logic from *check_gps() in facttest.cpp
// ****************************************************************************
int get_gps(gps_t *gps)
{
    int ret = 0;                                                                // Return value for function call
    json_keyval om[12];                                                         // Array used to handle json values returned from GPS calls
    double elapse=0;                                                            // Variable for running length of GPS call
    int k, done, i, intfmt, strfmt;                                             // Various temporary variables
    const char *mode[] = {                                                      // GPS configuration mode
        "2-MS-based mode",
        "3-MS assisted mode",
        "4-Standalone mode"
    };

    gettimeofday(&gps_start, NULL);                                             // Get start time for GPS call (sets global variable "gps_start")
    printf("Getting GPS information...\n");

    setGPSmode(4);                                                              // Sets GPS configuration to "Standalone" mode
    getGPSconfig(om,sizeof(om));
    enableGPS();

    done = 5;                                                                   // Variable "done" is either 0 when it's done, or holds the wait interval time
    while( done ) {
        k=i=getGPSlocation(om,sizeof(om));                                      // Get current GPS location info from MAL
        done = atoi(om[3].value)?0:5;                                           // Sets done to 0 (if GPS session has ended) or 5 (the timeout interval)

        for( i=1, intfmt=strfmt=0; i<k; i++ ) {                                 // Work through location info (in om[]), converting info from json format
            if( !strcmp(om[i].key,"loc_status") ) {
                gps->loc_status = atoi(om[i].value);
                printf("Status: %s\n",atoi(om[i].value)?"COMPLETED\n":"IN PROGRESS");
            }
            else if( !strcmp(om[i].key,"latitude") ) {
                gps->latitude = atof(om[i].value);
                printf(" latitude: %f\n",atof(om[i].value));
            }
            else if( !strcmp(om[i].key,"longitude") ) {
                gps->longitude = atof(om[i].value);
                printf("longitude: %f\n",atof(om[i].value));
            }
            else if( !strcmp(om[i].key,"timestamp") ) {
                char buf[80];
                time_t rawtime = ascii_to_epoch(om[i].value);
                struct tm *ts = localtime(&rawtime);
                gps->timestamp = ts;
                strftime(buf, sizeof(buf), "  Time is: %a %d-%m-%Y %H:%M:%S %Z", ts);
                puts(buf);
            }
            else if( !strcmp(om[i].key,"altitude") ) {
                gps->altitude = atoi(om[i].value);
                printf(" altitude: %d\n",atoi(om[i].value));
            }
            else if( !strcmp(om[i].key,"speed") ) {
                gps->speed = atoi(om[i].value);
                printf("    speed: %d\n",atoi(om[i].value));
            }
            else if( !strcmp(om[i].key,"accuracy") ) {
                gps->accuracy = atoi(om[i].value);
                printf(" accuracy: %d\n",atoi(om[i].value));
            }
            else if( !strcmp(om[i].key,"errno") ) {
                gps->errno = atoi(om[i].value);
                if( atoi(om[i].value) )
                    printf("GPS ERROR! %d\n",atoi(om[i].value));
            }
            else if( !strcmp(om[i].key,"errmsg") ) {
                if( strcmp(om[i].value,"<null>") )
                    printf("GPS ERROR MESSAGE: %s\n",om[i].value);
            }
            else
                printf("(%2d) KEY=%s ; VALUE=%s\n",i,om[i].key,om[i].value);
        }

        // Get current time and calculate elapse (how long we've been trying to get GPS info)
        gettimeofday(&gps_end, NULL);
        elapse = (((gps_end.tv_sec - gps_start.tv_sec)*1000) + (gps_end.tv_usec/1000 - gps_start.tv_usec/1000));

        // Subtract elapse from TimeOut to see if we keep going or abort
        if( ((GPS_TO*1000)-round(elapse))/1000 < 0) {
            done = 0;
            ret = 1;
            printf("\rGPS Acquisiton Timed Out (%d seconds)\n",(int)round(elapse)/1000);
        }
        else {
            printf("\rGPS Acquisiton time ellapsed = %d seconds\n",(int)round(elapse)/1000);
            sleep(done);
        }
    }

    disableGPS();

    return ret;
}
