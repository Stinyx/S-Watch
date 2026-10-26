/*

#include "TimeManager.h"
#include "wificredentials.h"
#include "UserInterface.h"
#include "State.h"

// NTP Variables
const long gmtOffset_sec = 3600;
const int daylightOffset_sec = 3600;
const char* ntpServer = "pool.ntp.org";

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
  char buf[30];
  sprintf(buf, "%d.%d-%d/%02d:%02d:%02d", t.tm_mday, t.tm_mon + 1, t.tm_year + + 1900, t.tm_hour, t.tm_min, t.tm_sec);
  return String(buf);
}
*/
/*
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

  */


