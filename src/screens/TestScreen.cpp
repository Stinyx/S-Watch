#include "TestScreen.h"
#include "Images.h"

TestScreen::TestScreen(Draw& drawing)
    : drawing(drawing) {}

void TestScreen::draw() {
    drawing.drawImage(flowersakuralogo);
}

void TestScreen::enter() {}
void TestScreen::update() {}
void TestScreen::handleInput(Input input) {}