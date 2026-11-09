#include "TestScreen.h"
#include "Images.h"
#include "services/PowerManager.h"
#include "hardware/Display.h"

TestScreen::TestScreen(Draw& drawing, PowerManager& power)
    : drawing(drawing), power(power) {}

void TestScreen::draw() {
    // 1. Refresh the time area.
    drawing.setTimePartial();

    display.firstPage();
    do {
        drawing.drawTime(0, 0);
    } while (display.nextPage());

    // 2. Read battery information.
    BatteryInfo battery = power.getBatteryInfo();

    // 3. Refresh the battery area independently.
    drawing.setBatteryPartial();

    display.firstPage();
    do {
        display.fillRect(15, 130, 100, 40, GxEPD_WHITE);
        drawing.drawBattery(battery, 20, 150);
    } while (display.nextPage());
}

void TestScreen::enter() {}
void TestScreen::update() {}
void TestScreen::handleInput(Input input) {}