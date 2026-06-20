#include "UserInterface.h"
#include "Settings.h"
#include "Debug.h"

// Draws a single 7-segment digit on the display
void draw_digit(int x, int y, int digit, int style){
    display.drawXBitmap(x, y, clockStyles[style][digit], digit_width, digit_height, GxEPD_BLACK);
}

// Draws text on screen (basically display.printf() but e-ink and dynamic with partial refresh)
void draw_text(int x, int y, const char* fmt, ...)
{
  char buffer[128];   // adjust size if needed

  // Build formatted string
  va_list args;
  va_start(args, fmt);
  vsnprintf(buffer, sizeof(buffer), fmt, args);
  va_end(args);

  int16_t x1, y1;
  uint16_t w, h;

  display.getTextBounds(buffer, x, y, &x1, &y1, &w, &h);
  display.setPartialWindow(x1, y1, w, h);

  display.fillRect(x1, y1, w, h, GxEPD_WHITE);
  display.setCursor(x, y);
  display.print(buffer);
}

void draw_settings(){
  epdDrawPartial(15, 45, 170, 145,
    [](){
      int offset = 60;
      int lineHeight = 25;
      int i = 0;
      for(const Setting& setting : settingsOptions){

        display.setCursor(15, offset);
        if(currentMenuSelected == i) display.printf(">%s", setting.description);
        else display.printf("%s", setting.description);

        if(setting.scrollable && setting.scrollOptions != NULL){
          display.setCursor(155, offset);
          display.printf("<%d>", *setting.scrollOptions);
        } 

        offset += lineHeight;
        i++;
      }
    }
  );
}

void draw_navigation(){
  epdDrawPartial(15, 45, 170, 145,
    [](){
      int offset = 60;
      int lineHeight = 25;
      int i = 0;
      for(const Setting& navigation : navigationOptions){

        display.setCursor(15, offset);
        if(currentNavigationSelected == i) display.printf(">%s", navigation.description);
        else display.printf("%s", navigation.description);

        offset += lineHeight;
        i++;
      }
    }
  );
}

void draw_about(){
  epdDrawPartial(20, 45, 170, 145,
    [](){
      draw_text(20, 55, "made by Stinyx\n uptime: (todo)\nversion: (todo)");
    }
  );
};

// Draws out the current date on screen
void draw_date(){
  struct tm timeinfo;  

  int winX = 16;
  int winY = 122;
  int winW = 168; 
  int winH = 200 - winY - 15; 

  int year = timeinfo.tm_year + 1900;
  int month = timeinfo.tm_mon + 1;
  int day = timeinfo.tm_mday;

  display.setTextSize(1);
  if( !getLocalTime(&timeinfo) ) { 

    epdDraw(
      [&](){
        draw_text(winX, winY + 20, "DATE NOT FOUND");
      }
    );
    return;

  }else{
    display.setPartialWindow(winX , winY, winW, winH);
    display.firstPage();
    do {
      display.setCursor(winX, winY + 20);
      display.println(&timeinfo, "%A");
      display.setCursor(winX, winY + 40);
      display.println(&timeinfo, "%B %d");
      display.setCursor(winX, winY + 60);
      display.println(&timeinfo, "%Y");
    } while (display.nextPage());
  }
}

// Draws out the current time on screen
void draw_time(){
  struct tm timeinfo;  
  char timeToString[4];

  int winX = 15;
  int winY = 50;
  int winW = 169; 
  int winH = digit_height; 
  int digitSpacing = 5;

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

  sprintf(timeToString, "%02d%02d", hour, minute); 

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
}

// Draws a white screen to avoid a full screen refresh but avoid ghosting a little
void draw_blank(){
  display.setPartialWindow(0, 0, DISPLAYWIDTH, DISPLAYHEIGHT);
  display.firstPage();
  display.fillRect(0, 0, DISPLAYWIDTH, DISPLAYHEIGHT, GxEPD_WHITE);
}

// Refreshes display fully to avoid ghosting
void refresh_display(){
  display.setFullWindow();
  epdDraw(
    [](){display.fillScreen(GxEPD_WHITE);}
  );
}

// Draws an image on screen
void draw_image(int x, int y, int w, int h, const unsigned char* image){
  display.setFullWindow();
  display.firstPage();
  epdDraw(
    [&](){display.fillScreen(GxEPD_WHITE);},
    [&](){display.drawXBitmap(x, y, image, w, h, GxEPD_BLACK);}
  );
}