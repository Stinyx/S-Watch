#include "TestScreen.h"

TestScreen::TestScreen(Draw& drawing)
    : drawing(drawing) {}

void TestScreen::draw() {
    drawing.centeredText("12:45", 80);
}

void TestScreen::enter() {}
void TestScreen::update() {}
void TestScreen::handleInput(Input input) {}