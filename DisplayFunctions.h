#ifndef DISPLAYFUNCTIONS_H
#define DISPLAYFUNCTIONS_H

#include <Arduino.h>

extern bool debug;

/// @brief Callback function for AtFinder
/// @param screenId ID of the screen to update
/// @param screenRow Row of the screen to update
/// @param text Char array of text
void updateEXDisplayRow(uint8_t screenId, uint8_t screenRow, char *text);

/// @brief Function to update displays when rows have changed
void displayChangedRows();

/// @brief Display all rows on all screens - handy for debug
/// @param delay Time in ms to wait before displaying rows
void displayAllRows(unsigned long delay);

#endif
