#include "Draw.h"
#include "hardware/Display.h"
#include "Clockfaces.h"
#include "Images.h"

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

    display.setPartialWindow(winX, winY, winW, winH);

    DateTime currentTime = timeManager.getCurrentTime();

    char timeToString[5];

    snprintf(timeToString, sizeof(timeToString),
             "%02d%02d", currentTime.hour, currentTime.minute);

    display.firstPage();

    do {
        display.fillRect(winX, winY, winW, winH, GxEPD_WHITE);

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

    } while (display.nextPage());
}

void Draw::drawBattery(const BatteryInfo& battery, int x, int y) {
    char buffer[48];

    if (battery.charging) {
        snprintf(buffer, sizeof(buffer),
                 "%d%% %.2fV *",
                 battery.percentage, battery.voltage);
    }
    else if (battery.usbConnected) {
        snprintf(buffer, sizeof(buffer),
                 "%d%% %.2fV USB ",
                 battery.percentage, battery.voltage);
    }
    else {
        snprintf(buffer, sizeof(buffer),
                 "%d%% %.2fV",
                 battery.percentage, battery.voltage);
    }

    display.setPartialWindow(15, 130, 190, 40);

    display.firstPage();

    do {
        display.fillRect(15, 130, 190, 40, GxEPD_WHITE);

        display.setCursor(x, y);
        display.print(buffer);

    } while (display.nextPage());
}

void Draw::drawDate(int x, int y) {
    DateTime currentTime = timeManager.getCurrentTime();

    display.setPartialWindow(15, 160, 190, 40);
    display.firstPage();

    do {
        display.fillRect(15, 160, 190, 40, GxEPD_WHITE);

        display.setCursor(x, y);
        display.printf(
            "%d.%d.%d",
            currentTime.dayNumber,
            currentTime.monthNumber,
            currentTime.year
        );

    } while (display.nextPage());
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
