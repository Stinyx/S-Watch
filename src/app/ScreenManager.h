
#pragma once

#include "Screen.h"

class ScreenManager {
public:
    void setScreen(Screen& next) {
        if (activeScreen == &next) {
            return;
        }

        activeScreen = &next;
        activeScreen->enter();
        activeScreen->draw();
    }

    void handleInput(Input input) {
        if (activeScreen != nullptr) {
            activeScreen->handleInput(input);
        }
    }

    void update() {
        if (activeScreen != nullptr) {
            activeScreen->update();
        }
    }

    void draw() {
        if (activeScreen != nullptr) {
            activeScreen->draw();
        }
    }

private:
    Screen* activeScreen = nullptr;
};
