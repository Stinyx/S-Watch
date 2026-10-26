#include "Draw.h"

Draw::Draw(Display& display)
    : display(display) {}

void Draw::centeredText(const char* text, int y) {
    auto& epd = display.raw();

    int16_t x1, y1;
    uint16_t w, h;

    epd.getTextBounds(text, 0, 0, &x1, &y1, &w, &h);

    int x = (epd.width() - static_cast<int>(w)) / 2 - x1;

    epd.setCursor(x, y);
    epd.print(text);
}

/*
void Draw::horizontalLine(int y) {
    auto& epd = display.raw();

    epd.drawFastHLine(
        0, y, epd.width(), GxEPD_BLACK
    );
}
*/