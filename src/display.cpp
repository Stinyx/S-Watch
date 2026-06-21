#include <GxEPD2_BW.h>
#include "GxEPD2_display_selection_new_style.h"

// Had problems with duplicate library includes so this was the solution, works so whatever
GxEPD2_DISPLAY_CLASS<GxEPD2_DRIVER_CLASS, 200> display(
  GxEPD2_DRIVER_CLASS(EPD_CS, 17, 16, 4)
);