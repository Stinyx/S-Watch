#include "TestScreen.h"
#include "Images.h"

TestScreen::TestScreen(Draw& drawing)
    : drawing(drawing) {}

void TestScreen::draw() {
    //drawing.drawImage(flowersakuralogo);
    drawing.drawTime(0, 0);
}

void TestScreen::enter() {}
void TestScreen::update() {}
void TestScreen::handleInput(Input input) {}