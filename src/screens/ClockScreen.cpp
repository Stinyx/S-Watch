#include "ClockScreen.h"
#include "Images.h"
#include "services/PowerManager.h"
#include "services/TimeManager.h"
#include "MainMenuScreen.h"
#include "hardware/Display.h"

ClockScreen::ClockScreen(Draw& drawing, PowerManager& power, ScreenManager& screenManager)
    : drawing(drawing), power(power), screenManager(screenManager){}

void ClockScreen::draw() {
    display.setFullWindow();

    display.firstPage();
    do {
        drawing.fill(FULLSCREEN);
        drawing.drawImage(loveflower);

        drawing.drawTime(15, 50);
        drawing.drawBattery(power.getBatteryInfo(), 150, 25, false, false); // 20 150 originally under time 
        drawing.drawDate(15, 25, false); // 20 originally under Battery

    } while (display.nextPage());
}

void ClockScreen::update() {
    drawing.setPartial(15, 10, 185, 125);  // 15 50 185 135 originally for the whole stack

    display.firstPage();
    do {
        drawing.fill(15, 10, 185, 125); // 15 50 185 135 originally

        drawing.drawImage(loveflower);

        drawing.drawTime(15, 50);
        drawing.drawBattery(power.getBatteryInfo(), 150, 25, false, false); // 20 150 originally under time 
        drawing.drawDate(15, 25, false); // 20 180 originally under Battery

    } while (display.nextPage());

}

void ClockScreen::enter() {
    timeManager.update();
}


void ClockScreen::handleInput(Input input) {
    switch (input) {
        case Input::Select:
                screenManager.setScreen();
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