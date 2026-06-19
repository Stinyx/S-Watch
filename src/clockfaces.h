#pragma once

#include <Arduino.h> 

#include "fonts/comicsansfont.h"
#include "fonts/7segmentfont.h"
#include "fonts/7segmentghostfont.h"

#define digit_width 37
#define digit_height 71

#define dots_width 5
#define dots_height 71

extern unsigned char* digitArray1[10];
extern unsigned char* digitArray2[10];
extern unsigned char* digitArray3[10];

extern unsigned char** clockStyles[3];