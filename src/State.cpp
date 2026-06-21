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
  //refresh_display();

  switch(state) {

    case CLOCK:
      display.setTextSize(2);
      draw_background(clk_bg);
      if(drawDate) draw_date();
      draw_time();
      break;

    case IMAGE:
      draw_image(0, 0, FULLSCREEN, FULLSCREEN, flowersakuralogo);  
      break;

    case SETTINGS:
      currentMenuSelected = 0;
      draw_background(cfg_bg);
      draw_settings();
      break;

    case ALARM:
      draw_background(alm_bg);
      break;

    case TIMER:
      draw_background(tmr_bg);
      break;

    case NAVIGATION:
      currentNavigationSelected = 0;
      draw_background(nav_bg);
      draw_navigation();
      break;

    case ABOUT:
      draw_background(abt_bg);
      draw_about();
      break;

    default:
      break;
  }
}

void set_current_state(WatchState newState){
  if(currentState != NTPSYNCING){
    currentState = newState;
  }
}