#include "TestScreen.h"
#include "Images.h"
#include "services/PowerManager.h"
#include "hardware/Display.h"

TestScreen::TestScreen(Draw& drawing, PowerManager& power)
    : drawing(drawing), power(power) {}

void TestScreen::draw() {
    BatteryInfo battery = power.getBatteryInfo();

    drawing.drawTime(0, 0);
    drawing.drawBattery(battery, 20, 150);
    drawing.drawDate(20, 180);

}

void TestScreen::enter() {}
void TestScreen::update() {}
void TestScreen::handleInput(Input input) {}