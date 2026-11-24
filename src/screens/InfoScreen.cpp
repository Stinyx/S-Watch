#include "InfoScreen.h"
#include "hardware/Display.h"
#include "graphics/Draw.h"
#include "Screens.h"
#include "services/ScreenManager.h"

InfoScreen::InfoScreen() = default;

// Draw the device information on the screen
void InfoScreen::draw() {
    display.setFullWindow();
    display.firstPage();

    do {
        drawing.fill(FULLSCREEN);
        drawing.drawText("DEVICE INFO", 15, 30);
        drawing.drawText("hello :3", 15, 70);
        drawing.drawText("ver: idk", 15, 95);
        drawing.drawText("Creator: Stinyx", 15, 120);
        drawing.drawText("BACK to menu", 15, 160);

    } while (display.nextPage());
}

// Handle button input on current screen
void InfoScreen::handleInput(Input input) {
    if (input == Input::Back) {
        screenManager.setScreen(mainMenuScreen);
    }
}