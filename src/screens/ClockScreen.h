
#pragma once

#include "app/Screen.h"
#include "graphics/Draw.h"
#include "services/PowerManager.h"
#include "app/ScreenManager.h"

class ClockScreen : public Screen {
public:
    explicit ClockScreen(Draw& draw, PowerManager& power, ScreenManager& screenManager);
    void enter() override;
    void update() override;
    void handleInput(Input input) override;
    void draw() override;

private:
     Draw& drawing;
     PowerManager& power;
     ScreenManager& screenManager;
};
