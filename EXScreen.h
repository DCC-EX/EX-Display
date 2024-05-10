#ifndef EXSCREEN_H
#define EXSCREEN_H

#include "Defines.h"
#include <Arduino.h>
#if SCREEN_TYPE == MCU
#include <Adafruit_GFX.h>
#elif SCREEN_TYPE == TFT
#include <TFT_eSPI.h>
#endif

/// @brief This EXScreen class is designed to be extended by other screen classes that define the methods to perform the
/// requesite activities according to the library in use to drive the physical display.
/// This allows all physical screen methods to be consistent regardless of the library or driver in use, allowing this
/// code to support multiple different display types without needing to have the main functions call different
/// libraries/methods. As this is a virtual only class, every virtual method must be declared and defined in the class
/// that extends this.
class EXScreen {
public:
  /// @brief Constructor for a new EXScreen object
  EXScreen() {
    fontHeight = 0;
    maxRows = 0;
    maxColumns = 0;
  }

  /// @brief Virtual function to implement to setup the physical screen parameters
  /// @param rotation Rotate the screen if necessary
  /// @param textSize Pixel multiplier to increase text size if desired
  /// @param backgroundColour Fill the screen with this colour during setup
  virtual void setupScreen(uint8_t rotation, uint8_t textSize, uint16_t backgroundColour);

  /// @brief Virtual function to implement
  /// @param backgroundColour
  virtual void clearScreen(uint16_t backgroundColour);

  /// @brief Virtual function to implement to write a row of text to the physical screen
  /// @param row
  /// @param column
  /// @param fontColour
  /// @param backgroundColour
  /// @param maxLength
  /// @param message
  virtual void writeRow(uint8_t row, uint8_t column, uint16_t fontColour, uint16_t backgroundColour, uint8_t maxLength,
                        char *message);

  // virtual void writeHeaderRow(uint8_t row, uint8_t column, uint16_t fontColour, uint16_t backgroundColour, uint8_t
  // maxLength,
  //                       char *message);

  /// @brief Height of the font in use to determine row height
  uint8_t fontHeight;

  /// @brief Width of the font in use to determine max columns
  uint8_t fontWidth;

  /// @brief Maximum number of rows this screen can physically display
  uint8_t maxRows;

  /// @brief Maximum number of columns this screen can physically display
  uint8_t maxColumns;
};

#endif
