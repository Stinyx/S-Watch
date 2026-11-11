#pragma once

#include "time.h"
//#include <Arduino.h>

/*
// NTP Variables


// Returns the local time in a formatted string
String return_local_time();

// Calculates and returns drift between two time structures
long calculate_drift(struct tm oldTime, struct tm newTime);

// idk if this is used but there is another similar one im too far gone
String return_local_time_from_tm(struct tm t);

// Syncs the NTP data from a NTP server
void sync_ntp();
*/

class DateTime{
    public:
        int hour = 0;
        int minute = 0;
        int second = 0;
        int dayNumber = 0;
        const char* dayText = "NONE";
        int year = 0;
        int monthNumber = 0;
        const char* monthText = "NONE";
};


class TimeManager {
public:
    void init();
    void update();

    DateTime getDateTime() const;
    DateTime getCurrentTime() const;
private:
    const long gmtOffset_sec = 3600;
    const int daylightOffset_sec = 3600;
    const char* ntpServer = "pool.ntp.org";
    const char* timeZone = "CET-1CEST,M3.5.0,M10.5.0/3";
    DateTime currentTime;
};

extern TimeManager timeManager;

