#include "fonts/comicsansfont.h"
#include "fonts/7segmentfont.h"
#include "fonts/7segmentghostfont.h"

#define digit_width 37
#define digit_height 71

#define dots_width 5
#define dots_height 71

// Digits with the missing ones deleted
unsigned char* digitArray1[10] = {
    digit0,
    digit1,
    digit2,
    digit3,
    digit4,
    digit5,
    digit6,
    digit7,
    digit8,
    digit9
};

// Digits with the missing ones having an outline
unsigned char* digitArray2[10] = {
    digit0_1,
    digit1_1,
    digit2_1,
    digit3_1,
    digit4_1,
    digit5_1,
    digit6_1,
    digit7_1,
    digit8_1,
    digit9_1
};

// Comic sans style digits
unsigned char* digitArray3[10] = {
    csans0,
    csans1,
    csans2,
    csans3,
    csans4,
    csans5,
    csans6,
    csans7,
    csans8,
    csans9,
};

// Styles
unsigned char** clockStyles[3] = {
    digitArray1, 
    digitArray2,
    digitArray3
};