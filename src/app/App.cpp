#include "app/App.h"
#include "graphics/Draw.h"
#include "screens/TestScreen.h"

Draw draw;
TestScreen testScreen(draw);

void App::begin() {
    display.init();

    display.setFullWindow();
    display.firstPage();

    do {
        testScreen.draw();
    } while (display.nextPage());
}

void App::update() {}