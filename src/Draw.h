
// GxEPD2
#include <GxEPD2_BW.h>
#include <Fonts/FreeMonoBold9pt7b.h>
#include "GxEPD2_display_selection_new_style.h"

#include "images.h"
#include "clockfaces.h"

#define DISPLAYWIDTH 200
#define DISPLAYHEIGHT 200
#define FULLSCREEN 200

template<typename... Funcs>
void epdDraw(Funcs... funcs)
{
  display.firstPage();
  do {
    (funcs(), ...);   // calls all functions
  } while (display.nextPage());
}

template<typename... Funcs>
void epdDrawPartial(int x, int y, int w, int h, Funcs... funcs)
{
  display.setPartialWindow(x, y, w, h);

  display.firstPage();
  do {
    (funcs(), ...);
  } while (display.nextPage());
}

// GxEPD setup (Drawing on e-ink screen)
void gxepd_init();