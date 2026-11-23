
#include "app/App.h"
#include <Arduino.h>

App app;

void setup() {
    setCpuFrequencyMhz(80);

    app.begin();
}

void loop(){
  app.loop();
}
