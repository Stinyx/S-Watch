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

    newSelection("Settings", [](){
        screenManager.setScreen(settingsScreen);
    });

    newSelection("TEST 1", NULL);
    newSelection("TEST 2", NULL);
    newSelection("TEST 3", NULL);
    newSelection("TEST 4", NULL);
    newSelection("TEST 5", NULL);
    newSelection("TEST 6", NULL);
    newSelection("TEST 7", NULL);
    newSelection("TEST 8", NULL);
    newSelection("TEST 9", NULL);

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

        drawMenuItems();

    } while (display.nextPage());
}


void MainMenuScreen::update() {

    drawing.setPartial(0, 40, 200, 200);
    display.firstPage();
    do{
        drawing.fill(0, 40, 200, 200);
        
        drawMenuItems();

    }while(display.nextPage());       

}