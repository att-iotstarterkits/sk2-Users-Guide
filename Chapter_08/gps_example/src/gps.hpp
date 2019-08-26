#ifndef __GPS_H__
#define __GPS_H__

// ****************************************************************************
// gps_t structure passes gps info back from get_gps() function
// ****************************************************************************
typedef struct _gps_t {
    int           loc_status;
    float         latitude;
    float         longitude;
    int           altitude;
    int           speed;
    int           accuracy;
    int           errno;
    struct tm     *timestamp;
    } gps_t;

#ifdef __cplusplus
extern "C" {
#endif

// ***** Prototypes *****
int get_gps(gps_t *gps);

#ifdef __cplusplus
}
#endif

#endif // __GPS_H__

/* =====================================================================
   Copyright (c) 2019, AT&T (R)

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
