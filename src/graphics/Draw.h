#pragma once

class Draw {
public:
    void centeredText(const char* text, int y);
    void drawImage(const unsigned char* image);
    void drawTime(int x, int y);
    void drawBattery(int x, int y);
    void setTimePartialWindow();

private:
    void drawDigit(int x, int y, int digit, int style);
};