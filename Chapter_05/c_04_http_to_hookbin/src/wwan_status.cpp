#include <stdio.h>
#include "mal.hpp"
#include "iot_monitor.h"
#include <unistd.h>                                                             // Needed for sleep(), usleep()
#include "wwan_status.hpp"

void WWANStatus(wwanInfo *wwan, netInfo *net)
{
    json_keyval om[20];
    int k;
    int i;

    const char *radio_mode[] = {"No service", "3G", "4G" };
    const char *radio_state[]= {
        "No Registered", "Registered with network",
        "searching", "registration denied", "unknown" };
    const char *xs_state[]   = {"Unknown","Attached","Detached"};
    const char *roaming[]    = {"Home", "Roaming", "Unknown"};

    printf("\nWWAN Status \n");
    printf("==============================================================\n");
    printf("               Received: %d key/value pairs:\n", get_wwan_status(om, sizeof(om)));

    wwan->radioMode   = om[3].value;
    wwan->sigStrength = om[4].value;
    wwan->sigLevel    = om[6].value;
    wwan->radioState  = radio_state[atoi(om[7].value)];
    wwan->cirSwState  = xs_state[atoi(om[8].value)];
    wwan->packSwState = xs_state[atoi(om[9].value)];
    wwan->regState    = roaming[atoi(om[16].value)];

    printf("             Radio Mode: %s(%s)\n", radio_mode[atoi(om[3].value)], om[3].value);
    printf("        Signal strength: %s\n", om[4].value);
    printf("           Signal Level: %s\n", om[6].value);
    printf("                  state: %s(%s)\n", radio_state[atoi(om[7].value)], om[7].value);
    printf(" Circuit-switched state: %s(%s)\n", xs_state[atoi(om[8].value)], om[8].value);
    printf("  Packet-switched state: %s(%s)\n", xs_state[atoi(om[9].value)], om[9].value);
    printf("     Registration state: %s(%s)\n\n", roaming[atoi(om[16].value)], om[16].value);

    const char * type[] = {"3G/LTE", "Ethernet", "WiFi" };
    const char * state[] ={ "Disconnected", "Disconnecting", "Connecting", "Connected",
                            "Disconnected, and PIN locked", "Disconnected and SIM removed" };

    printf("Network Connection Status \n");
    printf("==============================================================\n");
    printf("          Received: %d key/value pairs:\n", get_connection_status(om, sizeof(om)));

    net->connType    = om[3].value;
    net->connState   = om[4].value;
    net->connTime    = om[5].value;
    net->provider    = om[6].value;
    net->radioMode   = om[7].value;
    net->dbTech      = om[8].value;
    net->roamStatus  = om[9].value;
    net->sigStrength = om[10].value;
    net->sigLevel    = om[11].value;
    net->lte         = om[12].value;
    net->wcdma       = om[13].value;
    net->ipv6        = om[14].value;

    printf("   connection type: %s(%s)\n", type[atoi(om[3].value)], om[3].value);
    printf("  connection state: %s(%s)\n", state[atoi(om[4].value)], om[4].value);
    printf("   connection time: %s\n", om[5].value);
    printf("          provider: %s\n", om[6].value);
    printf("        radio mode: %s\n", om[7].value);
    printf("  data_bearer_tech: %s\n", om[8].value);
    printf("    roaming status: %s\n", om[9].value);
    printf("   signal strength: %s\n", om[10].value);
    printf("      signal level: %s\n", om[11].value);
    printf("          LTE rsrp: %s\n", om[12].value);
    printf("        WCDMA RSCP: %s\n", om[13].value);
    printf("      ipv6 address: %s\n\n", om[14].value);

    printf("          Received: %d key/value pairs:\n", get_wwan_allow_data_roaming(om, sizeof(om)));
    printf("Allow Data Roaming: %s (%s)\n\n", atoi(om[3].value)? "YES":"NO", om[3].value);
}



/* =====================================================================
#  Copyright (c) 2018, AT&T (R)

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