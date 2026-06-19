#include "Button.h"
#include "State.h"
#include "debug.h"
#include "settings.h"

// Input variables
Button2 button1;
Button2 button2;
Button2 button3;

// Button logic for a triple click (Settings screen for now)
void buttonTripleClick(){
  if(currentState != SETTINGS){
    currentState = SETTINGS;
  }else{
    currentState = CLOCK;
  }
};

// Button logic for a long click (NTP sync for now)
void buttonLongClick(Button2& b){
  currentState = NTPSYNCING;
};

void returnToHome(Button2& b){
  if(currentState != CLOCK || currentState != NTPSYNCING){
    currentState = CLOCK;
  }
};

// Button2 setup (Input)
void button_init(){ 
  button1.begin(BUTTON_PIN1, INPUT_PULLDOWN, false);
  button2.begin(BUTTON_PIN2, INPUT_PULLDOWN, false);
  button3.begin(BUTTON_PIN3, INPUT_PULLDOWN, false);
}

// TEMPORARY BUTTON LOGIC TESTING, SUBJECT TO CHANGE
void button_handler_init(){ 
  button1.setLongClickHandler(buttonLongClick);
  button1.setClickHandler([](Button2& b){
    if(currentState == SETTINGS && currentMenuSelected < settingsOptions.size() - 1) currentMenuSelected++;
    else if(currentState == NAVIGATION && currentNavigationSelected < navigationOptions.size() - 1) currentNavigationSelected++;
  });
  button1.setTripleClickHandler([](Button2& b){if(currentState != NTPSYNCING) buttonTripleClick();});


  button2.setLongClickHandler([](Button2& b){currentState = CLOCK;}); //returnToHome(), lambda now for ease of reading
  button2.setClickHandler([](Button2& b){
     if(currentState == SETTINGS && currentMenuSelected > 0) currentMenuSelected--;
     else if(currentState == NAVIGATION && currentNavigationSelected > 0) currentNavigationSelected--;
  });

  button2.setDoubleClickHandler([](Button2& b){
    if(currentState == SETTINGS) settingsOptions[currentMenuSelected].apply();
    else if(currentState == NAVIGATION) navigationOptions[currentNavigationSelected].apply();
  });

  button3.setTripleClickHandler([](Button2& b){if(currentState != NTPSYNCING) currentState = NAVIGATION;});
}

void ButtonLoop(){
    button1.loop();
    button2.loop();
    button3.loop();
}