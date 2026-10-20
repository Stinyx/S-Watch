#pragma once

#include "Input.h"

class Screen {
public:
    virtual ~Screen() = default;

    virtual void enter() {}
    virtual void update() {}
    virtual void handleInput(Input input) {}
    virtual void draw() = 0;
};