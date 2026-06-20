#include "Init.h"

#include "settings.h"
#include "UserInterface.h"
#include "Button.h"


void Init(){
    button_init();
    button_handler_init();
    gxepd_init();
    settings_init();
    navigation_init();
    refresh_display(); 
}