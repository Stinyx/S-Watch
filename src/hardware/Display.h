#pragma once

#include <GxEPD2_BW.h>
#include "GxEPD2_display_selection_new_style.h"
#include <Fonts/FreeMonoBold9pt7b.h>

using EpaperDisplay =
    GxEPD2_DISPLAY_CLASS<GxEPD2_DRIVER_CLASS, 200>;

extern EpaperDisplay epaperDisplay;

class Display {
public:
    void init();
};