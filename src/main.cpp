
#include "app/App.h"
#include <Arduino.h>

App app;

// Setup loop for the watch, mostly for the clockface
void setup() {
    setCpuFrequencyMhz(80);

    app.begin();
}

// Loop for menu and better button interactions
void loop(){
  app.loop();
}
