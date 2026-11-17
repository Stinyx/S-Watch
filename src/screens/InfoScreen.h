#pragma once

#include "app/Screen.h"

class InfoScreen : public Screen {
public:
    explicit InfoScreen(); 
    void draw() override;
    void update() override;
    void handleInput(Input input) override;
};