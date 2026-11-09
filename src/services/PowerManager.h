#pragma once

class BatteryInfo {
public:
    int percentage;
    float voltage;
    bool charging;
    bool usbConnected;
};

class PowerManager {
public:
    void init();
    BatteryInfo getBatteryInfo();

private:
    float readVoltage();
    int calculatePercentage(float voltage);
};