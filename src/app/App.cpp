#include "app/App.h"
#include "graphics/Draw.h"
#include "screens/TestScreen.h"
#include "services/TimeManager.h"

Draw draw;
TestScreen testScreen(draw);
Display displayController;

void App::begin() {
    bool initial = esp_sleep_get_wakeup_cause() != ESP_SLEEP_WAKEUP_TIMER;

    displayController.init(initial);

    if (initial) {
        timeManager.init();
    }

    update();
}

void App::update() {
    timeManager.update();
    // 1. Vykreslení obrazovky
    draw.setTimePartialWindow();

    display.firstPage();
    do {
        testScreen.draw();
    } while (display.nextPage());

    // 2. Uspání displeje
    display.hibernate();

    // 3. Přímý výpočet sekund do další minuty
    struct tm timeinfo;
    int secondsToSleep = 60;
    if (getLocalTime(&timeinfo, 1000)) {
        secondsToSleep = 60 - timeinfo.tm_sec;
        if (secondsToSleep <= 0) secondsToSleep = 60;
    }

    // 4. Přechod do Deep Sleep
    esp_sleep_enable_timer_wakeup((uint64_t)secondsToSleep * 1000000ULL);
    esp_deep_sleep_start();
}