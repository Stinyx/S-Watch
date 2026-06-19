#include "TimeManager.h"
#include "wificredentials.h"
#include "UserInterface.h"
#include "State.h"

// NTP Variables
const long gmtOffset_sec = 3600;
const int daylightOffset_sec = 3600;
const char* ntpServer = "pool.ntp.org";

// Returns the local time in a formatted string
String return_local_time() {
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) return ""; 

    char buf[9];
    sprintf(buf, "%02d:%02d:%02d", timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);

    return String(buf);
}

// Calculates and returns drift between two time structures
long calculate_drift(struct tm oldTime, struct tm newTime){
    time_t oldTimestamp = mktime(&oldTime);
    time_t newTimestamp = mktime(&newTime);
    return newTimestamp - oldTimestamp;  // in seconds
}

// idk if this is used but there is another similar one im too far gone
String return_local_time_from_tm(struct tm t){
  char buf[30];
  sprintf(buf, "%d.%d-%d/%02d:%02d:%02d", t.tm_mday, t.tm_mon + 1, t.tm_year + + 1900, t.tm_hour, t.tm_min, t.tm_sec);
  return String(buf);
}



