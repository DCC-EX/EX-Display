/*
 *  © 2024 Peter Cole
 *
 *  This is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  It is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this code.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef DISPLAYINTERFACE_H
#define DISPLAYINTERFACE_H

#include "Logger.h"

/// @brief Class to abstract away all physical display implementation to enable multiple display types
class DisplayInterface {
public:
  /// @brief Perform any initial once off setup or configuration here and call only once
  virtual void begin() = 0;

  /// @brief Clear the entire screen
  virtual void clearScreen() = 0;

  /// @brief Display a row of text on the display
  /// @param row Row number as specified in the SCREEN() command (not pixels)
  /// @param text Text to be displayed on this row
  /// @param underlined (Optional) Flag to underline this row - default false
  /// @param column Column number to start displaying at (based on text width, not pixels)
  virtual void displayRow(uint8_t row, const char *text, bool underlined = false, uint8_t column = 0) = 0;

  /// @brief Clear the specified row
  /// @param row Row number as specified in the SCREEN() command (not pixels)
  virtual void clearRow(uint8_t row) = 0;

  /// @brief Display the startup screen with software version
  /// @param version EX-Display version
  virtual void displayStartupInfo(const char *version) = 0;

  /// @brief Set the next DisplayInterface derived instance in the list
  /// @param display Pointer to the next instance
  void setNext(DisplayInterface *display) { _next = display; }

  /// @brief Get the next DisplayInterface derived instance in the list
  /// @return Pointer to the next instance
  DisplayInterface *getNext() { return _next; }

  /// @brief Set the logger instance to use for diagnostic logging
  /// @param logger Pointer to the Logger instance to use
  void setLogger(Logger *logger) { _logger = logger; }

  /// @brief Set the ID for this display instance
  /// @param displayId ID of this display
  void setId(uint8_t displayId) { _displayId = displayId; }

  /// @brief Get the ID of this display instance
  /// @return ID of this display
  uint8_t getId() { return _displayId; }

  /// @brief Set the Screen ID this display is currently displaying
  /// @param screenId Screen ID
  void setScreenId(int screenId) { _screenId = screenId; }

  /// @brief Get the Screen ID this display is currently displaing
  /// @return Screen ID
  int getScreenId() { return _screenId; }

  /// @brief Destructor for a DisplayInterface
  virtual ~DisplayInterface() = default;

protected:
  /// @brief Pointer to the next DisplayInterface derived instance in the list
  DisplayInterface *_next = nullptr;
  /// @brief Default text colour for the display
  uint16_t _textColour;
  /// @brief Default background colour for the display
  uint16_t _backgroundColour;
  /// @brief Pointer to the Logger instance for the DisplayInterface derived classes
  Logger *_logger = nullptr;
  /// @brief ID for this display instance
  uint8_t _displayId = 0;
  /// @brief ID of the screen this display is currently displaying, defaults to -1 to flag it is not a valid ID
  int _screenId = -1;
  /// @brief Orientation of this display, most displays require this setting otherwise ignore it
  uint8_t _rotation = 0;
  /// @brief Multiplier for text size, most displays require this setting otherwise ignore it
  uint8_t _textSize = 1;
  /// @brief Maximum row number (not count) that will fit on this display (based on font height, not pixels)
  uint8_t _maxRow = 0;
  /// @brief Maximum column number (not count) that will fit on this display (based on font width, not pixels)
  uint8_t _maxColumn = 0;
  /// @brief Calculated font height to determine row positioning
  uint8_t _fontHeight = 0;
  /// @brief Calculated font width to determine column positioning
  uint8_t _fontWidth = 0;
};

#endif // DISPLAYINTERFACE_H
