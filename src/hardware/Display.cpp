#include "Display.h"
#include "driver/gpio.h"
#include "esp_sleep.h"

void displayBusyCallback(const void*) {
    gpio_wakeup_enable(GPIO_NUM_36, GPIO_INTR_LOW_LEVEL);
    esp_sleep_enable_gpio_wakeup();
    esp_light_sleep_start();
}

GxEPD2_DISPLAY_CLASS<GxEPD2_DRIVER_CLASS, 200> display(
    GxEPD2_DRIVER_CLASS(33, 34, 35, 36)
);

void Display::init() {
    SPI.begin(47, 46, 48, 33);
    display.init(115200, false, 2, true);

    display.epd2.selectSPI(
        SPI,
        SPISettings(20000000, MSBFIRST, SPI_MODE0)
    );

    display.epd2.setBusyCallback(displayBusyCallback);

    display.setRotation(0);
    display.setFont(&FreeMonoBold9pt7b);
    display.setTextColor(GxEPD_BLACK);
    display.setFullWindow();
    display.setTextSize(1);
}