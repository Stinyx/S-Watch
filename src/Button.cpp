#include "Button.h"
#include "State.h"
#include "debug.h"
#include "settings.h"

// Input variables
Button2 button1;
Button2 button2;
Button2 button3;

// Button2 setup (Input)
void button_init(){ 
  button1.begin(BUTTON_PIN1, INPUT_PULLDOWN, false);
  button2.begin(BUTTON_PIN2, INPUT_PULLDOWN, false);
  button3.begin(BUTTON_PIN3, INPUT_PULLDOWN, false);
}

// Button logic, might change in the future since 4 buttons are planned
void button_handler_init(){ 

  //Button 1 logic
  button1.setLongClickHandler([](Button2& b){set_current_state(NTPSYNCING);});
  button1.setClickHandler([](Button2& b){scrollable_menu_down();});
  button1.setTripleClickHandler([](Button2& b){set_current_state(SETTINGS);});

  //Button 2 logic
  button2.setLongClickHandler([](Button2& b){set_current_state(CLOCK);}); 
  button2.setClickHandler([](Button2& b){scrollable_menu_up();});
  button2.setDoubleClickHandler([](Button2& b){scrollable_menu_apply();});

  //Button 3 logic
  button3.setTripleClickHandler([](Button2& b){set_current_state(NAVIGATION);});
}

// Check if each of the buttons has been pressed or not
void ButtonLoop(){
  button1.loop();
  button2.loop();
  button3.loop();
}