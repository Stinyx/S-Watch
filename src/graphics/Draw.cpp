#include "Draw.h"
#include "hardware/Display.h"

void Draw::centeredText(const char* text, int y) {
    int16_t x1, y1;
    uint16_t w, h;

    display.getTextBounds(
        text, 0, 0, &x1, &y1, &w, &h
    );

    int x = (display.width() - static_cast<int>(w)) / 2 - x1;

    display.setCursor(x, y);
    display.print(text);
}
