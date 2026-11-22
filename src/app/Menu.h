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

    void newSelection(char* name, void (*callback)()) {
        this->selections.emplace_back(name, callback);
    }

    void moveUp() {
        if (selections.empty()) return;
        selected = (selected + selections.size() - 1) % selections.size();
    }

    void moveDown() {
        if (selections.empty()) return;
        selected = (selected + 1) % selections.size();
    }

    void reset(){
        this->selected = 0;
    }

    void activate() {
        if (selections.empty()) return;

        if (selections[selected].callback == NULL) {
            return;
        }

        if (selections[selected].callback) {
            selections[selected].callback();
        }
    }

    int size(){
        return selections.size();
    }

    int getSelected(){
        return this->selected;
    }

    const Selection& getSelection(size_t index) const {
        return selections[index];
    }

    void drawMenuItems() {
        const int visibleItems = 5;
        const int lineHeight = 24;
        const int startY = 70;

        const int totalItems = size();
        const int selected = getSelected();

        if (totalItems == 0) return;

        // Calculate which item should appear first.
        // Keep the selected item visible by scrolling the entire list.
        int menuScrollOffset = 0;

        if (selected >= visibleItems) {
            menuScrollOffset = selected - visibleItems + 1;
        }

        // Determine whether there are more items above or below.
        bool showTopArrow = menuScrollOffset > 0;
        bool showBottomArrow =
            menuScrollOffset + visibleItems < totalItems;

        // Draw the arrow indicating more items above.
        if (showTopArrow) {
            display.setCursor(94, 53);
            display.print("^");
        }

        // Draw the visible selections.
        for (int row = 0; row < visibleItems; row++) {

            int selectionIndex = menuScrollOffset + row;

            if (selectionIndex >= totalItems) {
                break;
            }

            int y = startY + row * lineHeight;

            const Selection& selection = getSelection(selectionIndex);

            display.setCursor(18, y);

            // Draw the selection indicator at the actual selected item.
            if (selectionIndex == selected) {
                display.print("> ");
            } else {
                display.print("  ");
            }

            display.print(selection.name);
        }

        // Draw the arrow indicating more items below.
        if (showBottomArrow) {
            display.setCursor(94, 190);
            display.print("v");
        }
    }

private:
    int selected = 0;
    std::vector<Selection> selections;
};