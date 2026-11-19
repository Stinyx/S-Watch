#include "MainMenuScreen.h"
#include "hardware/Display.h"
#include "graphics/Draw.h"
#include "Screens.h"
#include "services/ScreenManager.h"

MainMenuScreen::MainMenuScreen(){
    newSelection("Watch Face", [](){
        screenManager.setScreen(clockScreen);
    });

    newSelection("Device Info", [](){
        screenManager.setScreen(infoScreen);
    });
}

void MainMenuScreen::enter() {
    reset();
}

void MainMenuScreen::handleInput(Input input) {
    switch (input) {
        case Input::Up:
            moveUp();
            update();
            break;

        case Input::Down:
            moveDown();
            update();
            break;

        case Input::Select:
            activate();
            break;
        
        case Input::Back:
            screenManager.setScreen(clockScreen);
            break;

        default:
            break;
    }
}


void MainMenuScreen::draw() {
    display.setFullWindow();
    display.firstPage();

    do {
        drawing.fill(FULLSCREEN);
        drawing.drawText("MENU", 15, 25);

        for (int i = 0; i < size(); i++) {
            int y = 65 + i * 40;

            if (i == getSelected()) {
                display.drawRect(10, y - 15, 180, 30, GxEPD_BLACK);
                drawing.drawText("> ", 18, y + 4);
            } else {
                drawing.drawText("  ", 18, y + 4);
            }

            display.print(getSelection(i).name);
        }

    } while (display.nextPage());
}


void MainMenuScreen::update() {

    drawing.setPartial(0, 45, 200, 85);
    display.firstPage();
    do{
        drawing.fill(0, 45, 200, 85);
        
        for (int i = 0; i < size(); i++) {
            int y = 65 + i * 40;

            if (i == getSelected()) {
                display.drawRect(10, y - 15, 180, 30, GxEPD_BLACK);
                drawing.drawText("> ", 18, y + 4);
            } else {
                drawing.drawText("  ", 18, y + 4);
            }

            display.print(getSelection(i).name);
        }

    }while(display.nextPage());       

}