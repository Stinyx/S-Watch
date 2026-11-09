#include "PowerManager.h"
#include <Arduino.h>

#define BATTERY_ADC_PIN 9
#define CHARGING_STATUS_PIN 10
#define USB_DETECT_PIN 21

// Example 100k + 100k voltage divider.
#define ADC_VOLTAGE_DIVIDER 2.0f

void PowerManager::init() {
    analogReadResolution(12);
    analogSetPinAttenuation(BATTERY_ADC_PIN, ADC_11db);

    pinMode(CHARGING_STATUS_PIN, INPUT);
    pinMode(USB_DETECT_PIN, INPUT);
}

float PowerManager::readVoltage() {
    // GPIO 9 is connected to the Watchy V3 battery-sense circuit.
    // Calibrate this conversion against a multimeter.
    uint32_t millivolts =
        analogReadMilliVolts(BATTERY_ADC_PIN);

    // Do not assume an external 2:1 divider.
    // Set this factor to match the V3 board's actual circuit.
    return (millivolts / 1000.0f) * ADC_VOLTAGE_DIVIDER;
}

int PowerManager::calculatePercentage(float voltage) {
    int percentage = (int)(
        (voltage - 3.2f) / (4.2f - 3.2f) * 100.0f
    );

    return constrain(percentage, 0, 100);
}

BatteryInfo PowerManager::getBatteryInfo() {
    BatteryInfo info;

    info.voltage = readVoltage();
    info.percentage = calculatePercentage(info.voltage);
    info.charging = digitalRead(CHARGING_STATUS_PIN) == LOW;
    info.usbConnected = digitalRead(USB_DETECT_PIN) == HIGH;

    return info;
}