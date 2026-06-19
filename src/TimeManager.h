#pragma once

#include "time.h"
#include <Arduino.h>

// NTP Variables
extern const long gmtOffset_sec;
extern const int daylightOffset_sec;
extern const char* ntpServer;

// Returns the local time in a formatted string
String return_local_time();

// Calculates and returns drift between two time structures
long calculate_drift(struct tm oldTime, struct tm newTime);

// idk if this is used but there is another similar one im too far gone
String return_local_time_from_tm(struct tm t);

// Syncs the NTP data from a NTP server
void sync_ntp();

