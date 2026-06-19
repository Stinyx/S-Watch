#pragma once

// Button2 
#include "Button2.h"

#define BUTTON_PIN1 33
#define BUTTON_PIN2 32
#define BUTTON_PIN3 35

extern Button2 button1;
extern Button2 button2;
extern Button2 button3;

// Button logic for a triple click (Settings screen for now)
void buttonTripleClick();

// Button logic for a long click (NTP sync for now)
void buttonLongClick(Button2& b);

void returnToHome(Button2& b);

// Button2 setup (Input)
void button_init();

// TEMPORARY BUTTON LOGIC TESTING, SUBJECT TO CHANGE
void button_handler_init();

void ButtonLoop();