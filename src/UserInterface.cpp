/*
#include "UserInterface.h"
#include "Settings.h"
#include "Debug.h"

// Draws a single 7-segment digit on the display


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

int menuScrollOffset = 0;   // first visible item
const int visibleItems = 5;



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

void draw_sprite(int x, int y, int w, int h, const unsigned char* image){
  display.drawXBitmap(x, y, image, w, h, GxEPD_BLACK);
};

void draw_background(const unsigned char* backgroundImage){
  if(drawBackground) draw_image(0, 0, FULLSCREEN, FULLSCREEN, backgroundImage);
}
*/