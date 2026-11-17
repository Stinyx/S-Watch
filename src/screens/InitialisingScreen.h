#pragma once

#include "app/Screen.h"

class InitialisingScreen : public Screen {
public:
    explicit InitialisingScreen();
    void enter() override;
    void update() override;
    void handleInput(Input input) override;
    void draw() override;

};