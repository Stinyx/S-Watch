#include "Display.h"

GxEPD2_DISPLAY_CLASS<GxEPD2_DRIVER_CLASS, 200> display(
    GxEPD2_DRIVER_CLASS(33, 34, 35, 36)
);

void Display::init() {
    SPI.begin(47, 46, 48, 33);

    display.init(115200);
    display.setRotation(0);
    display.setFont(&FreeMonoBold9pt7b);
    display.setTextColor(GxEPD_BLACK);
    display.setFullWindow();
    display.setTextSize(1);
}