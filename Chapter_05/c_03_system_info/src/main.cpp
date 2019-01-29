#include <stdio.h>
#include "mal.hpp"
#include "iot_monitor.h"
#include <unistd.h>                                                             // Needed for sleep(), usleep()
#include "wwan_status.hpp"

int c;
sysinfo  mySystem;                                                              // Get system info from MAL
wwanInfo myWwan;                                                                // Get wwan info from MAL
netInfo  myNetw;                                                                // Get network info from MAL
unsigned int dbg_flag = 0;

int main(void) {
    // Return variables from function calls
    int  ret;
    // Key/value pairs for parsing json
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

    printf("\nNetwork Time = %s\n\n", get_networkTime(om, sizeof(om)));


    WWANStatus(&myWwan, &myNetw);

    printf("Radio mode: %s\n\n", myWwan.radioMode.c_str());

    printf("connType %s\n", myNetw.connType.c_str());
    printf("connState %s\n", myNetw.connState.c_str());
    printf("connTime %s\n", myNetw.connTime.c_str());
    printf("provider %s\n", myNetw.provider.c_str());
    printf("radioMode %s\n", myNetw.radioMode.c_str());
    printf("dbTech %s\n", myNetw.dbTech.c_str());
    printf("roamStatus %s\n", myNetw.roamStatus.c_str());
    printf("sigStrength %s\n", myNetw.sigStrength.c_str());
    printf("sigLevel %s\n", myNetw.sigLevel.c_str());
    printf("lte %s\n", myNetw.lte.c_str());
    printf("wcdma %s\n", myNetw.wcdma.c_str());
    printf("ipv6 %s\n\n", myNetw.ipv6.c_str());

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