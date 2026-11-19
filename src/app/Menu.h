#pragma once

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

private:
    int selected = 0;
    std::vector<Selection> selections;
};