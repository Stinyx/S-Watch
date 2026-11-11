#pragma once

#include "services/PowerManager.h"
#include "services/TimeManager.h"

class Draw {
public:
    void drawImage(const unsigned char* image);
    void drawTime(int x, int y);
    void drawBattery(const BatteryInfo& battery, int x, int y);
    void drawDate(int x, int y);
    void drawText(char *text, int x, int y);


private:
    void drawDigit(int x, int y, int digit, int style);
};