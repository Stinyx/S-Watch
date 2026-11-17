#pragma once

#include "app/Screen.h"

class MainMenuScreen : public Screen {
public:
    explicit MainMenuScreen();
    void enter() override;
    void handleInput(Input input) override;
    void draw() override;
    void update() override;

private:
    int selected = 0;
    bool selectionMade = false;

    static constexpr int ITEM_COUNT = 2;
};