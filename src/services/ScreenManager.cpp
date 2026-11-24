#include "App/Screen.h"
#include "ScreenManager.h"

// Sets the intial screen upon first boot
void ScreenManager::setInitialScreen(Screen& screen) {
    activeScreen = &screen;
    activeScreen->enter();
}

// Sets the current screen to the given screen
//
// Parameters: Screen nextScreen
void ScreenManager::setScreen(Screen& next) {
    if (activeScreen == &next) {
        return;
    }

    activeScreen = &next;
    activeScreen->enter();

    // Full refresh when changing screens
    activeScreen->draw();
}

// Handles the input on the current screen
//
// Parameters: Input input
void ScreenManager::handleInput(Input input) {
    if (activeScreen != nullptr) {
        activeScreen->handleInput(input);
    }
}

// Redraws the current screen partially
void ScreenManager::update() {
    if (activeScreen != nullptr) {
        activeScreen->update();
    }
}

// Redraws the current screen upon entering a new one
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


