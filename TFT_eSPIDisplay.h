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

#include "Defines.h"
#include "DisplayInterface.h"
#include <SPI.h>
#include <TFT_eSPI.h>

// Define the standard fonts available for this display type
#define FONT_TFT_ESPI_SMALL &FreeMono9pt7b
#define FONT_TFT_ESPI_MEDIUM &FreeMono12pt7b
#define FONT_TFT_ESPI_LARGE &FreeMono18pt7b
#define FONT_TFT_ESPI_XLARGE &FreeMono24pt7b
#define FONT_TFT_ESPI_SMALL_SANS &FreeSans9pt7b
#define FONT_TFT_ESPI_MEDIUM_SANS &FreeSans12pt7b
#define FONT_TFT_ESPI_LARGE_SANS &FreeSans18pt7b
#define FONT_TFT_ESPI_XLARGE_SANS &FreeSans24pt7b

// If not overridden by myConfig.h, set the font
#ifndef TEXT_FONT
#define TEXT_FONT FONT_TFT_ESPI_MEDIUM
#endif // TEXT_FONT

/// @brief Display class for TFT_eSPI based displays
class TFT_eSPIDisplay : public DisplayInterface {
public:
  /// @brief Constructor for a TFT_eSPIDisplay instance
  /// @param rotation
  /// @param textSize
  /// @param textColour
  /// @param backgroundColour
  TFT_eSPIDisplay(uint8_t rotation, uint8_t textSize, uint16_t textColour, uint16_t backgroundColour);

  /// @brief Alternate constructor for a TFT_eSPIDisplay instance to specify the CS pin to allow for two displays
  /// @param rotation
  /// @param textSize
  /// @param textColour
  /// @param backgroundColour
  /// @param csPin
  TFT_eSPIDisplay(uint8_t rotation, uint8_t textSize, uint16_t textColour, uint16_t backgroundColour, int csPin);

  /// @brief Perform any initial once off setup or configuration here and call only once
  void begin() override;

  /// @brief Clear the entire screen
  void clearScreen() override;

  /// @brief Display a row of text on the display
  /// @param row Row number as specified in the SCREEN() command (not pixels)
  /// @param text Text to be displayed on this row
  /// @param underlined (Optional) Flag to underline this row - default false
  /// @param column (Optional) Column to start displaying the text, column being width of a character (not pixels)
  void displayRow(uint8_t row, const char *text, bool underlined = false, uint8_t column = 0) override;

  /// @brief Clear the specified row
  /// @param row Row number as specified in the SCREEN() command (not pixels)
  void clearRow(uint8_t row) override;

  /// @brief Display the startup screen with software version
  /// @param version EX-Display version
  void displayStartupInfo(const char *version) override;

  /// @brief Get the TFT_eSPI instance created by this instance - needed for the touch interface
  /// @return Pointer to the TFT_eSPI instance
  TFT_eSPI *getTFT_eSPIInstance();

  /// @brief Test if the TFT_eSPI instance has been initialised - needed for the touch interface
  /// @return true|false
  bool tftInitialised();

  /// @brief Static method to enable the compiler to generate create commands from myDevices.h entries
  /// @param rotation
  /// @param textSize
  /// @param textColour
  /// @param backgroundColour
  /// @return Pointer to a new TFT_eSPIDisplay instance
  static TFT_eSPIDisplay *create(uint8_t rotation, uint8_t textSize, uint16_t textColour, uint16_t backgroundColour);

  /// @brief Alternate static method to enable the compiler to generate create commands from myDevices.h entries
  /// @param rotation
  /// @param textSize
  /// @param textColour
  /// @param backgroundColour
  /// @param csPin
  /// @return Pointer to a new TFT_eSPIDisplay instance
  static TFT_eSPIDisplay *create(uint8_t rotation, uint8_t textSize, uint16_t textColour, uint16_t backgroundColour,
                                 int csPin);

  /// @brief Destructor for the TFT_eSPIDisplay
  ~TFT_eSPIDisplay() override;

private:
  static TFT_eSPI *_tft;
  const GFXfont *_gfxFont;
  static bool _tftInitialised;

  /// @brief Get the X/Y coordinates to draw the specified row, starting at the specified column
  /// @param row Row number
  /// @param column Column to start drawing at
  /// @param x Variable to update with the x position
  /// @param y Variable to update with the y position
  void _getRowPosition(uint8_t row, uint8_t column, int32_t &x, int32_t &y);
};

#endif // PIO_UNIT_TESTING

#endif // TFT_ESPIDISPLAY_H
