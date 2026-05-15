#pragma once
#include "main.h"

// device ID
#define DEVICE_ID "<DEVICE_ID>"                             // CHANGE IT AS YOU DESIRE, but IT MUST BE 3 CHARACTERS LONG for database compatibility

// WIFI credentials
#define SECRET_SSID "<SSID>"
#define SECRET_PASS "<PASSWORD>"


// MQTT server details/credentials
const char MQTT_BROKER_ADRRESS[] = "";                      // CHANGE TO MQTT BROKER'S IP ADDRESS
const int MQTT_PORT = 1883;                                 // CHANGE TO MQTT BROKER'S PORT
const char MQTT_CLIENT_ID[] = "";                           // CHANGE IT AS YOU DESIRE
const char MQTT_USERNAME[] = "";                            // CHANGE IT IF REQUIRED, empty if not required
const char MQTT_PASSWORD[] = "";                            // CHANGE IT IF REQUIRED, empty if not required