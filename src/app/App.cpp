#include "app/App.h"
#include "graphics/Draw.h"
#include "screens/TestScreen.h"
#include "services/TimeManager.h"
#include "services/PowerManager.h"

Draw draw;
PowerManager powerManager;
TestScreen testScreen(draw, powerManager);
Display displayController;

void App::begin() {
    bool initial = esp_sleep_get_wakeup_cause() != ESP_SLEEP_WAKEUP_TIMER;

    displayController.init(initial);
    powerManager.init();

    if (initial) {
        timeManager.init();
    }

    update();
}

void App::update() {
    timeManager.update();

    // TestScreen handles both partial refreshes.
    testScreen.draw();

    display.hibernate();

    struct tm timeinfo;
    int secondsToSleep = 60;

    if (getLocalTime(&timeinfo, 1000)) {
        secondsToSleep = 60 - timeinfo.tm_sec;
        if (secondsToSleep <= 0) secondsToSleep = 60;
    }

    esp_sleep_enable_timer_wakeup(
        (uint64_t)secondsToSleep * 1000000ULL
    );

    esp_deep_sleep_start();
}