#include "InfoScreen.h"
#include "hardware/Display.h"
#include "graphics/Draw.h"
#include "Screens.h"
#include "App/ScreenManager.h"

InfoScreen::InfoScreen() = default;

void InfoScreen::draw() {
    display.setFullWindow();
    display.firstPage();

    do {
        drawing.fill(FULLSCREEN);
        drawing.drawText("DEVICE INFO", 15, 30);
        drawing.drawText("S-Watch", 15, 70);
        drawing.drawText("ESP32-S3", 15, 95);
        drawing.drawText("BACK to menu", 15, 160);

    } while (display.nextPage());
}

void InfoScreen::handleInput(Input input) {
    if (input == Input::Back) {
        screenManager.setScreen(mainMenuScreen);
    }
}

void InfoScreen::update(){
    // nothing needed
}