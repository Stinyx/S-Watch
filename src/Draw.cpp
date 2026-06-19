#include "Draw.h"

// GxEPD setup (Drawing on e-ink screen)
void gxepd_init(){  
  display.init(115200);
  display.setRotation(0);
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_BLACK);
  display.setFullWindow();
  display.setTextSize(1);
}