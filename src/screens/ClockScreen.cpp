#include "ClockScreen.h"
#include "services/PowerManager.h"
#include "hardware/Display.h"

ClockScreen::ClockScreen(Draw& drawing, PowerManager& power)
    : drawing(drawing), power(power) {}

void ClockScreen::draw() {
    display.setFullWindow();

    display.firstPage();
    do {
        display.fillScreen(GxEPD_WHITE);

        BatteryInfo battery = power.getBatteryInfo();

        drawing.drawTime(0, 0);
        drawing.drawBattery(battery, 20, 150);
        drawing.drawDate(20, 180);

    } while (display.nextPage());
}

void ClockScreen::enter() {}
void ClockScreen::update() {}

void ClockScreen::handleInput(Input input) {
    switch (input) {
        case Input::Select:
            // Open your menu screen here.
            break;

        case Input::Back:
            break;

        case Input::Up:
            break;

        case Input::Down:
            break;

        default:
            break;
    }
}