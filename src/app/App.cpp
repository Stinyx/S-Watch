#include "app/App.h"
#include "graphics/Draw.h"
#include "screens/TestScreen.h"
#include "screens/InitialisingScreen.h"
#include "services/TimeManager.h"
#include "services/PowerManager.h"
#include "hardware/Button.h"
#include "screens/MainMenuScreen.h"
#include "screens/InfoScreen.h"

Draw draw;
PowerManager powerManager;
TestScreen testScreen(draw, powerManager);
InitialisingScreen initialisingScreen(draw);
Display displayController;
Button buttons;
ScreenManager screenManager;
MainMenuScreen menuScreen;
InfoScreen infoScreen;

static unsigned long lastActivity = 0;
static constexpr unsigned long MENU_TIMEOUT = 15000;

static void handleButtonInput(Input input) {
    if (input == Input::None) return;

    lastActivity = millis();

    if (screenManager.isOnWatchFace()) {
        if (input == Input::Select) {
            screenManager.setScreen(menuScreen);
        }
        return;
    }

    if (screenManager.isActive(menuScreen)) {
        if (input == Input::Back) {
            screenManager.setScreen(testScreen);
            return;
        }

        menuScreen.handleInput(input);

        if (menuScreen.consumeSelection()) {
            switch (menuScreen.getSelection()) {
                case 0:
                    screenManager.setScreen(testScreen);
                    break;

                case 1:
                    screenManager.setScreen(infoScreen);
                    break;
            }
        }

        return;
    }

    if (screenManager.isActive(infoScreen)) {
        if (input == Input::Back) {
            screenManager.setScreen(menuScreen);
        }
    }
}

void App::begin() {
    esp_sleep_wakeup_cause_t cause = esp_sleep_get_wakeup_cause();

    bool coldBoot = (cause == ESP_SLEEP_WAKEUP_UNDEFINED);
    bool timerWake = (cause == ESP_SLEEP_WAKEUP_TIMER);
    bool buttonWake = (cause == ESP_SLEEP_WAKEUP_EXT1);

    displayController.init();
    powerManager.init();
    buttons.init();

    // Initialize the clock on first boot.
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
    }

    // Restore the current time after every deep-sleep wake.
    else if (timerWake || buttonWake) {
        timeManager.update();
    }

    // Register the watch face and available screens.
    screenManager.setWatchFace(testScreen);
    screenManager.setScreen(testScreen);

    lastActivity = millis();

    // Process the button that woke the watch.
    if (buttonWake) {
        Input wakeInput = buttons.getWakeupInput();
        handleButtonInput(wakeInput);
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
        handleButtonInput(input);
    }

    screenManager.update();

    if (!screenManager.isOnWatchFace()) {
        if (millis() - lastActivity >= MENU_TIMEOUT) {
            screenManager.setScreen(testScreen);
        }
    }

    if (screenManager.isOnWatchFace()) {
        sleepUntilNextMinute();
    }
}