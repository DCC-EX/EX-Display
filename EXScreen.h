#ifndef EXSCREEN_H
#define EXSCREEN_H

// #include <Adafruit_GFX.h>
#include <Arduino.h>
#include <TFT_eSPI.h>

/// @brief This EXScreen class is designed to be extended by other screen classes that define the methods to perform the
/// requesite activities according to the library in use to drive the physical display.
/// This allows all physical screen methods to be consistent regardless of the library or driver in use, allowing this
/// code to support multiple different display types without needing to have the main functions call different
/// libraries/methods. As this is a virtual only class, every virtual method must be declared and defined in the class
/// that extends this.
class EXScreen {
public:
  /// @brief Constructor for a new EXScreen object
  EXScreen(uint8_t maxRows, uint8_t maxColumns) : _maxRows(maxRows), _maxColumns(maxColumns) {}

  /// @brief Virtual function to implement to setup the required parameters for the physical screen
  virtual void setupScreen(uint8_t rotation, uint16_t textColour, uint16_t backgroundColour);

  /// @brief Virtual function to implement to write a row of text to the physical screen
  virtual void writeRow(uint8_t row, uint8_t column, const GFXfont *fontName, uint16_t fontColour, uint8_t textSize,
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
