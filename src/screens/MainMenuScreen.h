#pragma once

#include "app/Screen.h"
#include "graphics/Draw.h"

class MainMenuScreen : public Screen {
public:
    explicit MainMenuScreen(Draw& draw);
    void enter() override;
    void handleInput(Input input) override;
    void draw() override;
    void update() override;

    int getSelection() const;
    bool consumeSelection();

private:
     Draw& drawing;
    int selected = 0;
    bool selectionMade = false;

    static constexpr int ITEM_COUNT = 2;
};