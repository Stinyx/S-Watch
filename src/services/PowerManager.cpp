#include "PowerManager.h"
#include <Arduino.h>

#define BATTERY_ADC_PIN 9
#define CHARGING_STATUS_PIN 10
#define USB_DETECT_PIN 21

#define ADC_VOLTAGE_DIVIDER ((360.0f + 100.0f) / 360.0f)

void PowerManager::init() {
    analogReadResolution(12);
    analogSetPinAttenuation(BATTERY_ADC_PIN, ADC_11db);

    pinMode(CHARGING_STATUS_PIN, INPUT_PULLUP);
    pinMode(USB_DETECT_PIN, INPUT);
}

float PowerManager::readVoltage() {
    uint32_t millivolts = analogReadMilliVolts(BATTERY_ADC_PIN);

    return (millivolts / 1000.0f) * ADC_VOLTAGE_DIVIDER;
}

int PowerManager::calculatePercentage(float voltage) {
    int percentage = (int)(
        (voltage - 3.2f) / (3.91f - 3.2f) * 100.0f
    );

    return constrain(percentage, 0, 100);
}

BatteryInfo PowerManager::getBatteryInfo() {
    BatteryInfo info;

    info.voltage = readVoltage();
    info.percentage = calculatePercentage(info.voltage);
    info.usbConnected = digitalRead(USB_DETECT_PIN) == HIGH;
    info.charging = info.usbConnected && digitalRead(CHARGING_STATUS_PIN) == LOW;
    
    return info;
}