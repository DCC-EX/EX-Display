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
  /// @param column (Optional) Column to start displaying the text, column being width of a character (not pixels)
  virtual void displayRow(int row, const char *text, bool underlined = false, int column = 0) = 0;

  /// @brief Clear the specified row
  /// @param row Row number as specified in the SCREEN() command (not pixels)
  virtual void clearRow(int row) = 0;

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
};

#endif // DISPLAYINTERFACE_H
