#include "app/App.h"
#include "graphics/Draw.h"
#include "screens/TestScreen.h"
#include "screens/InitialisingScreen.h"
#include "services/TimeManager.h"
#include "services/PowerManager.h"

Draw draw;
PowerManager powerManager;
TestScreen testScreen(draw, powerManager);
InitialisingScreen initialisingScreen(draw);
Display displayController;

void App::begin() {
    bool initial = esp_sleep_get_wakeup_cause() != ESP_SLEEP_WAKEUP_TIMER;

    displayController.init(initial);
    powerManager.init();

    if (initial) {
        display.setFullWindow();
        display.firstPage();
        do {
            initialisingScreen.draw();
        } while (display.nextPage());

        timeManager.init();

        // FILL SCREEN TO WHITE BEFORE SHOWING CLOCKSCREEN AFTER INIT SCREEN
        do {
            display.fillScreen(GxEPD_WHITE);
        } while (display.nextPage());
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