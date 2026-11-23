#pragma once

#include "time.h"

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

    void disableRadios();
private:
    const long gmtOffset_sec = 3600;
    const int daylightOffset_sec = 3600;
    const char* ntpServer = "pool.ntp.org";
    const char* timeZone = "CET-1CEST,M3.5.0,M10.5.0/3";
    DateTime currentTime;
};

extern TimeManager timeManager;

