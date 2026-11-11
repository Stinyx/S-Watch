#pragma once

#include "app/Input.h"

class Button {
public:
    void init();

    // Returns the button that woke the watch, if any.
    Input getWakeupInput();

    // Reads buttons while the watch is already awake.
    Input readInput();

    // Configure buttons as deep-sleep wake sources.
    void enableWakeup();

private:
    Input lastInput = Input::None;
    unsigned long lastChange = 0;
    Input candidateInput = Input::None;
};

