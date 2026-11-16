S2-Watch (Stinyx Smartwatch)
============================

Simple open-source E-ink based watch on the ESP32, inspired by the [Watchy watch by SQFMI](https://watchy.sqfmi.com/), using their kit for the hardware, i do use AI for occasional help, since i am not the best programmer around

I have wanted a watch for a long time, and i like customizing things, so i thought to make a watch as my project. I've wanted it to last a long time without me needing to charge it, hence i chose an E-Ink display. Scrolling through youtube reels, i came upon the watchy watch, which suited all of my needs perfectly.

It had:

* A programmable ESP-32-S3 chip inside with bluetooth and WI-FI built in
* An E-Ink screen, so it would last longer and take no charge while not drawing
* 4 external buttons so i could scroll through menus
* Accelerometer and gyroscope to track rotation and movement
* A buzzer to give the user haptic feedback on Alarms and such
* And it was open source and available to buy!

## Technologies And Libraries 

* `<GxEPD2_BW.h>` - E-Ink display compatibility and communication
* `<WiFi.h>` - connecting to wifi and syncing NTP data
* `<time.h>` - to keep track of time and for the watch to watch

- Written in `C++` in `VSCode` using `PlatformIO` for writing to the MCU
- All GUI elements and art handmade by me in `GIMP`

## Hardware (for breadboard prototyping)

* [Good Display GDEY0154D67 1.54" 200x200 ePaper display](https://www.laskakit.cz/good-display-gdey0154d67-1-54--200x200-epaper-displej/)
* [GeB LiPol Battery 503035 500mAh 3.7V JST-PH 2.0](https://www.laskakit.cz/baterie-li-po-3-7v-500mah-lipo/) 
* ESP32 microcontroller (aliexpress, don't know the specific one)

## Wiring (breadboard prototyping with E-Ink screen and an ESP-32 Devkit)

`ESP32`        `E‑Ink Display`  
GPIO18  →    CLK  
GPIO23  →    DIN  
GPIO17  →    DC  
GPIO16  →    RST  
GPIO5   →    CS  
GND     →    GND  
3V3     →    VCC  

## Hardware (for for actual project and production)

* [Watchy Watch V3 by SQFMI](https://cz.mouser.com/en/ProductDetail/SQFMI/SQFMI-WATCHY-10?qs=DRkmTr78QARN9VSJRzqRxw%3D%3D)

## Features (Slowly being added)

* [x] Automatic NTP synchronization upon watch boot
* [x] Battery percentage indicator
* [x] Date and time functionality
* [x] External buttons mapped for changing screens and UI handling
* [ ] Manual NTP synchronization
* [ ] Multiple clock display styles (currently 3 types)

## Integrated Screens

* [x] **Clock** - shows current date and time (customizable in the future)
* [x] **About** - Short information and custom about text (done but change info)
* [ ] **Settings** - for changing UI and NTP Syncing, other settings soon (so far i have a menu)
* [ ] **Timer** - stopwatch functionality
* [ ] **Alarm** - set up alarms
* [ ] **Navigation** - Changing between timer, alarm, settings, etc. (going to be in the menu)

## TODO (Future reference for code or hardware)

# What i want to achieve
- i want  to achieve all of the standard smartwatch functionalities in my own style

* [x] Refactor code into multiple files for readability
* [x] Show the current time
* [x] Settings for customization (partly)
* [x] Automatic NTP syncing (only on boot)
* [ ] Timer functionality
* [ ] Stopwatch functionality
* [ ] Customization and easier custom clock screens

# What is optional
* Start designing PCB (with some tweaks from Watchy hardware)
* ESPNow functionality (to turn on other projects, lights and such)
* Current Soundcloud song info through BLE 
* Amount of steps
* Current weather
* Wifi indicator



