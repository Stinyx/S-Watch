#pragma once

#include "hardware/Display.h"
#include "Screen.h"
#include <vector>

class Selection {
public:
    Selection(char* name, void (*callback)())
        : name(name), callback(callback) {}

    void (*callback)();
    char* name;
};

class Menu : public Screen {
public:

    // Creates a new selection option for the given menu
    void newSelection(char* name, void (*callback)()) {
        this->selections.emplace_back(name, callback);
    }

    // Move up the options in the menu
    void moveUp() {
        if (selections.empty()) return;
        selected = (selected + selections.size() - 1) % selections.size();
    }

    // Move down the options in the menu
    void moveDown() {
        if (selections.empty()) return;
        selected = (selected + 1) % selections.size();
    }

    // Reset the option selection position to zero
    void reset(){
        this->selected = 0;
    }

    // Activates the callback function for the given option
    void activate() {
        if (selections.empty()) return;

        if (selections[selected].callback == NULL) {
            return;
        }

        if (selections[selected].callback) {
            selections[selected].callback();
        }
    }

    // Returns the count of the options
    int size(){
        return selections.size();
    }

    // Returns the current index of the menu selection
    int getSelected(){
        return this->selected;
    }

    // Returns the selection at a given selection index
    const Selection& getSelection(size_t index) const {
        return selections[index];
    }

    // Draws the options in the current menu
    void drawMenuItems() {
        const int visibleItems = 5;
        const int lineHeight = 24;
        const int startY = 70;

        const int totalItems = size();
        const int selected = getSelected();

        if (totalItems == 0) return;

        int menuScrollOffset = 0;

        if (selected >= visibleItems) {
            menuScrollOffset = selected - visibleItems + 1;
        }

        bool showTopArrow = menuScrollOffset > 0;
        bool showBottomArrow =
            menuScrollOffset + visibleItems < totalItems;

        if (showTopArrow) {
            display.setCursor(94, 53);
            display.print("^");
        }

        for (int row = 0; row < visibleItems; row++) {

            int selectionIndex = menuScrollOffset + row;

            if (selectionIndex >= totalItems) {
                break;
            }

            int y = startY + row * lineHeight;

            const Selection& selection = getSelection(selectionIndex);

            display.setCursor(18, y);

            if (selectionIndex == selected) {
                display.print("> ");
            } else {
                display.print("  ");
            }

            display.print(selection.name);
        }

        if (showBottomArrow) {
            display.setCursor(94, 190);
            display.print("v");
        }
    }

private:
    int selected = 0;
    std::vector<Selection> selections;
};