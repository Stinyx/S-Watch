#include "TestScreen.h"

TestScreen::TestScreen(Draw& draw)
    : draw(draw) {}

void TestScreen::enter() {
    draw.centeredText("12:45", 80);
    //draw.horizontalLine(100);
}