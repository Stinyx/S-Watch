#pragma once

#include "Draw.h"

extern int menuScrollOffset;
extern const int visibleItems;

// Draws a single 7-segment digit on the display
void draw_digit(int x, int y, int digit, int style);

// Draws text on screen (basically display.printf() but e-ink and dynamic with partial refresh)
void draw_text(int x, int y, const char* fmt, ...);

void draw_settings();

void draw_navigation();

void draw_about();

// Draws out the current date on screen
void draw_date();

// Draws out the current time on screen
void draw_time();

// Draws a white screen to avoid a full screen refresh but avoid ghosting a little
void draw_blank();

// Refreshes display fully to avoid ghosting
void refresh_display();

// Draws an image on screen
void draw_image(int x, int y, int w, int h, const unsigned char* image);

void draw_sprite(int x, int y, int w, int h, const unsigned char* image);

void draw_background(const unsigned char* backgroundImage);