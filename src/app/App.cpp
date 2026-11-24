#include "app/App.h"
#include "graphics/Draw.h"
#include "screens/Screens.h"
#include "soc/rtc.h"

#include "services/TimeManager.h"
#include "services/PowerManager.h"
#include "services/ScreenManager.h"

#include "hardware/Button.h"
#include "hardware/Display.h"

// Graphics
Draw drawing;

// Hardware
Display displayController;
Button buttons;

// Managers/Services
ScreenManager screenManager;
PowerManager powerManager;
TimeManager timeManager;

// Screens
ClockScreen clockScreen;
InitialisingScreen initialisingScreen;
MainMenuScreen mainMenuScreen;
InfoScreen infoScreen;
SettingsScreen settingsScreen;

// Timeouts
static unsigned long lastActivity = 0;
static constexpr unsigned long MENU_TIMEOUT = 15000;

static void handleButtonInput(Input input) {
    if (input == Input::None) return;

    lastActivity = millis();

    screenManager.handleInput(input);
}

// Start the firmware
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
    }

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
        screenManager.update();
    } else {
        screenManager.draw();
    }
}

// Update some parts of firmware
void App::update() {
    timeManager.update();
    screenManager.update();
}

// Deep sleep for the clockscreen
void App::sleepUntilNextMinute() {
    display.hibernate();

    rtc_clk_32k_enable(true);

    struct tm timeinfo = {};
    int secondsToSleep = 60;

    if (getLocalTime(&timeinfo, 1000)) {
        secondsToSleep = 60 - timeinfo.tm_sec;

        if (secondsToSleep <= 0 || secondsToSleep > 60) {
            secondsToSleep = 60;
        }
    }

    timeManager.disableRadios();

    buttons.enableWakeup();

    esp_sleep_enable_timer_wakeup(
        (uint64_t)secondsToSleep * 1000000ULL
    );

    esp_deep_sleep_start();
}

// Firmware loop instead of periodic deepsleep for better menu button responsiveness
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