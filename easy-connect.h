/*
 * FILE: easy-connect.h
 *
 * Copyright (c) 2015 - 2017 ARM Limited. All rights reserved.
 * SPDX-License-Identifier: Apache-2.0
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef __EASY_CONNECT_H__
#define __EASY_CONNECT_H__

#include "mbed.h"

#define ETHERNET          1
#define WIFI              11
#define MESH_LOWPAN_ND    101
#define MESH_THREAD       102
#define CELLULAR          202
#define CELLULAR_WNC14A2A 203

// Define macros for radio type
#define ATMEL   1
#define MCR20   2
#define SPIRIT1 3
#define EFR32   4

#if MBED_CONF_EASY_CONNECT_NETWORK_INTERFACE == MESH_LOWPAN_ND || \
    MBED_CONF_EASY_CONNECT_NETWORK_INTERFACE == MESH_THREAD
// This is address to mbed Device Connector (hard-coded IP due to DNS might not be there)
#define MBED_SERVER_ADDRESS "coaps://[2607:f0d0:2601:52::20]:5684"
#else
// This is address to mbed Device Connector
#define MBED_SERVER_ADDRESS "coap://api.connector.mbed.com:5684"
#endif

/* \brief print_MAC - print_MAC  - helper function to print out MAC address
 * in: network_interface - pointer to network i/f
 *     bool log-messages   print out logs or not
 * MAC address is print, if it can be acquired & log_messages is true.
 *
 */
void print_MAC(NetworkInterface* network_interface, bool log_messages);


/* \brief easy_connect - easy_connect function to connect the pre-defined network bearer,
 *                       config done via mbed_app.json (see README.md for details).
 * IN: bool  log_messages  print out diagnostics or not.
 */
NetworkInterface* easy_connect(bool log_messages = false);

/* \brief easy_connect - easy_connect function to connect the pre-defined network bearer,
 *                       config done via mbed_app.json (see README.md for details).
 * IN: bool  log_messages  print out diagnostics or not.
 *     char* WiFiSSID      WiFi SSID - by default NULL, but if it's NULL
 *                         then MBED_CONF_EASY_CONNECT_WIFI_SSID will be used
 *     char* WiFiPassword  WiFi Password - by default NULL, but if it's NULL
 *                         then MBED_CONF_EASY_CONNECT_WIFI_PASSWORD will be used
 */
NetworkInterface* easy_connect(bool log_messages,
                               char* WiFiSSID,
                               char* WiFiPassword);

/* \brief easy_get_netif - easy_connect function to get pointer to network interface w/o connect it.
                           You might need this for example getting the WiFi interface, then doing a scan
                           and then connecting to one of the SSIDs found with a password end user supplies.
 * IN: bool  log_messages  print out diagnostics or not.
 */

NetworkInterface* easy_get_netif(bool log_messages);
/* \brief easy_get_wifi - easy_connect function to get pointer to Wifi interface
 *                        without connecting to it. You would want this 1st so that
 *                        you can scan the APNs, choose the right one and then connect.
 *
 * IN: bool  log_messages  print out diagnostics or not.
 */
WiFiInterface* easy_get_wifi(bool log_messages);

#endif // __EASY_CONNECT_H__
