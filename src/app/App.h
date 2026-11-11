#pragma once

#include "hardware/Display.h"
#include  "hardware/Button.h"
#include "services/TimeManager.h"
#include "ScreenManager.h"

class App {
public:
    App() = default;
    ~App() = default;
    void begin();
    void update();
    void loop();
    void sleepUntilNextMinute();
};