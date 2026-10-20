#include <WiFi.h>
#include "Settings.h"
#include "Debug.h"
#include "Button.h"
#include "State.h"
#include "TimeManager.h"
#include "UserInterface.h"
#include "wificredentials.h"
#include "Init.h"

// Timer variables
unsigned long lastUpdate = 0;
int lastConnectionUpdate = 0;
int timeoutTimer = 0;

// Syncs the NTP data from a NTP server
void sync_ntp(){
  epdDraw(
    draw_blank
  );

  struct tm oldTime;
  getLocalTime(&oldTime);
  String oldTimeStr = return_local_time_from_tm(oldTime);

  display.setFullWindow();
  display.setTextSize(1);
  epdDraw(
    [&](){
      draw_text(0, 20, "Syncing NTP...");
    }
  );

  WiFi.mode(WIFI_STA);
  WiFi.begin(HWIFISSID, HWIFIPSWD);  

  while (WiFi.status() != WL_CONNECTED) {   
    delay(500);
  }

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);  

  struct tm newTime;
  getLocalTime(&newTime);
  String newTimeStr = return_local_time_from_tm(newTime);

  long drift = calculate_drift(oldTime, newTime);

  display.setTextSize(1);
  epdDrawPartial(0, 50, 200, 130, 
    [&](){
      display.setCursor(0, 70);
      display.printf("Old: \n%s", oldTimeStr.c_str());
    },
    [&](){
      display.setCursor(0, 120);
      display.printf("New: \n%s", newTimeStr.c_str());
    },
    [&](){
      display.setCursor(0,  170);
      display.printf("Drift: %lds", drift);
    }
  );

  WiFi.disconnect(true);  
  WiFi.mode(WIFI_OFF);  

  delay(5000);

  currentState = CLOCK;
}


// Basic arduino setup
void setup() {
  // Set base state
  currentState = CLOCK;

  Init();

  if(startupProcedure){
    //NTP and WIFI connection setup
    unsigned long wifiStart = millis();
    unsigned long lastDraw  = 0;
    const unsigned long WIFI_TIMEOUT = 10000; 
    int lineSpacing = 15;
    int offset = 15;

    // Draw WIFI Status message
    epdDraw(
      [&](){draw_text(0, 10, "> CONNECTING TO\nLOCAL WIFI");}
    );

    WiFi.begin(HWIFISSID, HWIFIPSWD);

    while (WiFi.status() != WL_CONNECTED) {

      // Try to connect to wifi for 10s, else timeout and display error message
      if (millis() - wifiStart > WIFI_TIMEOUT) {
        epdDraw(
          [&](){
            offset = lineSpacing * 3;
            draw_text(0, offset, "> FAILED TO \nCONNECT TO\nLOCAL WIFI!");
            delay(5000);
          }
        );
        break; 
      }

      delay(200); 
    }

    struct tm timeinfo;
    int retries = 0;  

    // Display that wifi was connected
    epdDraw(
      [&](){
        offset = lineSpacing * 3;
        draw_text(0, offset, "> WIFI\nCONNECTED\nSUCCESFULLY!");
        }
    );
    
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

    // Display NTP Waiting status message
    epdDraw(
      [&](){
        offset = lineSpacing * 7;
        draw_text(0, offset, "> WAITING FOR\nNTP RESPONSE...");
      }
    );

    // Try to get NTP Data
    while(!getLocalTime(&timeinfo) && retries < 10){
        delay(1000);
        retries++;
    }

    // Display if NTP was synced succesfully or not
    if (retries == 10){
      epdDraw(
        [&](){
          offset = lineSpacing * 10;
          draw_text(0, offset, "> FAILED TO GET\nNTP DATA!");
        }
      );
    } else {
      epdDraw(
        [&](){
          offset = lineSpacing * 10;
          draw_text(0, offset, "> NPT DATA\nACQUIRED\nSUCCESFULLY!");
        }
      );
    }
    delay(2000);

    // Disconnect wifi for power saving
    WiFi.disconnect(true);
    WiFi.mode(WIFI_OFF);
  }
}

// Basic arduino loop
void loop() {

  ButtonLoop();

  if (currentState != lastState) {
    onStateEnter(currentState);
    lastState = currentState;
  }

  switch (currentState) {

    case NTPSYNCING:
      sync_ntp();
      break;

    case CLOCK:
      if (millis() - lastUpdate >= 10000) { 
        epdDraw(
          draw_time,
          [&]() {
            if (drawDate) draw_date();
          }
        );

        lastUpdate = millis();
      }
      break;

    case SETTINGS:
      if (currentMenuSelected != lastMenuSelected) {
        draw_settings();
        lastMenuSelected = currentMenuSelected;
      }
      break;

    case NAVIGATION:
      if (currentNavigationSelected != lastNavigationSelected) {
        draw_navigation();
        lastNavigationSelected = currentNavigationSelected;
      }
      break;
  }
}

