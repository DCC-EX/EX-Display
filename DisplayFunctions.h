#ifndef DISPLAYFUNCTIONS_H
#define DISPLAYFUNCTIONS_H

#include <Arduino.h>
#include "EXDisplayClass.h"

extern bool debug;

extern EXDisplay *display0;

/// @brief Callback function for AtFinder
/// @param screenId ID of the screen to update
/// @param screenRow Row of the screen to update
/// @param text Char array of text
void updateEXDisplayRow(uint8_t screenId, uint8_t screenRow, char *text);

/// @brief Display all rows on all screens - handy for debug
void displayAllRows();

#endif
