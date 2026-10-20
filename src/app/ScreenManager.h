#pragma once

#include "Screen.h"

class ScreenManager {
public:
    void setScreen(Screen* screen);
    void update();
    void handleInput(Input input);
    void draw();

private:
    Screen* currentScreen = nullptr;
};