#ifndef DISPLAYFUNCTIONS_H
#define DISPLAYFUNCTIONS_H

#include "EXDisplayClass.h"
#include <Arduino.h>

extern bool debug;

// extern EXDisplay *display0;

/// @brief Callback function for AtFinder
/// @param screenId ID of the screen to update
/// @param screenRow Row of the screen to update
/// @param text Char array of text
void updateEXDisplayRow(uint8_t screenId, uint8_t screenRow, char *text);

/// @brief Update the active display on its associated screen
void updateScreen();

/// @brief Display all rows on all screens - handy for debug
void displayAllRows();

/// @brief Check if the provided message contains embedded colours
/// @param message Message to check for format #0x0000#0x0000#
/// @return True|False
bool embeddedColours(const char *message);

/// @brief Extract text/foreground and background colours
/// @param message Message to extrat colours from
/// @param textColour Integer for the text/foreground colour
/// @param backgroundColour Integer for the background colour
void extractColours(char *message, uint16_t *textColour, uint16_t *backgroundColour);

#endif
