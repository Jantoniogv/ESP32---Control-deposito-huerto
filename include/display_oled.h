#ifndef _DYSPLAY_OLED_H_
#define _DYSPLAY_OLED_H_
#include <Arduino.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "images.h"

#include "debug_utils.h"
#define DEBUG

#define DIR_OLED_I2C 0x3C

xSemaphoreHandle mutexOled;

uint8_t displayWidth = 128;
uint8_t displayHigh = 64;

Adafruit_SSD1306 display(displayWidth, displayHigh);

void printDisplayOled()
{
    if (xSemaphoreTake(mutexOled, portMAX_DELAY) == pdTRUE)
    {
        display.display();
    }

    xSemaphoreGive(mutexOled);
}

void init_oled()
{
    mutexOled = xSemaphoreCreateMutex();

    if (!display.begin(SSD1306_SWITCHCAPVCC, DIR_OLED_I2C))
    {
        DEBUG_PRINT("Starting OLED failed!");
        while (1)
            ;
    }

    DEBUG_PRINT("Init display OLED ok");

    display.clearDisplay();
    display.drawBitmap(0, 0, logo, 128, 64, WHITE);
    printDisplayOled();
    vTaskDelay(3000);
};

#endif //_DYSPLAY_OLED_H_