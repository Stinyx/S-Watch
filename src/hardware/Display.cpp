#include "Display.h"

#include "GxEPD2_display_selection_new_style.h"


void Display::init() {
    epaperDisplay.init(115200);
    epaperDisplay.setRotation(0);
    epaperDisplay.setFont(&FreeMonoBold9pt7b);
    epaperDisplay.setTextColor(GxEPD_BLACK);
    epaperDisplay.setFullWindow();
    epaperDisplay.setTextSize(1);
}