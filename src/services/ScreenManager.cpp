#include "App/Screen.h"
#include "ScreenManager.h"


void ScreenManager::setInitialScreen(Screen& screen) {
    activeScreen = &screen;
    activeScreen->enter();
}

void ScreenManager::setScreen(Screen& next) {
    if (activeScreen == &next) {
        return;
    }

    activeScreen = &next;
    activeScreen->enter();

    // Full refresh when changing screens
    activeScreen->draw();
}

void ScreenManager::handleInput(Input input) {
    if (activeScreen != nullptr) {
        activeScreen->handleInput(input);
    }
}

void ScreenManager::update() {
    if (activeScreen != nullptr) {
        activeScreen->update();
    }
}

void ScreenManager::draw() {
    if (activeScreen != nullptr) {
        activeScreen->draw();
    }
}

void ScreenManager::setWatchFace(Screen& screen) {
    watchFace = &screen;
}

bool ScreenManager::isOnWatchFace() const {
    return activeScreen == watchFace;
}

bool ScreenManager::isActive(const Screen& screen) const {
    return activeScreen == &screen;
}


