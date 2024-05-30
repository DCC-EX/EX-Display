#ifndef FONTOPTIONS_H
#define FONTOPTIONS_H

#if SCREEN_TYPE == MCU
#include <Fonts/FreeMono12pt7b.h>
#include <Fonts/FreeMono18pt7b.h>
#include <Fonts/FreeMono24pt7b.h>
#include <Fonts/FreeMono9pt7b.h>
#include <Fonts/FreeSans12pt7b.h>
#include <Fonts/FreeSans18pt7b.h>
#include <Fonts/FreeSans24pt7b.h>
#include <Fonts/FreeSans9pt7b.h>

#endif

/// @brief Macros for available colours
#define BLACK 0x0000
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF
#define OLED_BLACK 0
#define OLED_WHITE 1
#define OLED_INVERT 2

/// @brief Macros for available fonts
#define SMALL &FreeMono9pt7b
#define MEDIUM &FreeMono12pt7b
#define LARGE &FreeMono18pt7b
#define XLARGE &FreeMono24pt7b
#define SMALL_SANS &FreeSans9pt7b
#define MEDIUM_SANS &FreeSans12pt7b
#define LARGE_SANS &FreeSans18pt7b
#define XLARGE_SANS &FreeSans24pt7b

#endif
