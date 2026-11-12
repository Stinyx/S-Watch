#include "app/App.h"
#include "graphics/Draw.h"
#include "screens/ClockScreen.h"
#include "screens/InitialisingScreen.h"
#include "services/TimeManager.h"
#include "services/PowerManager.h"
#include "hardware/Button.h"
#include "screens/MainMenuScreen.h"
#include "screens/InfoScreen.h"

// GRAPHICS
Draw draw;

// HARDWARE
PowerManager powerManager;
Display displayController;
Button buttons;

// INDIVIDUAL SCREENS + SCREEN MANAGER
ScreenManager screenManager;
ClockScreen clockScreen(draw, powerManager);
InitialisingScreen initialisingScreen(draw);
MainMenuScreen menuScreen(draw);
InfoScreen infoScreen(draw);

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
            screenManager.setScreen(clockScreen);
            return;
        }

        menuScreen.handleInput(input);

        if (menuScreen.consumeSelection()) {
            switch (menuScreen.getSelection()) {
                case 0:
                    screenManager.setScreen(clockScreen);
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

    screenManager.setWatchFace(clockScreen);
    screenManager.setInitialScreen(clockScreen);

    lastActivity = millis();

    if (buttonWake) {
        Input wakeInput = buttons.getWakeupInput();

        if (wakeInput == Input::Select) {
            // Go straight to the menu. Do not draw the clock first.
            handleButtonInput(wakeInput);
        } else {
            // Other buttons leave us on the watch face.
            screenManager.draw();
        }
    } else {
        // Cold boot or timer wake: draw the watch face normally.
        screenManager.draw();
    }
}

void App::update() {
    timeManager.update();
    screenManager.update();
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

    // Do not refresh the screen continuously here.
    // Individual screens call update() when something changes.

    if (!screenManager.isOnWatchFace()) {
        if (millis() - lastActivity >= MENU_TIMEOUT) {
            screenManager.setScreen(clockScreen);
        }
    }

    if (screenManager.isOnWatchFace()) {
        sleepUntilNextMinute();
    }
}