#ifndef PHYSICALSCREEN_H
#define PHYSICALSCREEN_H

#include "Defines.h"
#include "LogicalDisplay.h"
#include <Arduino.h>

/// @brief This PhysicalScreen class is designed to be extended by other screen classes that define the methods to
/// perform the requesite activities according to the library in use to drive the physical screen. This allows all
/// physical screen methods to be consistent regardless of the library or driver in use, allowing this code to support
/// multiple different screen types without needing to have the main functions call different libraries/methods. Every
/// virtual method must be declared and defined in the class that extends this.
class PhysicalScreen {
public:
  PhysicalScreen() { _logicalDisplay = nullptr; }

  /// @brief Virtual function to implement to setup the physical screen parameters
  /// @param rotation Rotate the screen if necessary
  /// @param textSize Pixel multiplier to increase text size if desired
  /// @param backgroundColour Fill the screen with this colour during setup
  virtual void setupScreen(uint8_t rotation, uint8_t textSize, uint16_t backgroundColour);

  /// @brief Virtual function to implement to clear the entire screen
  /// @param backgroundColour Valid colour to set the entire screen to
  virtual void clearScreen(uint16_t backgroundColour);

  /// @brief Virtual function to implement to clear the specified row
  /// @param row Row number to clear, 0 - 255
  /// @param backgroundColour Valid colour to set the row to
  virtual void clearRow(uint8_t row, uint16_t backgroundColour);

  /// @brief Virtual function to implement to write a row of text to the physical screen
  /// @param row Row on screen, 0 - 255 (not pixels)
  /// @param column Column on screen, 0 - 255 (not pixels)
  /// @param fontColour Valid colour for the text
  /// @param backgroundColour Valid colour for the background
  /// @param maxLength Maximum number of columns (not pixels) that can fit on the screen
  /// @param message Char array containing the text to display
  virtual void writeRow(uint8_t row, uint8_t column, uint16_t fontColour, uint16_t backgroundColour, uint8_t maxLength,
                        char *message, bool underlined);

  /// @brief Virtual function to implement to write a horizontal line on the specified row
  /// @param row Row on screen, 0 - 255 (not pixels)
  /// @param column Column to start the line, 0 - 255 (not pixels)
  /// @param lineWidth Pixel width to make the line
  /// @param lineLength Number of columns for the line (not pixels), 0 - 255
  /// @param lineColour Valid colour for the line
  /// @param backgroundColour Valid colour for the background
  virtual void writeLine(uint8_t row, uint8_t column, uint8_t lineLength, uint16_t lineColour,
                         uint16_t backgroundColour);

  /// @brief Get the first EXDisplay object in the linked list
  /// @return Pointer to the first EXDisplay object
  LogicalDisplay *getFirstDisplay();

  /// @brief Check if there is already a display created at the specified number
  /// @param displayNumber True|False
  /// @return
  bool displayNumberExists(uint8_t displayNumber);

  /// @brief Get the display and associated row linked list for the specified display number
  /// @param displayNumber Display number to get, 0 - 255
  /// @return EXDisplay object, or nullptr if not exists
  static LogicalDisplay *getDisplayByNumber(uint8_t displayNumber);

  /// @brief Get the currently selected display
  /// @return Pointer to the currently selected display
  LogicalDisplay *getActiveDisplay();

  /// @brief Switch active display to the next display in the linked list
  void setNextDisplay();

  /// @brief Switch active display to the previous display in the linked list
  void setPreviousDisplay();

  /// @brief Call this method as often as possible to support timed display switching
  /// @param switchDelay Time in milliseconds before switching displays
  void autoSwitch(unsigned long switchDelay);

protected:
  LogicalDisplay *_logicalDisplay; // Pointer to the first associated logical display
  LogicalDisplay *_activeDisplay;  // Current logical display this physical screen needs to show
};

#endif
