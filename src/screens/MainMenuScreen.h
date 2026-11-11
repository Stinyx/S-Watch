#pragma once

#include "app/Screen.h"

class ScreenManager;
class TestScreen;
class InitialisingScreen;

class MainMenu : public Screen {
public:
    MainMenu(ScreenManager& manager,
             TestScreen& watchFace,
             InitialisingScreen& initialisingScreen);

    void enter() override;
    void handleInput(Input input) override;
    void draw() override;

private:
    ScreenManager& manager;
    TestScreen& watchFace;
    InitialisingScreen& initialisingScreen;
    int selectedItem = 0;
};
