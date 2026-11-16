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

void Draw::fill(int x, int y, int w, int h){
    display.fillRect(x, y, w, h, GxEPD_WHITE);
}

void Draw::setPartial(int x, int y, int w, int h){
    display.setPartialWindow(x, y, w, h);
}

void Draw::drawText(char *text, int x, int y){
    display.setCursor(x, y);
    display.printf("%s", text);
}

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

void Draw::drawDate(int x, int y, bool drawYear) {
    DateTime currentTime = timeManager.getCurrentTime();

        display.setCursor(x, y);
        drawYear ? display.printf("%d.%d.%d", currentTime.dayNumber, currentTime.monthNumber, currentTime.year) : 
                    display.printf("%d.%d", currentTime.dayNumber, currentTime.monthNumber);
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
