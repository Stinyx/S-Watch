#include "Draw.h"
#include "hardware/Display.h"
#include "ClockStyles.h"
#include "Images.h"

// Draws a full screen image on the screen
void Draw::drawImage(const unsigned char* image){
    display.drawXBitmap(0, 0, image, 200, 200, GxEPD_BLACK);
}

// Draws a clock seven segment digit on the screen
void Draw::drawDigit(int x, int y, int digit, int style){
    display.drawXBitmap(x, y, clockStyles[style][digit], digit_width, digit_height, GxEPD_BLACK);
}

// Fills the given area with white on the screen
void Draw::fill(int x, int y, int w, int h){
    display.fillRect(x, y, w, h, GxEPD_WHITE);
}

// Creates a partial window at given coordinates on the screen
void Draw::setPartial(int x, int y, int w, int h){
    display.setPartialWindow(x, y, w, h);
}

// Draws text at given coordinates on the screen
void Draw::drawText(char *text, int x, int y){
    display.setCursor(x, y);
    display.printf("%s", text);
}

// Draws the current time at given coordinates on the screen
void Draw::drawTime(int x, int y, int style) {
    int digitSpacing = 5;

    DateTime currentTime = timeManager.getCurrentTime();

    char timeToString[5];

    snprintf(timeToString, sizeof(timeToString),
             "%02d%02d", currentTime.hour, currentTime.minute);

        int offset = 0;

        for (int i = 0; i < 4; i++) {
            int digit = timeToString[i] - '0';

            drawDigit(x + offset, y, digit, style);

            if (i == 1) {
                offset += digit_width + 3;

                display.drawXBitmap(
                    x + offset,
                    y + (digit_height - dots_height) / 2,
                    dots,
                    dots_width,
                    dots_height,
                    GxEPD_BLACK
                );

                offset += dots_width + 3;
            } else {
                offset += digit_width + digitSpacing;
            }
        }

}

// Draws the current battery percentage and status at given coordinates on the screen
void Draw::drawBattery(const BatteryInfo& battery, int x, int y, bool drawVolts, bool drawUSB) {
    char buffer[48];


    if (battery.usbConnected && drawUSB) {
        drawVolts ? snprintf(buffer, sizeof(buffer), "%d%% %.2fV USB", battery.percentage, battery.voltage) : 
                    snprintf(buffer, sizeof(buffer), "%d%% USB", battery.percentage);
    }
    else {
        drawVolts ? snprintf(buffer, sizeof(buffer), "%d%% %.2fV", battery.percentage, battery.voltage) : 
                    snprintf(buffer, sizeof(buffer), "%d%%", battery.percentage);
    }


    display.setCursor(x, y);
    display.print(buffer);

}

// Draws the current date at given coordinates on the screen
void Draw::drawDate(int x, int y, bool drawYear) {
    DateTime currentTime = timeManager.getCurrentTime();

        display.setCursor(x, y);
        drawYear ? display.printf("%d.%d.%d", currentTime.dayNumber, currentTime.monthNumber, currentTime.year) : 
                    display.printf("%d.%d", currentTime.dayNumber, currentTime.monthNumber);
}
