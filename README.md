S2-Watch (Stinyx Smartwatch)
============================

Simple open-source E-ink based watch on the ESP32, inspired by the Watchy watch using basically the same components

## Hardware

* Good Display - e-ink display 200x200px BW
* ESP32 microcontroller (for now, planning for a custom PCB)
* 400 mAh LiPO Battery (integrated with the PCB)
* (Custom PCB for easier construction and wiring)

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



