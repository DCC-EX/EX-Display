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

#ifndef TFT_ESPIDISPLAY_H
#define TFT_ESPIDISPLAY_H

// Do not load when testing, TFT_eSPI library is incompatible and will cause failures.
#ifndef PIO_UNIT_TESTING

#include "DisplayInterface.h"
#include <SPI.h>
#include <TFT_eSPI.h>

/// @brief Display class for TFT_eSPI based displays
class TFT_eSPIDisplay : public DisplayInterface<uint16_t> {
public:
  /// @brief Constructor for the TFT_eSPIDisplay
  TFT_eSPIDisplay();

  /// @brief Perform any initial once off setup or configuration here and call only once
  void begin() override;

  /// @brief Clear the entire screen
  void clearScreen() override;

  /// @brief Display a row of text on the display
  /// @param row Row number as specified in the SCREEN() command (not pixels)
  /// @param text Text to be displayed on this row
  /// @param underlined (Optional) Flag to underline this row - default false
  /// @param column (Optional) Column to start displaying the text, column being width of a character (not pixels)
  void displayRow(int row, const char *text, bool underlined = false, int column = 0) override;

  /// @brief Clear the specified row
  /// @param row Row number as specified in the SCREEN() command (not pixels)
  void clearRow(int row) override;

  /// @brief Display the startup screen with software version
  /// @param version EX-Display version
  void displayStartupInfo(const char *version) override;

  /// @brief Get the TFT_eSPI instance created by this instance - handy for the touch interface
  /// @return Pointer to the TFT_eSPI instance
  TFT_eSPI *getTFT_eSPIInstance();

  /// @brief Destructor for the TFT_eSPIDisplay
  ~TFT_eSPIDisplay() override;

private:
  TFT_eSPI *_tft;
};

#endif // PIO_UNIT_TESTING

#endif // TFT_ESPIDISPLAY_H
