
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

        // Full refresh when changing screens
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

    void setWatchFace(Screen& screen) {
        watchFace = &screen;
    }

    bool isOnWatchFace() const {
        return activeScreen == watchFace;
    }

    bool isActive(const Screen& screen) const {
        return activeScreen == &screen;
    }

private:
    Screen* activeScreen = nullptr;
    Screen* watchFace = nullptr;
};
