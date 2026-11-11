#pragma once

#include "app/Screen.h"
#include "graphics/Draw.h"

class InfoScreen : public Screen {
public:
    explicit InfoScreen(Draw& draw); 
    void draw() override;
    void update() override;
private:
    Draw& drawing;
};