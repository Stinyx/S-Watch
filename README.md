S2-Watch (Stinyx Smartwatch)
============================

Simple open-source E-ink based watch on the ESP32, inspired by the [Watchy watch](https://watchy.sqfmi.com/), using their kit for the hardware, i do use AI for occasional help, since i am not the best programmer around

## Hardware (for breadboard prototyping)

* [Good Display GDEY0154D67 1.54" 200x200 ePaper display](https://www.laskakit.cz/good-display-gdey0154d67-1-54--200x200-epaper-displej/)
* [GeB LiPol Battery 503035 500mAh 3.7V JST-PH 2.0](https://www.laskakit.cz/baterie-li-po-3-7v-500mah-lipo/) 
* ESP32 microcontroller 

## ~~Features~~ Redoing whole code

* Automatic NTP synchronization upon watch boot
* Manual NTP synchronization
* Multiple clock display styles (currently 3 types)
* Multiple watch background styles (eventually)
* External buttons mapped for changing screens and UI handling

## ~~Integrated Menus/Screens~~ Redoing whole code

* **Clock** - shows current date and time
* **Settings** - for changing UI and NTP Syncing, other settings soon
* **Timer** - stopwatch functionality
* **Alarm** - set up alarms
* **Navigation** - Changing between timer, alarm, settings, etc.
* **About** - Short information and custom about text
        
* (Maybe upcoming) Sakura logo image
* *YOU WEEZO* image (for now because of `Mispul`) (easter egg?)

## Technologies And Libraries 

* `<Button2.h>` - watch input
* `<GxEPD2_BW.h>` - e-ink display compatibility
* `<WiFi.h>` - connecting to wifi and syncing NTP data
* `<math.h>` - for easier calculations
* `<time.h>` - to keep track of time

- Written in `C++` in `VSCode` using `PlatformIO` for writing to the MCU
- All UI elements and art handmade by me in `GIMP`

## Wiring (for breadboard)

`ESP32`        `E‑Ink Display`  
GPIO18  →    CLK  
GPIO23  →    DIN  
GPIO17  →    DC  
GPIO16  →    RST  
GPIO5   →    CS  
GND     →    GND  
3V3     →    VCC  

## TODO (Future reference for code or hardware)

# What i want to achieve
* ~~Refactor code into multiple files~~ - done but poorly
* ~~Show the current time~~ - done
* ~~Settings for customization~~ - done
* ~~Automatic NTP syncing~~ - done but poorly
* Redo the startup procedure
* More customization and easier custom screens
* Fix button inputs not registering when startupProcedure is turned off (no time data)

# What is optional
* Start designing PCB
* Timer
* Stopwatch
* ESPNow functionality
* Current Soundcloud song info through BLE 
* Amount of steps
* Current weather
* Wifi indicator
* Fix button inputs not registering when startupProcedure is turned off (no time data)



