
#include "MainMenuScreen.h"
#include "app/ScreenManager.h"
#include "screens/TestScreen.h"
#include "screens/InitialisingScreen.h"

void MainMenu::enter() {
    selectedItem = 0;
}

void MainMenu::handleInput(Input input) {
    switch (input) {
        case Input::Up:
            selectedItem = (selectedItem + 1) % 2;
            draw();
            break;

        case Input::Down:
            selectedItem = (selectedItem + 1) % 2;
            draw();
            break;

        case Input::Select:
            if (selectedItem == 0) {
                manager.setScreen(watchFace);
            } else {
                manager.setScreen(initialisingScreen);
            }
            break;

        case Input::Back:
            manager.setScreen(watchFace);
            break;

        default:
            break;
    }
}
