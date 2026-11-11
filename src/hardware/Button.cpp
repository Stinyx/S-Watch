
#include "Button.h"

#include <Arduino.h>
#include <esp_sleep.h>
#include <driver/rtc_io.h>

#define MENU_PIN 7
#define BACK_PIN 6
#define UP_PIN   0
#define DOWN_PIN 8

static constexpr uint64_t BUTTON_MASK =
    (1ULL << MENU_PIN) |
    (1ULL << BACK_PIN) |
    (1ULL << UP_PIN) |
    (1ULL << DOWN_PIN);

void Button::init() {
    pinMode(MENU_PIN, INPUT_PULLUP);
    pinMode(BACK_PIN, INPUT_PULLUP);
    pinMode(UP_PIN, INPUT_PULLUP);
    pinMode(DOWN_PIN, INPUT_PULLUP);
}

Input Button::readInput() {
    if (digitalRead(MENU_PIN) == LOW) return Input::Select;
    if (digitalRead(BACK_PIN) == LOW) return Input::Back;
    if (digitalRead(UP_PIN) == LOW) return Input::Up;
    if (digitalRead(DOWN_PIN) == LOW) return Input::Down;

    return Input::None;
}

Input Button::getWakeupInput() {
    if (esp_sleep_get_wakeup_cause() != ESP_SLEEP_WAKEUP_EXT1) {
        return Input::None;
    }

    uint64_t wakePins = esp_sleep_get_ext1_wakeup_status();

    if (wakePins & (1ULL << MENU_PIN)) return Input::Select;
    if (wakePins & (1ULL << BACK_PIN)) return Input::Back;
    if (wakePins & (1ULL << UP_PIN)) return Input::Up;
    if (wakePins & (1ULL << DOWN_PIN)) return Input::Down;

    return Input::None;
}

void Button::enableWakeup() {
    // Buttons are active LOW.
    esp_sleep_enable_ext1_wakeup(
        BUTTON_MASK,
        ESP_EXT1_WAKEUP_ANY_LOW
    );
}
