#pragma once

#include "App/Screen.h"

class ScreenManager {
public:

    void setInitialScreen(Screen& screen);
    void setScreen(Screen& next);
    void handleInput(Input input);
    void update();
    void draw();
    void setWatchFace(Screen& screen);
    bool isOnWatchFace() const;
    bool isActive(const Screen& screen) const;

private:
    Screen* activeScreen = nullptr;
    Screen* watchFace = nullptr;
};

extern ScreenManager screenManager;
