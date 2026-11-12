#include "InitialisingScreen.h"
#include "Images.h"
#include "hardware/Display.h"

InitialisingScreen::InitialisingScreen(Draw& drawing)
    : drawing(drawing) {}

void InitialisingScreen::draw() {
    display.setFullWindow();

    display.firstPage();
    do{
        drawing.drawImage(flowersakuralogo);
        drawing.drawText("S-Watch Initialising...", 20, 190);
    }while(display.nextPage());
    

}

void InitialisingScreen::enter() {}
void InitialisingScreen::update() {}
void InitialisingScreen::handleInput(Input input) {}