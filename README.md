S2-Watch (Stinyx Smartwatch)
============================

Simple open-source E-ink based watch on the ESP32, inspired by the Watchy watch using basically the same components

## Hardware

* [Good Display GDEY0154D67 1.54" 200x200 ePaper display](https://www.laskakit.cz/good-display-gdey0154d67-1-54--200x200-epaper-displej/)
* [GeB LiPol Battery 503035 500mAh 3.7V JST-PH 2.0](https://www.laskakit.cz/baterie-li-po-3-7v-500mah-lipo/) (after i have PCB, usb-micro for now)
* ESP32 microcontroller (for now, planning for a custom PCB)
* (Custom PCB in the far far future)

## Features

* Automatic NTP synchronization upon watch boot
* Manual NTP synchronization
* Multiple clock display styles
* Multiple watch background styles
* *YOU WEEZO* image (for now because of `Mispul`)
* Settings screen - for changing UI and NTP Syncing, other settings soon
* Clock screen - shows current date and time
* External buttons mapped for changing screens and UI handling

## Technologies And Libraries 

* `<Button2.h>` - watch input
* `<GxEPD2_BW.h>` - e-ink display compatibility
* `<WiFi.h>` - connecting to wifi and syncing NTP data
* `<math.h>` - for easier calculations
* `<time.h>` - to keep track of time

- Written in **C++** in **VSCode** using **PlatformIO** for writing to the MCU
- All UI elements and art handmade by me in **GIMP**

## Wiring (Until PCB is made)

**ESP32**        **E‑Ink Display**  
GPIO18  →    CLK  
GPIO23  →    DIN  
GPIO17  →    DC  
GPIO16  →    RST  
GPIO5   →    CS  
GND     →    GND  
3V3     →    VCC  

## Button usage for now

### Button 1 (GPIO33)
* Long press - Sync NTP data
* Click - Nothing for now (select element in settings UI later)
* Double click - Show YOU WEEZO image
* Triple click - Settings menu (empty for now)

for triple and double click, you click them again the same amount of times to go back to the clock  

example usage in code as functions for Button2 callback set functions:

~~~cpp
void buttonDoubleClick(Button2& b){
  if(currentState != WEEZO){
    currentState = WEEZO;
  }else if(currentState == WEEZO){
    currentState = CLOCK;
  }
}

void buttonTripleClick(Button2& b){
  if(currentState != SETTINGS){
    currentState = SETTINGS;
  }else{
    currentState = CLOCK;
  }
}

void buttonLongClick(Button2& b){
  currentState = NTPSYNCING;
}
~~~



