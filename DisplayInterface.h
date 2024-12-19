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
/// When implementing this class, specify the colour type used by the associated display library
/// Eg. class TFT_eSPIDisplay : public DisplayInterface<uint16_t> {...}
template <typename ColourType> class DisplayInterface {
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

  /// @brief Set the current text colour
  /// @param textColour ColourType as implemented by the derived class
  void setTextColour(ColourType textColour) { _textColour = textColour; }

  /// @brief Get the current text colour
  /// @return ColourType as implemented by the derived class
  ColourType getTextColour() { return _textColour; }

  /// @brief Set the current background colour
  /// @param backgroundColour ColourType as implemented by the derived class
  void setBackgroundColour(ColourType backgroundColour) { _backgroundColour = backgroundColour; }

  /// @brief Get the current background colour
  /// @return ColourType as implemented by the derived class
  ColourType getBackgroundColour() { return _backgroundColour; }

  /// @brief Set the logger instance to use for diagnostic logging
  /// @param logger Pointer to the Logger instance to use
  void setLogger(Logger *logger) { _logger = logger; }

  /// @brief Destructor for a DisplayInterface
  virtual ~DisplayInterface() = default;

private:
  ColourType _textColour;
  ColourType _backgroundColour;
  Logger *_logger = nullptr;
};

#endif // DISPLAYINTERFACE_H
