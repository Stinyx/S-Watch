#pragma once

#include "services/PowerManager.h"
#include "services/TimeManager.h"

class Draw {
public:
    void centeredText(const char* text, int y);
    void drawImage(const unsigned char* image);
    void drawTime(int x, int y);
    void drawBattery(const BatteryInfo& battery, int x, int y);

    // Generic partial window
    void setPartialWindow(int x, int y, int width, int height);
    void setTimePartial();
    void setBatteryPartial();

private:
    void drawDigit(int x, int y, int digit, int style);
};