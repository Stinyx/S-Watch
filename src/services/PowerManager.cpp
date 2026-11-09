#include "PowerManager.h"
#include <Arduino.h>

// Change this to your actual battery ADC pin.
#define BATTERY_ADC_PIN 34

// Example 100k + 100k voltage divider.
#define ADC_VOLTAGE_DIVIDER 2.0f

void PowerManager::init() {
    analogReadResolution(12);
    analogSetPinAttenuation(
        BATTERY_ADC_PIN,
        ADC_11db
    );
}

float PowerManager::readVoltage() {
    uint32_t millivolts =
        analogReadMilliVolts(BATTERY_ADC_PIN);

    return (millivolts / 1000.0f)
           * ADC_VOLTAGE_DIVIDER;
}

int PowerManager::calculatePercentage(float voltage) {
    // Simple initial estimate.
    int percentage = (int)(
        (voltage - 3.2f) / (4.2f - 3.2f) * 100.0f
    );

    return constrain(percentage, 0, 100);
}

BatteryInfo PowerManager::getBatteryInfo() {
    BatteryInfo info;

    info.voltage = readVoltage();
    info.percentage = calculatePercentage(info.voltage);

    return info;
}