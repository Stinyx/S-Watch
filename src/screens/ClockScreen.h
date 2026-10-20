#pragma once

#include "app/Screen.h"
#include "watchfaces/WatchFace.h"

class ClockScreen : public Screen {
public:
    void enter() override;
    void update() override;
    void handleInput(Input input) override;
    void draw() override;

private:
    WatchFace* activeWatchFace = nullptr;
};