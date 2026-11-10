#include "InitialisingScreen.h"
#include "Images.h"
#include "hardware/Display.h"

InitialisingScreen::InitialisingScreen(Draw& drawing)
    : drawing(drawing) {}

void InitialisingScreen::draw() {
    drawing.drawImage(flowersakuralogo);

}

void InitialisingScreen::enter() {}
void InitialisingScreen::update() {}
void InitialisingScreen::handleInput(Input input) {}