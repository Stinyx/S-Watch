#include "ClockScreen.h"
#include "services/PowerManager.h"
#include "hardware/Display.h"

ClockScreen::ClockScreen(Draw& drawing, PowerManager& power)
    : drawing(drawing), power(power) {}

void ClockScreen::draw() {
    display.setFullWindow();

    display.firstPage();
    do {
        drawing.fill(FULLSCREEN);

        drawing.drawTime(15, 50);
        drawing.drawBattery(power.getBatteryInfo(), 20, 150);
        drawing.drawDate(20, 180);

    } while (display.nextPage());
}

void ClockScreen::update() {
    drawing.setPartial(15, 50, 185, 135);

    display.firstPage();
    do {
        drawing.fill(15, 50, 185, 135);

        drawing.drawTime(15, 50);
        drawing.drawBattery(power.getBatteryInfo(), 20, 150);
        drawing.drawDate(20, 180);

    } while (display.nextPage());

    /*
    // Update time
    drawing.setPartial(15, 50, 169, 71);
    display.firstPage();
    do {
        drawing.fill(15, 50, 169, 71);
        drawing.drawTime(15, 50);
    } while (display.nextPage());


    // Update battery
    drawing.setPartial(15, 130, 185, 25);
    display.firstPage();
    do {
       drawing.fill(15, 130, 185, 25);
        drawing.drawBattery(power.getBatteryInfo(), 20, 150);
    } while (display.nextPage());


    // Update date
    drawing.setPartial(15, 160, 185, 25);
    display.firstPage();
    do {
       drawing.fill(15, 160, 185, 25);
        drawing.drawDate(20, 180);
    } while (display.nextPage());
    */
}

void ClockScreen::enter() {}


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