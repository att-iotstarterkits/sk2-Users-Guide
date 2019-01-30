#ifndef __WWAN_STATUS_H__
#define __WWAN_STATUS_H__

#ifdef __cplusplus
typedef struct {
  std::string radioMode;
  std::string sigStrength;
  std::string sigLevel;
  std::string radioState;
  std::string cirSwState;
  std::string packSwState;
  std::string regState;
  } wwanInfo;
extern wwanInfo myWwan;
#endif

#ifdef __cplusplus
typedef struct {
    std::string connType;
    std::string connState;
    std::string connTime;
    std::string provider;
    std::string radioMode;
    std::string dbTech;
    std::string roamStatus;
    std::string sigStrength;
    std::string sigLevel;
    std::string lte;
    std::string wcdma;
    std::string ipv6;
  } netInfo;
extern netInfo myNetw;
#endif

#ifdef __cplusplus
extern "C" {
#endif

void WWANStatus(wwanInfo *, netInfo *);

#ifdef __cplusplus
}
#endif

#endif // __WWAN_STATUS_H__

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