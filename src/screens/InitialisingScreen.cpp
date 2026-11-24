#include "InitialisingScreen.h"
#include "Images.h"
#include "hardware/Display.h"
#include "graphics/Draw.h"

InitialisingScreen::InitialisingScreen() = default;

// Draw the initialising screen text and logo
void InitialisingScreen::draw() {
    display.setFullWindow();

    display.firstPage();
    do{
        drawing.drawImage(flowersakuralogo);
        drawing.drawText("S-Watch Booting...", 10, 190);
    }while(display.nextPage());
    

}