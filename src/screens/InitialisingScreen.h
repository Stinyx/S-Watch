#pragma once

#include "app/Screen.h"
#include "graphics/Draw.h"

class InitialisingScreen : public Screen {
public:
    explicit InitialisingScreen(Draw& draw);
    void enter() override;
    void update() override;
    void handleInput(Input input) override;
    void draw() override;

private:
     Draw& drawing;
};