
// GxEPD2
#include <GxEPD2_BW.h>
#include <Fonts/FreeMonoBold9pt7b.h>
#include "GxEPD2_display_selection_new_style.h"
#include "images.h"

#include <math.h>

// Button2 
#include "Button2.h"
#define BUTTON_PIN 33

// NTP (Network Time Protocol)
#include <WiFi.h>
#include "time.h"

#define DISPLAYWIDTH 200
#define DISPLAYHEIGHT 200

// Input variables
Button2 button;
int state = 0;
int drawn = 0;

// NTP Variables
const char* ssid = "TP-Link_26F7";
const char* password = "10834312";
const long gmtOffset_sec = 3600;
const int daylightOffset_sec = 3600;
const char* ntpServer = "pool.ntp.org";

// DEBUG SETTINGS
const int startupProcedure = 1;
const int currentClockStyle = 1; //0 is first

unsigned long lastUpdate = 0;
int lastConnectionUpdate = 0;
int timeoutTimer = 0;



enum WatchState {
  NTPSYNCING,
  NTPSYNCED,
  CLOCK,
  SETTINGS,
  WEEZO,
  WEEZODRAWN,
};

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

unsigned char** clockStyles[2] = {
  digitArray, 
  digitArray2
};

enum WatchState currentState;
WatchState lastState = SETTINGS;

void print_local_time() {   
  struct tm timeinfo;
  if( !getLocalTime(&timeinfo) ) {   
    Serial.println("Unable to get time data");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");  
}

String return_local_time() {
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) return ""; 

    char buf[9];
    sprintf(buf, "%02d:%02d:%02d", timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);

    return String(buf);
}

long calculate_drift(struct tm oldTime, struct tm newTime){
    time_t oldTimestamp = mktime(&oldTime);
    time_t newTimestamp = mktime(&newTime);
    return newTimestamp - oldTimestamp;  // in seconds
}

String return_local_time_from_tm(struct tm t){
  char buf[9];
  sprintf(buf, "%02d:%02d:%02d", t.tm_hour, t.tm_min, t.tm_sec);
  return String(buf);
}

void draw_digit(int x, int y, int digit, int style){
    display.drawXBitmap(x, y, clockStyles[style][digit], digit_width, digit_height, GxEPD_BLACK);
}

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

  /*
  int year   = timeinfo.tm_year + 1900;
  int month  = timeinfo.tm_mon + 1;
  int day    = timeinfo.tm_mday;
  */

  int hour   = timeinfo.tm_hour;
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

void draw_text_static(String text, int x, int y){
  display.firstPage();
  do {
    display.setCursor(x, y);
    display.printf("%s", text.c_str());
  } while (display.nextPage());

}

void draw_text_partial(String text, int x, int y) {
  int16_t x1, y1;
  uint16_t w, h;

  display.getTextBounds(text.c_str(), x, y, &x1, &y1, &w, &h);
  display.setPartialWindow(x1, y1, w, h);
  display.firstPage();

  do {
      display.fillRect(x1, y1, w, h, GxEPD_WHITE);
      display.setCursor(x, y);
      display.printf("%s", text.c_str());
  } while (display.nextPage());
}

void sync_ntp(){
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);  

  while (WiFi.status() != WL_CONNECTED) {   
    delay(500);
    Serial.print(".");
  }

  Serial.println(" CONNECTED");
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);   
  print_local_time();
  WiFi.disconnect(true);  
  WiFi.mode(WIFI_OFF);  
}

void draw_blank(){
  display.setPartialWindow(0, 0, DISPLAYWIDTH, DISPLAYHEIGHT);
  display.firstPage();
  do {
    display.fillRect(0, 0, DISPLAYWIDTH, DISPLAYHEIGHT, GxEPD_WHITE);
  } while (display.nextPage());
}

void refresh_display(){
  display.setFullWindow();
  display.firstPage();
  do {
    display.fillScreen(GxEPD_WHITE);
  } while (display.nextPage());
}

// BUTTON PRESSING LOGIC
void buttonDoubleClick(Button2& b){
  if(currentState != WEEZO){
    currentState = WEEZO;
  }else if(currentState == WEEZO){
    refresh_display();
    currentState = CLOCK;
  }
}

void buttonLongClick(Button2& b){
  currentState = NTPSYNCING;
}

void draw_image(int x, int y, int w, int h, const unsigned char* image){
  display.setFullWindow();
  display.firstPage();
  do {
    display.fillScreen(GxEPD_WHITE);
    display.drawXBitmap(x, y, image, w, h, GxEPD_BLACK);
  } while (display.nextPage());
}



void setup() {
  // Set base state
  currentState = CLOCK;

  // Button2 setup (Input)
  button.begin(BUTTON_PIN, INPUT_PULLDOWN, false);
  button.setLongClickHandler(buttonLongClick);
  button.setDoubleClickHandler(buttonDoubleClick);

  // GxEPD setup (Drawing on screen)
  display.init(115200);
  display.setRotation(0);
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_BLACK);
  display.setFullWindow();

  // Refresh display once
  refresh_display();

  if(startupProcedure){
    //NTP and WIFI connection setup
    unsigned long wifiStart = millis();
    unsigned long lastDraw  = 0;
    const unsigned long WIFI_TIMEOUT = 10000; 
    int resultTextPosition = 60;
    int resultTexPositionCursor = resultTextPosition + 25;

    // Draw WIFI Status message
    display.setFullWindow();
    display.firstPage();
    do {
      display.setCursor(0, 10);
      display.println("CONNECTING");
      display.println("TO WIFI...\n");
      display.printf("%d/%d", millis() - wifiStart, WIFI_TIMEOUT);
    } while (display.nextPage());

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {

      // Try to connect to wifi for 10s, else timeout and display error message
      if (millis() - wifiStart > WIFI_TIMEOUT) {

        display.setPartialWindow(0, resultTextPosition, 200, 100);
        display.firstPage();
        do {
          display.setCursor(0, resultTexPositionCursor);
          display.println("FAILED TO");
          display.println("CONNECT TO");
          display.println("WIFI!");
        } while (display.nextPage());

        delay(5000);
        break; 
      }

      delay(200); 
    }

    struct tm timeinfo;
    int retries = 0;  

    // Display that wifi was connected
    display.setPartialWindow(0, resultTextPosition, 200, 100);
    display.firstPage();
    do {
      display.setCursor(0, resultTexPositionCursor);
      display.println("WIFI");
      display.println("CONNECTED");
      display.println("SUCCESSFULLY!");
    } while (display.nextPage());
    delay(1000);

    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

    // Display NTP Waiting status message
    display.setFullWindow();
    display.firstPage();
    do {
      display.fillScreen(GxEPD_WHITE);
      display.setCursor(0, 10);
      display.println("WAITING");
      display.println("FOR NTP");
      display.println("RESPONSE...\n");
      display.printf("%d/%d", 1, 1);
    } while (display.nextPage());

    // Try to get NTP Data
    while(!getLocalTime(&timeinfo) && retries < 10){
        delay(1000);
        retries++;
    }

    // Display if NTP was synced succesfully or not
    if (retries == 10){
      display.setPartialWindow(0, resultTextPosition, 200, 100);
      display.firstPage();
      do {
        display.setCursor(0, resultTexPositionCursor);
        display.println("FAILED TO");
        display.println("GET NTP DATA!");
      } while (display.nextPage());
    } else {
      display.setPartialWindow(0, resultTextPosition, 200, 100);
      display.firstPage();
      do {
        display.setCursor(0, resultTexPositionCursor);
        display.println("NTP TIME");
        display.println("ACQUIRED");
        display.println("SUCCESFULLY!");
      } while (display.nextPage());
    }
    delay(2000);

    // Disconnect wifi for power saving
    WiFi.disconnect(true);
    WiFi.mode(WIFI_OFF);
  }
}

void onStateEnter(WatchState state) {
  // Reset text size
  display.setTextSize(1);

  switch(state) {

    case CLOCK:
      display.setTextSize(2);
      draw_image(0, 0, 200, 200, clk_bg);
      draw_time();
      break;

    case WEEZO:
      draw_image(0, 0, 200, 200, weezo);  
      break;

    case NTPSYNCING:

      refresh_display();
      draw_text_partial("Syncing NTP...", 10, 50);
      break;

    default:
      break;
  }
}


void loop() {
  button.loop();

  if (currentState != lastState) {
    onStateEnter(currentState);
    lastState = currentState;
  }

  switch(currentState){
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

      draw_blank();
      draw_text_partial("Old: " + oldTimeStr, 10, 80);
      draw_text_partial("New: " + newTimeStr, 10, 120);
      draw_text_partial("Drift: " + String(drift) + "s", 10, 150);

      delay(5000);
      refresh_display();

      currentState = NTPSYNCED;
      break;
    }
    case NTPSYNCED:
      currentState = CLOCK;
      break;
    case CLOCK:
      if(millis() - lastUpdate >= 10000){ 
          draw_time();
          lastUpdate = millis();
      }
      break;
    case SETTINGS:
      break;
  }
}
