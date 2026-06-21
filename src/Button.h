#pragma once

// Button2 library for managing buttons
#include "Button2.h"

#define BUTTON_PIN1 33
#define BUTTON_PIN2 32
#define BUTTON_PIN3 35

extern Button2 button1;
extern Button2 button2;
extern Button2 button3;

// Button2 setup (Input)
void button_init();

// Each buttons functions
void button_handler_init();

// Loop to check button presses
void ButtonLoop();