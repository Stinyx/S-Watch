#include "PowerManager.h"
#include <Arduino.h>

#define BATTERY_ADC_PIN 9
#define CHARGING_STATUS_PIN 10
#define USB_DETECT_PIN 21

#define ADC_VOLTAGE_DIVIDER ((360.0f + 100.0f) / 360.0f)

// Initialises the power manager
void PowerManager::init() {
    analogReadResolution(12);
    analogSetPinAttenuation(BATTERY_ADC_PIN, ADC_11db);

    pinMode(CHARGING_STATUS_PIN, INPUT_PULLUP);
    pinMode(USB_DETECT_PIN, INPUT);
}

// Reads voltage from given pin and returns it in volts
//
// Return value: float volts
float PowerManager::readVoltage() {
    uint32_t millivolts = analogReadMilliVolts(BATTERY_ADC_PIN);

    return (millivolts / 1000.0f) * ADC_VOLTAGE_DIVIDER;
}

// Calculates percentage from inputted volts
//
// Parameters: float voltage
// Return value: int percentage
int PowerManager::calculatePercentage(float voltage) {
    int percentage = (int)(
        (voltage - 3.2f) / (3.91f - 3.2f) * 100.0f
    );

    return constrain(percentage, 0, 100);
}

// Returns info about current battery statistics
//
// Return value: BatteryInfo object
BatteryInfo PowerManager::getBatteryInfo() {
    BatteryInfo info;

    info.voltage = readVoltage();
    info.percentage = calculatePercentage(info.voltage);
    info.usbConnected = digitalRead(USB_DETECT_PIN) == HIGH;
    info.charging = info.usbConnected && digitalRead(CHARGING_STATUS_PIN) == LOW;
    
    return info;
}