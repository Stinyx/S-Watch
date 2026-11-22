#pragma once

#include "app/Menu.h"

class SettingsScreen : public Menu {
public:
    explicit SettingsScreen();
    void enter() override;
    void update() override;
    void handleInput(Input input) override;
    void draw() override;

};
