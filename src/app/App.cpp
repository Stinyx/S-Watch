#include "app/App.h"
#include "graphics/Draw.h"
#include "screens/TestScreen.h"

Draw draw;
TestScreen testScreen(draw);
Display displayController;

void App::begin() {
    displayController.init();

    display.firstPage();
    do {
        testScreen.draw();
    } while (display.nextPage());
}

void App::update() {}