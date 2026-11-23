#include "TimeManager.h"
#include "config/WifiCredentials.h"
#include <WiFi.h>
#include "esp_bt.h"
#include "config/Debug.h"


DateTime TimeManager::getDateTime() const{
  DateTime time;

  WiFi.begin(HWIFISSID, HWIFIPSWD);

  unsigned long startAttempt = millis();

  while (WiFi.status() != WL_CONNECTED &&
        millis() - startAttempt < 10000) {
      delay(500);
  }

  if (WiFi.status() != WL_CONNECTED) {

      WiFi.disconnect(true);
      WiFi.mode(WIFI_OFF);

      // Return a zero-initialized DateTime.
      time = {};
      return time;
  }

  configTzTime(this->timeZone, this->ntpServer);

  struct tm timeinfo;

  if (!getLocalTime(&timeinfo, 15000)) {

    WiFi.disconnect(true);
    WiFi.mode(WIFI_OFF);

    time = {};
    return time;
  }
  
  Serial.println(&timeinfo, "%d.%m.%Y %H:%M:%S");

  time.hour = timeinfo.tm_hour;
  time.minute = timeinfo.tm_min;
  time.second = timeinfo.tm_sec;
  time.dayNumber = timeinfo.tm_mday;
  time.dayText = "IDK";
  time.year = timeinfo.tm_year + 1900;
  time.monthNumber = timeinfo.tm_mon + 1;
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
  currentTime = getDateTime();
};

void TimeManager::update() {
    setenv("TZ", timeZone, 1);
    tzset();

    struct tm timeinfo = {};

    if (!getLocalTime(&timeinfo, 1000)) {
        return;
    }

    currentTime.hour = timeinfo.tm_hour;
    currentTime.minute = timeinfo.tm_min;
    currentTime.second = timeinfo.tm_sec;
    currentTime.dayNumber = timeinfo.tm_mday;
    currentTime.year = timeinfo.tm_year + 1900;
    currentTime.monthNumber = timeinfo.tm_mon + 1;
}

void TimeManager::disableRadios() {
    WiFi.disconnect(true);
    WiFi.mode(WIFI_OFF);

    btStop();
}

extern TimeManager timeManager;






