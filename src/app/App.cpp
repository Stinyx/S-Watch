#include "app/App.h"
#include "graphics/Draw.h"
#include "screens/TestScreen.h"
#include "screens/InitialisingScreen.h"
#include "services/TimeManager.h"
#include "services/PowerManager.h"
#include "hardware/Button.h"

Draw draw;
PowerManager powerManager;
TestScreen testScreen(draw, powerManager);
InitialisingScreen initialisingScreen(draw);
Display displayController;
Button buttons;
ScreenManager screenManager;

void App::begin() {
    esp_sleep_wakeup_cause_t cause = esp_sleep_get_wakeup_cause();

    bool coldBoot = (cause == ESP_SLEEP_WAKEUP_UNDEFINED);
    bool timerWake = (cause == ESP_SLEEP_WAKEUP_TIMER);
    bool buttonWake = (cause == ESP_SLEEP_WAKEUP_EXT1);

    displayController.init();
    powerManager.init();
    buttons.init();

    if (coldBoot) {
        display.setFullWindow();
        display.firstPage();
        do {
            initialisingScreen.draw();
        } while (display.nextPage());

        timeManager.init();

        display.setFullWindow();
        display.firstPage();
        do {
            display.fillScreen(GxEPD_WHITE);
        } while (display.nextPage());

    } else if (timerWake || buttonWake) {
        timeManager.update();
    }

    Input wakeInput = Input::None;

    screenManager.setWatchFace(testScreen);

    if (buttonWake) {
        wakeInput = buttons.getWakeupInput();
    }

    screenManager.setScreen(testScreen);

    if (wakeInput != Input::None) {
        screenManager.handleInput(wakeInput);
    }
}

void App::update() {
    timeManager.update();
    screenManager.draw();
}

void App::sleepUntilNextMinute() {
    display.hibernate();

    struct tm timeinfo;
    int secondsToSleep = 60;

    if (getLocalTime(&timeinfo, 1000)) {
        secondsToSleep = 60 - timeinfo.tm_sec;
        if (secondsToSleep <= 0)
            secondsToSleep = 60;
    }

    esp_sleep_enable_timer_wakeup(
        (uint64_t)secondsToSleep * 1000000ULL
    );

    buttons.enableWakeup();
    esp_deep_sleep_start();
}

void App::loop() {
    Input input = buttons.readInput();

    if (input != Input::None) {
        screenManager.handleInput(input);
    }

    screenManager.update();

    if (screenManager.isOnWatchFace()) {
        sleepUntilNextMinute();
    }
}