#pragma once

#include "app/Screen.h"

class InitialisingScreen : public Screen {
public:
    explicit InitialisingScreen();
    void draw() override;
};