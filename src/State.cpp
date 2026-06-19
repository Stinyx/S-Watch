#include "State.h"
#include "debug.h"  
#include "UserInterface.h"
#include "Settings.h"

// Watch states
enum WatchState currentState;
WatchState lastState = SETTINGS;
int state = 0;

// If watchstate changes, do something only once
void onStateEnter(WatchState state) {
  // Reset text size (AND MAYBE OTHER THINGS IN THE FUTURE)
  display.setTextSize(1);
  refresh_display();

  switch(state) {

    case CLOCK:
      display.setTextSize(2);
      if(drawBackground) draw_image(0, 0, FULLSCREEN, FULLSCREEN, clk_bg);
      if(drawDate) draw_date();
      draw_time();
      break;

    case IMAGE:
      draw_image(0, 0, FULLSCREEN, FULLSCREEN, flowersakuralogo);  
      break;

    case SETTINGS:
      currentMenuSelected = 0;
      if(drawBackground) draw_image(0, 0, FULLSCREEN, FULLSCREEN, cfg_bg);
      draw_settings();
      break;

    case ALARM:
      if(drawBackground) draw_image(0, 0, FULLSCREEN, FULLSCREEN, alm_bg);
      break;

    case TIMER:
      if(drawBackground) draw_image(0, 0, FULLSCREEN, FULLSCREEN, tmr_bg);
      break;

    case NAVIGATION:
      currentNavigationSelected = 0;
      if(drawBackground) draw_image(0, 0, FULLSCREEN, FULLSCREEN, nav_bg);
      draw_navigation();
      break;

    case ABOUT:
      if(drawBackground) draw_image(0, 0, FULLSCREEN, FULLSCREEN, abt_bg);
      draw_about();
      break;

    default:
      break;
  }
}