#pragma once

#include "TimeManager.h"
#include "config/WifiCredentials.h"
#include <WiFi.h>
#include "config/Debug.h"

/*

#include "TimeManager.h"
#include "wificredentials.h"
#include "UserInterface.h"
#include "State.h"



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


    int retries = 0;  

    // Display that wifi was connected
    epdDraw(
      [&](){
        offset = lineSpacing * 3;
        draw_text(0, offset, "> WIFI\nCONNECTED\nSUCCESFULLY!");
        }
    );
    
    

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

  }

  */

DateTime TimeManager::getDateTime() const{
  DateTime time;

  WiFi.begin(HWIFISSID, HWIFIPSWD);

  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi connected!");

  configTzTime(this->timeZone, this->ntpServer);

  struct tm timeinfo;

  if (!getLocalTime(&timeinfo, 5000)) {
    Serial.println("Unable to get time from NTP");

    time.hour = 0;
    time.minute = 0;
    time.second = 0;
    time.dayNumber;
    time.dayText = "NONE";
    time.year = 0;
    time.monthNumber = 0;
    time.monthText = "NONE";

    return time;
  }
  
  Serial.println(&timeinfo, "%d.%m.%Y %H:%M:%S");

  time.hour = timeinfo.tm_hour;
  time.minute = timeinfo.tm_min;
  time.second = timeinfo.tm_sec;
  time.dayNumber = timeinfo.tm_wday;
  time.dayText = "IDK";
  time.year = timeinfo.tm_year + 1900;
  time.monthNumber = timeinfo.tm_mday;
  time.monthText = "IDK";

  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);

  return time;
};

DateTime TimeManager::getCurrentTime() const{
  DateTime time = this->currentTime;

  return time;
};

void TimeManager::init(){
  DateTime time;
  time = getCurrentTime();

  this->currentTime = time;

};

void TimeManager::update(){
    // Restore timezone after deep-sleep restart.
  setenv("TZ", timeZone, 1);
  tzset();

  struct tm timeinfo = {};

  if (!getLocalTime(&timeinfo, 1000)) {
      Serial.println("Internal clock unavailable");
      return; // Keep the previous currentTime
  }

  currentTime.hour = timeinfo.tm_hour;
  currentTime.minute = timeinfo.tm_min;
  currentTime.second = timeinfo.tm_sec;
  currentTime.dayNumber = timeinfo.tm_mday;
  currentTime.year = timeinfo.tm_year + 1900;
  currentTime.monthNumber = timeinfo.tm_mon + 1;
}





