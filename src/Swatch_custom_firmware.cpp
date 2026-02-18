
// GxEPD2
#include <GxEPD2_BW.h>
#include <Fonts/FreeMonoBold9pt7b.h>
#include "GxEPD2_display_selection_new_style.h"
#include "images.h"

#include <math.h>

// Button2 
#include "Button2.h"
#define BUTTON_PIN 33

// Wifi + NTP (Network Time Protocol)
#include <WiFi.h>
#include "time.h"
#include "wificredentials.h"

#define DISPLAYWIDTH 200
#define DISPLAYHEIGHT 200
#define FULLSCREEN 200

// Input variables
Button2 button;
int state = 0;
int drawn = 0;

// NTP Variables

const long gmtOffset_sec = 3600;
const int daylightOffset_sec = 3600;
const char* ntpServer = "pool.ntp.org";

// Debug settings for now until Settings are fully implemented
const int startupProcedure = 1;
const int currentClockStyle = 1; //0 is first

// Timer variables
unsigned long lastUpdate = 0;
int lastConnectionUpdate = 0;
int timeoutTimer = 0;

// Watch state enum with all the possible states (state machine)
enum WatchState {
  NTPSYNCING,
  NTPSYNCED,
  CLOCK,
  SETTINGS,
  WEEZO,
  WEEZODRAWN,
};

// Digits with the missing ones deleted
unsigned char* digitArray[10] = {
  digit0,
  digit1,
  digit2,
  digit3,
  digit4,
  digit5,
  digit6,
  digit7,
  digit8,
  digit9
};

// Digits with the missing ones having an outline
unsigned char* digitArray2[10] = {
  digit0_1,
  digit1_1,
  digit2_1,
  digit3_1,
  digit4_1,
  digit5_1,
  digit6_1,
  digit7_1,
  digit8_1,
  digit9_1
};

// Styles
unsigned char** clockStyles[2] = {
  digitArray, 
  digitArray2
};

// Watch states
enum WatchState currentState;
WatchState lastState = SETTINGS;

template<typename... Funcs>
void epdDraw(Funcs... funcs)
{
  display.firstPage();
  do {
    (funcs(), ...);   // calls all functions
  } while (display.nextPage());
}

template<typename... Funcs>
void epdDrawPartial(int x, int y, int w, int h, Funcs... funcs)
{
  display.setPartialWindow(x, y, w, h);

  display.firstPage();
  do {
    (funcs(), ...);
  } while (display.nextPage());
}

// Returns the local time in a formatted string
String return_local_time() {
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) return ""; 

    char buf[9];
    sprintf(buf, "%02d:%02d:%02d", timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);

    return String(buf);
}

// Calculates and returns drift between two time structures
long calculate_drift(struct tm oldTime, struct tm newTime){
    time_t oldTimestamp = mktime(&oldTime);
    time_t newTimestamp = mktime(&newTime);
    return newTimestamp - oldTimestamp;  // in seconds
}

// idk if this is used but there is another similar one im too far gone
String return_local_time_from_tm(struct tm t){
  char buf[9];
  sprintf(buf, "%02d:%02d:%02d", t.tm_hour, t.tm_min, t.tm_sec);
  return String(buf);
}

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

// Draws out the current date on screen
void draw_date(){
  struct tm timeinfo;  

  int winX = 16;
  int winY = 122;
  int winW = 168; 
  int winH = 200 - winY - 15; 

  int year   = timeinfo.tm_year + 1900;
  int month  = timeinfo.tm_mon + 1;
  int day    = timeinfo.tm_mday;

  display.setTextSize(1);
  if( !getLocalTime(&timeinfo) ) { 
    display.setPartialWindow(winX , winY, winW, winH);
    display.firstPage();
    do {
      display.setCursor(winX, winY + 20);
      display.println("DATE NOT FOUND");
    } while (display.nextPage());
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

  int winX = 16;
  int winY = 50;
  int winW = 168; 
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

// Syncs the NTP data from a NTP server
void sync_ntp(){
  WiFi.mode(WIFI_STA);
  WiFi.begin(HWIFISSID, HWIFIPSWD);  

  while (WiFi.status() != WL_CONNECTED) {   
    delay(500);
  }

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);   
  WiFi.disconnect(true);  
  WiFi.mode(WIFI_OFF);  
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
  display.firstPage();
  display.fillScreen(GxEPD_WHITE);
}

// Button logic for a single click (Weezo image haha get weezo'd)
void buttonDoubleClick(Button2& b){
  if(currentState != WEEZO){
    currentState = WEEZO;
  }else if(currentState == WEEZO){
    currentState = CLOCK;
  }
}

// Button logic for a triple click (Settings screen for now)
void buttonTripleClick(Button2& b){
  if(currentState != SETTINGS){
    currentState = SETTINGS;
  }else{
    currentState = CLOCK;
  }
}

// Button logic for a long click (NTP sync for now)
void buttonLongClick(Button2& b){
  currentState = NTPSYNCING;
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


// Basic arduino setup
void setup() {
  // Set base state
  currentState = CLOCK;

  // Button2 setup (Input)
  button.begin(BUTTON_PIN, INPUT_PULLDOWN, false);
  button.setLongClickHandler(buttonLongClick);
  button.setDoubleClickHandler(buttonDoubleClick);
  button.setTripleClickHandler(buttonTripleClick);

  // GxEPD setup (Drawing on screen)
  display.init(115200);
  display.setRotation(0);
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_BLACK);
  display.setFullWindow();

  // Refresh display once to avoid ghosting and apparently activate partial refresh
  refresh_display();

  if(startupProcedure){
    //NTP and WIFI connection setup
    unsigned long wifiStart = millis();
    unsigned long lastDraw  = 0;
    const unsigned long WIFI_TIMEOUT = 10000; 
    int resultTextPosition = 60;
    int resultTexPositionCursor = resultTextPosition + 25;
    int topPadded = 10;

    // Draw WIFI Status message
    epdDraw(
      [&](){draw_text(0, topPadded, "CONNECTING TO\nLOCAL WIFI");}
    );

    WiFi.begin(HWIFISSID, HWIFIPSWD);

    while (WiFi.status() != WL_CONNECTED) {

      // Try to connect to wifi for 10s, else timeout and display error message
      if (millis() - wifiStart > WIFI_TIMEOUT) {
        epdDraw(
          [&](){draw_text(0, resultTexPositionCursor, "FAILED TO CONNECT\nTO WIFI!");},
          refresh_display
        );

        delay(5000);
        break; 
      }

      delay(200); 
    }

    struct tm timeinfo;
    int retries = 0;  

    // Display that wifi was connected
    epdDraw(
      [&](){draw_text(0, resultTexPositionCursor, "WIFI\nCONNECTED\nSUCCESFULLY!");},
      [](){delay(1000);},
      refresh_display
    );
    
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

    // Display NTP Waiting status message
    epdDraw(
      [&](){draw_text(0, topPadded, "WAITING FOR\nNTP RESPONSE...");}
    );

    // Try to get NTP Data
    while(!getLocalTime(&timeinfo) && retries < 10){
        delay(1000);
        retries++;
    }

    // Display if NTP was synced succesfully or not
    if (retries == 10){
      epdDraw(
        [&](){draw_text(0, resultTexPositionCursor, "FAILED TO GET\nNTP DATA!");}
      );
    } else {
      epdDraw(
        [&](){draw_text(0, resultTexPositionCursor, "NPT DATA ACQUIRED\nSUCCESFULLY!");}
      );
    }
    delay(2000);

    // Disconnect wifi for power saving
    WiFi.disconnect(true);
    WiFi.mode(WIFI_OFF);
  }
}

// If watchstate changes, do something only once
void onStateEnter(WatchState state) {
  // Reset text size (AND MAYBE OTHER THINGS IN THE FUTURE)
  display.setTextSize(1);
  refresh_display();
  
  switch(state) {

    case CLOCK:
      display.setTextSize(2);
      draw_image(0, 0, FULLSCREEN, FULLSCREEN, clk_bg);
      draw_date();
      draw_time();
      break;

    case WEEZO:
      draw_image(0, 0, FULLSCREEN, FULLSCREEN, flowersakuralogo);  
      break;

    case NTPSYNCING:
      draw_text(10, 50, "Syncing NTP...");
      break;

    case SETTINGS:
      draw_image(0, 0, FULLSCREEN, FULLSCREEN, cfg_bg);
      break;

    default:
      break;
  }
}

// Basic arduino loop
void loop() {
  button.loop();

  if (currentState != lastState) {
    onStateEnter(currentState);
    lastState = currentState;
  }

  switch(currentState){
    // THIS LOOKS SO FUCKING UGLY I GOTTA FIX THE SYNC_NTP SHIT FUNCTION WHATEVER
    case NTPSYNCING:
    {
      struct tm oldTime;
      getLocalTime(&oldTime);
      String oldTimeStr = return_local_time_from_tm(oldTime);

      sync_ntp();  

      struct tm newTime;
      getLocalTime(&newTime);
      String newTimeStr = return_local_time_from_tm(newTime);

      long drift = calculate_drift(oldTime, newTime);

      
      epdDraw(
        draw_blank,
        [&](){draw_text(10, 80, "Old: %s", oldTimeStr);},
        [&](){draw_text(10, 120, "New: %s", newTimeStr);},
        [&](){draw_text(10, 150, "Drift: %ss", String(drift));}
      );

      delay(5000);
      currentState = NTPSYNCED;
      break;
    }
    case NTPSYNCED:
      currentState = CLOCK;
      break;
    // THIS CLOCK FUNCTION ALSO LOOKS BAD SO I GOTTA MAKE IT LOOK BETTER
    case CLOCK:
      if(millis() - lastUpdate >= 10000){ 
          // DRAWING THE DATE IS UNOPTIMISED, MAKE IT DRAW ONLY WHEN IT CHANGES 
          epdDraw(draw_time, draw_date);
          lastUpdate = millis();
      }
      break;
    case SETTINGS:
      break;
  }
}
