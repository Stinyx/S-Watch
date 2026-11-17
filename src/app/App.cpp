#include "app/App.h"
#include "graphics/Draw.h"
#include "screens/Screens.h"
#include "services/TimeManager.h"
#include "services/PowerManager.h"
#include "hardware/Button.h"

#include "hardware/Display.h"
#include "services/ScreenManager.h"


// GRAPHICS
Draw drawing;

// HARDWARE

Display displayController;
Button buttons;

// MANAGERS
ScreenManager screenManager;
PowerManager powerManager;
TimeManager timeManager;

ClockScreen clockScreen;
InitialisingScreen initialisingScreen;
MainMenuScreen mainMenuScreen;
InfoScreen infoScreen;

static unsigned long lastActivity = 0;
static constexpr unsigned long MENU_TIMEOUT = 15000;

static void handleButtonInput(Input input) {
    if (input == Input::None) return;

    lastActivity = millis();

    screenManager.handleInput(input);
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

        handleButtonInput(wakeInput);

    } else if (timerWake) {
        // Timer wake: update the watch face using partial refresh.
        screenManager.update();
    } else {
        // Cold boot: full refresh.
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

    timeManager.disableRadios();

    buttons.enableWakeup();
    esp_deep_sleep_start();
}

void App::loop() {
    Input input = buttons.readInput();

    if (input != Input::None) {
        handleButtonInput(input);
    }

    if (!screenManager.isOnWatchFace()) {
        if (millis() - lastActivity >= MENU_TIMEOUT) {
            screenManager.setScreen(clockScreen);
        }
    }

    if (screenManager.isOnWatchFace()) {
        sleepUntilNextMinute();
    }
}