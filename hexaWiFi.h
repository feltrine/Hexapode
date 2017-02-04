#ifndef _HEXAWIFI_H_
#define _HEXAWIFI_H_

#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>

#include "hexaServo.h"

/* WiFi access credentials */
#define _SSID_ "hexapodeAP"
#define _PASSWORD_ "thereisnospoon"

void initWiFi();
void waitInstr();
void handleRoot();
void handleForward();
void handleBackward();
void handleLeft();
void handleRight();

#endif
