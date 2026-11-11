#include "MainMenuScreen.h"
#include "hardware/Display.h"

static const char* menuItems[] = {
    "Watch face",
    "Device info"
};

void MainMenuScreen::enter() {
    selected = 0;
    selectionMade = false;
}

void MainMenuScreen::handleInput(Input input) {
    switch (input) {
        case Input::Up:
            selected = (selected + ITEM_COUNT - 1) % ITEM_COUNT;
            draw();
            break;

        case Input::Down:
            selected = (selected + 1) % ITEM_COUNT;
            draw();
            break;

        case Input::Select:
            selectionMade = true;
            break;

        default:
            break;
    }
}

void MainMenuScreen::draw() {
    display.setPartialWindow(0, 0, 200, 200);
    display.firstPage();

    do {
        display.fillScreen(GxEPD_WHITE);

        display.setFont(nullptr);
        display.setTextSize(2);
        display.setTextColor(GxEPD_BLACK);

        display.setCursor(15, 25);
        display.print("MENU");

        display.setTextSize(1);

        for (int i = 0; i < ITEM_COUNT; i++) {
            int y = 65 + i * 40;

            if (i == selected) {
                display.drawRect(10, y - 15, 180, 30, GxEPD_BLACK);
                display.setCursor(18, y + 4);
                display.print("> ");
            } else {
                display.setCursor(18, y + 4);
                display.print("  ");
            }

            display.print(menuItems[i]);
        }

    } while (display.nextPage());
}

int MainMenuScreen::getSelection() const {
    return selected;
}

bool MainMenuScreen::consumeSelection() {
    bool result = selectionMade;
    selectionMade = false;
    return result;
}