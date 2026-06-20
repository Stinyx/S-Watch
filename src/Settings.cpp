#include "Settings.h"
#include "debug.h"
#include "UserInterface.h"
#include "TimeManager.h"
#include "State.h"
#include <vector>


Setting::Setting(
    std::function<void()> func,
    const char* desc,
    bool scroll,
    int* scrollOptions
):  action(func),
    description(desc),
    scrollable(scroll),
    scrollOptions(scrollOptions)
{
}

void Setting::apply() {
    action();
}

void new_setting(const char* description, std::function<void()> function, bool scrollable, int *scrollOptions){
  settingsOptions.push_back(Setting(function, description, scrollable, scrollOptions));
}

void new_navigation(const char* description, std::function<void()> function){
 navigationOptions.push_back(Setting(function, description, NULL, NULL));
}

std::vector<Setting> settingsOptions;
std::vector<Setting> navigationOptions;

int currentMenuSelected = 0;
int currentNavigationSelected = 0;

int lastMenuSelected = 0;
int lastNavigationSelected = 0;

// Setting initialisation
void settings_init(){
  new_setting("Clock Style", [](){
    currentClockStyle++;
    if(currentClockStyle > 2) currentClockStyle = 0;
    draw_settings();
  }, true, &currentClockStyle);

  new_setting("Draw BG", [](){
    drawBackground = !drawBackground;
    draw_settings();
  }, true, &drawBackground);

  new_setting("Draw Date", [](){
    drawDate = !drawDate;
    draw_settings();
  }, true, &drawDate);

  new_setting("Military", [](){
    militaryTime = !militaryTime;
    draw_settings();
  }, true, &militaryTime);

  // Only ones that dont have options and are just toggle basically
  new_setting("Sync NTP", sync_ntp, false, NULL);


  new_setting("TEST3", [](){}, false, NULL);
}

void navigation_init(){
  new_navigation("Timer", [](){currentState = TIMER;});
  new_navigation("Image", [](){currentState = IMAGE;});
  new_navigation("Alarm", [](){currentState = ALARM;});
  new_navigation("About", [](){currentState = ABOUT;});
}

