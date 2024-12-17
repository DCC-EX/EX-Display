#ifndef DISPLAYFUNCTIONS_H
#define DISPLAYFUNCTIONS_H

#include "PhysicalScreen.h"
#include <Arduino.h>

extern bool debug;

/// @brief Callback function for AtFinder
/// @param screenId ID of the screen to update
/// @param screenRow Row of the screen to update
/// @param text Char array of text
void updateDisplayRow(uint8_t screenId, uint8_t screenRow, char *text);

/// @brief Update the active display on its associated screen
void updateScreen();

/// @brief Display all rows on all screens - handy for debug
void displayAllRows();

#endif
