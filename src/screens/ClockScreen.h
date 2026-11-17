#pragma once

#include "app/Screen.h"

class ClockScreen : public Screen {
public:
    explicit ClockScreen();
    void enter() override;
    void update() override;
    void handleInput(Input input) override;
    void draw() override;

};
