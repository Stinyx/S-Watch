#pragma once

#include "app/Input.h"

class Button {
public:
    void init();
    Input getWakeupInput();
    Input readInput();
    void enableWakeup();

private:
    Input lastInput = Input::None;
    unsigned long lastChange = 0;
    Input candidateInput = Input::None;
};

