
#pragma once

#include "app/Screen.h"
#include "graphics/Draw.h"
#include "services/PowerManager.h"

class ClockScreen : public Screen {
public:
    explicit ClockScreen(Draw& draw, PowerManager& power);
    void enter() override;
    void update() override;
    void handleInput(Input input) override;
    void draw() override;

private:
     Draw& drawing;
     PowerManager& power;
};
