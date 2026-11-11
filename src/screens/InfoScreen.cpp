#include "InfoScreen.h"
#include "hardware/Display.h"

void InfoScreen::draw() {
    display.setPartialWindow(0, 0, 200, 200);
    display.firstPage();

    do {
        display.fillScreen(GxEPD_WHITE);

        //display.setFont(nullptr);
        //display.setTextSize(2);
        display.setTextColor(GxEPD_BLACK);

        display.setCursor(15, 30);
        display.print("DEVICE INFO");

        //display.setTextSize(1);
        display.setCursor(15, 70);
        display.print("S-Watch");

        display.setCursor(15, 95);
        display.print("ESP32-S3");

        display.setCursor(15, 160);
        display.print("BACK to menu");

    } while (display.nextPage());
}

void InfoScreen::update(){
    // stuff
}