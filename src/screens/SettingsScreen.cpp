#include "SettingsScreen.h"
#include "hardware/Display.h"
#include "graphics/Draw.h"
#include "Screens.h"
#include "services/ScreenManager.h"

// Initialise the options directly in the class constructor
SettingsScreen::SettingsScreen(){

    newSelection("SETTING 1", NULL);
    newSelection("SETTING 2", NULL);
    newSelection("SETTING 3", NULL);
    newSelection("SETTING 4", NULL);
    newSelection("SETTING 5", NULL);
    newSelection("SETTING 6", NULL);
    newSelection("SETTING 7", NULL);
    newSelection("SETTING 8", NULL);
    newSelection("SETTING 9", NULL);

}

// Reset current menu selection upon entering the menu
void SettingsScreen::enter() {
    reset();
}

// Handle the input on the current screen
void SettingsScreen::handleInput(Input input) {
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
            screenManager.setScreen(mainMenuScreen);
            break;

        default:
            break;
    }
}

// Draw the screen upon first entering it 
void SettingsScreen::draw() {
    display.setFullWindow();
    display.firstPage();

    do {
        drawing.fill(FULLSCREEN);
        drawing.drawText("SETTINGS", 15, 25);

        drawMenuItems();

    } while (display.nextPage());
}

// Partially update the screen after button interactions
void SettingsScreen::update() {

    drawing.setPartial(0, 40, 200, 200);
    display.firstPage();
    do{
        drawing.fill(0, 40, 200, 200);
        
        drawMenuItems();

    }while(display.nextPage());       

}