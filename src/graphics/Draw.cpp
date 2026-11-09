#include "Draw.h"
#include "hardware/Display.h"
#include "Clockfaces.h"

#include "Images.h"

void Draw::centeredText(const char* text, int y) {
    int16_t x1, y1;
    uint16_t w, h;

    display.getTextBounds(
        text, 0, 0, &x1, &y1, &w, &h
    );

    int x = (display.width() - static_cast<int>(w)) / 2 - x1;

    display.setCursor(x, y);
    display.print(text);
}

void Draw::drawImage(const unsigned char* image){
    display.drawXBitmap(0, 0, image, 200, 200, GxEPD_BLACK);
}

void Draw::drawDigit(int x, int y, int digit, int style){
    display.drawXBitmap(x, y, clockStyles[style][digit], digit_width, digit_height, GxEPD_BLACK);
}

void Draw::drawTime(int x, int y) {
    int winX = 15;
    int winY = 50;
    int winW = 169;
    int winH = digit_height;
    int digitSpacing = 5;

    // Clear only the time area.
    display.fillRect(winX, winY, winW, winH, GxEPD_WHITE);

    DateTime currentTime = timeManager.getCurrentTime();

    char timeToString[5];

    snprintf(timeToString, sizeof(timeToString),
             "%02d%02d", currentTime.hour, currentTime.minute);

    int offset = 0;

    for (int i = 0; i < 4; i++) {
        int digit = timeToString[i] - '0';
        drawDigit(winX + offset, winY, digit, 1);

        if (i == 1) {
            offset += digit_width + 3;

            display.drawXBitmap(
                winX + offset,
                winY + (digit_height - dots_height) / 2,
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

void Draw::setPartialWindow(int x, int y, int width, int height) {
    display.setPartialWindow(x, y, width, height);
}

void Draw::setTimePartial() {
    setPartialWindow(15, 50, 169, digit_height);
}

void Draw::setBatteryPartial() {
    setPartialWindow(15, 130, 190, 40);
}

void Draw::drawBattery(const BatteryInfo& battery, int x, int y) {
    char buffer[32];

    if(battery.charging){
        snprintf(buffer, sizeof(buffer), "%d%% %.2fv (CHARGING)", battery.percentage, battery.voltage);
    }else{
        snprintf(buffer, sizeof(buffer), "%d%% %.2fv", battery.percentage, battery.voltage);
    }
    

    display.setCursor(x, y);
    display.print(buffer);
}
/*
void draw_time(){



  if( !getLocalTime(&timeinfo) ) { 
    sprintf(timeToString, "0000"); 
    display.setPartialWindow(winX, winY, winW, winH);
    display.firstPage();
    do {
        int offset = 0;
        for(int i = 0; i < 4; i++){
            int digit = timeToString[i] - '0';
            draw_digit(winX + offset, winY, digit, currentClockStyle);

            if(i == 1){
                offset += digit_width + 3;
                display.drawXBitmap(winX + offset, winY + (digit_height - dots_height)/2, dots, dots_width, dots_height, GxEPD_BLACK);
                offset += dots_width + 3;
            }else{
                offset += digit_width + digitSpacing;
            }
        }
    } while (display.nextPage());
    return;
  }

  int hour = timeinfo.tm_hour;
  int minute = timeinfo.tm_min;
  int second = timeinfo.tm_sec;
  const char* ampm = (timeinfo.tm_hour >= 12) ? "PM" : "AM";

  if (militaryTime == 0) {
    if (hour == 0) {
        hour = 12;      // Midnight -> 12 AM
    } else if (hour > 12) {
        hour -= 12;     // 13-23 -> 1-11 PM
    }
  }

  

  
}
*/
