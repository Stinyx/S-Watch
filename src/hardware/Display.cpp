#include "Display.h"

GxEPD2_DISPLAY_CLASS<GxEPD2_DRIVER_CLASS, 200> display(
    GxEPD2_DRIVER_CLASS(EPD_CS, 17, 16, 4)
);

void Display::init() {
    display.init(115200);
    display.setRotation(0);
    display.setFont(&FreeMonoBold9pt7b);
    display.setTextColor(GxEPD_BLACK);
    display.setFullWindow();
    display.setTextSize(1);
}