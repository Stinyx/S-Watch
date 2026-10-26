#pragma once

// Button2 library for managing buttons
#include "Button2.h"

#define BUTTON_PIN1 33
#define BUTTON_PIN2 32
#define BUTTON_PIN3 35

class Button{
private:
    /* data */
public:
    Button(/* args */);
    ~Button();
    void Init();
    void Update();
    Button2 button1;
    Button2 button2;
    Button2 button3;
};

