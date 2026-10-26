/*

#include "SettingsScreen.h"

void SettingsScreen::draw(){
  epdDrawPartial(15, 45, 170, 145,
      []() {
          int lineHeight = 25;
          int offset = (menuScrollOffset > 0) ? 85 : 60;

          for (int row = 0; row < visibleItems; row++) {

              int settingIndex = menuScrollOffset + row;

              if (settingIndex >= settingsOptions.size())
                  break;

              const Setting& setting = settingsOptions[settingIndex];

              display.setCursor(15, offset);

              if (currentMenuSelected == settingIndex)
                  display.printf(">%s", setting.description);
              else
                  display.printf("%s", setting.description);

              if (setting.scrollable && setting.scrollOptions != NULL && setting.toggleable == false) {
                  display.setCursor(155, offset);
                  display.printf("<%d>", *setting.scrollOptions);
              }

              if(setting.toggleable == true){
                
                if(*setting.scrollOptions == 0){
                  draw_sprite(155, offset - toggle_button_height, toggle_button_width, toggle_button_height, toggle_button_off);
                }else{
                  draw_sprite(155, offset - toggle_button_height, toggle_button_width, toggle_button_height, toggle_button_on);
                }
              }

              offset += lineHeight;
          }

          // Show arrows if more items exist
          if (menuScrollOffset > 0) {
              display.setCursor(60, 60);
              display.print("/\\ /\\ /\\");
          }

          if (menuScrollOffset + visibleItems < settingsOptions.size()) {
              display.setCursor(60, 180);
              display.print("\\/ \\/ \\/");
          }
      }
  );
}
*/