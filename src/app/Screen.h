#pragma once

#include "Input.h"
#define FULLSCREEN 0, 0, 200, 200

class Screen {
public:
    virtual ~Screen() = default;

    virtual void enter() {}
    virtual void update() {}
    virtual void handleInput(Input input) {}
    virtual void draw() = 0;
};