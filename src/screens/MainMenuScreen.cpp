#include "MainMenuScreen.h"
#include "hardware/Display.h"

static const char* menuItems[] = {
    "Watch face",
    "Device info"
};

MainMenuScreen::MainMenuScreen(Draw& drawing)
    : drawing(drawing){}

void MainMenuScreen::enter() {
    selected = 0;
    selectionMade = false;
}

void MainMenuScreen::handleInput(Input input) {
    switch (input) {
        case Input::Up:
            selected = (selected + ITEM_COUNT - 1) % ITEM_COUNT;
            update();
            break;

        case Input::Down:
            selected = (selected + 1) % ITEM_COUNT;
            update();
            break;

        case Input::Select:
            selectionMade = true;
            break;

        default:
            break;
    }
}

void MainMenuScreen::draw() {
    display.setFullWindow();
    display.firstPage();

    do {
        drawing.fill(FULLSCREEN);
        drawing.drawText("MENU", 15, 25);

        for (int i = 0; i < ITEM_COUNT; i++) {
            int y = 65 + i * 40;

            if (i == selected) {
                display.drawRect(10, y - 15, 180, 30, GxEPD_BLACK);
                drawing.drawText("> ", 18, y + 4);
            } else {
                drawing.drawText("  ", 18, y + 4);
            }

            display.print(menuItems[i]);
        }

    } while (display.nextPage());
}


void MainMenuScreen::update() {

    drawing.setPartial(0, 45, 200, 85);
    display.firstPage();
    do{
        drawing.fill(0, 45, 200, 85);
        
        for (int i = 0; i < ITEM_COUNT; i++) {
            int y = 65 + i * 40;

            if (i == selected) {
                display.drawRect(10, y - 15, 180, 30, GxEPD_BLACK);
                drawing.drawText("> ", 18, y + 4);
            } else {
                drawing.drawText("  ", 18, y + 4);
            }

            display.print(menuItems[i]);
        }

    }while(display.nextPage());       

}


int MainMenuScreen::getSelection() const {
    return selected;
}

bool MainMenuScreen::consumeSelection() {
    bool result = selectionMade;
    selectionMade = false;
    return result;
}