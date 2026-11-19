#pragma once

#include "app/Menu.h"

class MainMenuScreen : public Menu {
public:
    explicit MainMenuScreen();
    void enter() override;
    void handleInput(Input input) override;
    void draw() override;
    void update() override;

private:
};