#ifndef EXSCREEN_H
#define EXSCREEN_H

#include "Arial9pt7b.h"

#include <Adafruit_GFX.h>
#include <Arduino.h>

class EXScreen {
public:
  /// @brief Constructor for a new EXScreen object
  EXScreen(uint8_t maxRows, uint8_t maxColumns) : _maxRows(maxRows), _maxColumns(maxColumns) {}

  /// @brief Virtual function to implement to setup the required parameters for the physical screen
  virtual void setupScreen(uint8_t rotation, uint8_t textColour, uint8_t backgroundColour);

  /// @brief Virtual function to implement to write a row of text to the physical screen
  virtual void writeRow(uint8_t row, uint8_t column, const GFXfont *fontName, uint8_t fontColour, uint8_t textSize,
                        char *message);

  /// @brief Get the maximum number of rows this screen can physically display
  /// @return 0 - 255
  uint8_t getMaxRows() { return _maxRows; }

  /// @brief  Get the maximum number of columns this screen can physically display
  /// @return 0 - 255
  uint8_t getMaxColumns() { return _maxColumns; }

private:
  uint8_t _maxRows;    // Maximum number of rows this screen can display
  uint8_t _maxColumns; // Maximum number of columns this screen can display
};

#endif
