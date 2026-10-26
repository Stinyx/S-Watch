
#pragma once

#include "app/Screen.h"
#include "graphics/Draw.h"
//#include "watchfaces/MinimalWatchFace.h"

class TestScreen : public Screen {
public:
    explicit TestScreen(Draw& draw);
    void enter() override;
    void update() override;
    void handleInput(Input input) override;
    void draw() override;

private:
    //WatchFace* activeWatchFace = nullptr;
     Draw& draw;
};
