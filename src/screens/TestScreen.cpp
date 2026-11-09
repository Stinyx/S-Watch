#include "TestScreen.h"
#include "Images.h"
#include "services/PowerManager.h"

TestScreen::TestScreen(Draw& drawing, PowerManager& power)
    : drawing(drawing), power(power) {}

void TestScreen::draw() {
    // Draw clock
    drawing.setTimePartial();

    drawing.drawTime(0, 0);

    // Draw battery
    drawing.setBatteryPartial();

    BatteryInfo battery = power.getBatteryInfo();
    drawing.drawBattery(battery, 20, 150);
}

void TestScreen::enter() {}
void TestScreen::update() {}
void TestScreen::handleInput(Input input) {}