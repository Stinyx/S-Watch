#include "app/App.h"
#include "graphics/Draw.h"
#include "screens/TestScreen.h"

Display display;
Draw draw(display);
TestScreen testScreen(draw);

void App::begin() {
    testScreen.enter();
    /*
    display.begin();
    buttons.begin();
    storage.begin();
    timeService.begin();
    */

}

void App::update() {
       /*
    buttons.update();
    timeService.update();

    screenManager.update();
    */
}