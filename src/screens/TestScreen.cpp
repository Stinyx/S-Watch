#include "TestScreen.h"

TestScreen::TestScreen(Draw& drawing)
    : drawing(drawing) {}

void TestScreen::update() {
}

void TestScreen::handleInput(Input input) {
}

void TestScreen::draw(){
}

void TestScreen::enter() {
    drawing.centeredText("12:45", 80);
}