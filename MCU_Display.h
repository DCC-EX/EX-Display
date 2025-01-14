/*
 *  © 2024 Peter Cole
 *  © 2025 Colin Murdoch
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

#ifndef MCU_DISPLAY_H
#define MCU_DISPLAY_H

// Do not load when testing.
#ifndef PIO_UNIT_TESTING
#include "Defines.h"
#include "DisplayInterface.h"
#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
#include <TouchScreen.h>
#include <SPI.h>

#define MINPRESSURE 200
#define MAXPRESSURE 1000

// Define the standard fonts available for this display type
#define FONT_MCU_SMALL &FreeMono9pt7b
#define FONT_MCU_MEDIUM &FreeMono12pt7b
#define FONT_MCU_LARGE &FreeMono18pt7b
#define FONT_MCU_XLARGE &FreeMono24pt7b
#define FONT_MCU_SMALL_SANS &FreeSans9pt7b
#define FONT_MCU_MEDIUM_SANS &FreeSans12pt7b
#define FONT_MCU_LARGE_SANS &FreeSans18pt7b
#define FONT_MCU_XLARGE_SANS &FreeSans24pt7b
#define FONT_MCU_MEDIUM_BOLD &FreeMonoBold12pt7b
#define FONT_MCU_SERIF_BOLD_ITALIC &FreeSerifBoldItalic12pt7b

// If not overridden by myConfig.h, set the font
#ifndef TEXT_FONT
#define TEXT_FONT FONT_MCU_MEDIUM_BOLD
#endif

// ALL Touch panels and wiring is DIFFERENT
// copy-paste results from TouchScreen_Calibr_native.ino
//These settings are for the McuFriend 2.8" shield

const byte XP = 7, XM = A1, YP = A2, YM = 6;

//const int TS_LEFT = 99, TS_RT = 895, TS_TOP = 122, TS_BOT = 918;  // For Landscape Orientation
const int TS_LEFT = 123, TS_RT = 923, TS_TOP = 895, TS_BOT = 98; // for Portrait orientation 2




/// @brief Display class for TFT_eSPI based displays
class MCU_Display : public DisplayInterface {
public:
  /// @brief Constructor for a TFT_eSPIDisplay instance
  /// @param rotation Rotation of the display, 0 - 3, refer to TFT_eSPI documentation for details
  /// @param textFont The identiy of the font for this display.
  /// @param textColour Default 16bit text colour, refer to TFT_eSPI documentation for details
  /// @param backgroundColour Default 16bit background colour, refer to TFT_eSPI documentation for details
  MCU_Display(uint8_t rotation, const GFXfont *textFont, uint16_t textColour, uint16_t backgroundColour);

  /// @brief Perform any initial once off setup or configuration here and call only once
  void begin() override;

  /// @brief Clear the entire screen
  void clearScreen() override;

  /// @brief Display the specified Screen on this display
  /// @param screen Pointer to the Screen to display
  void displayScreen(Screen *screen) override;

  /// @brief Clear the specified row
  /// @param row Row number as specified in the SCREEN() command (not pixels)
  void clearRow(uint8_t row);

  /// @brief Display the startup screen with software version
  /// @param version EX-Display version
  void displayStartupInfo(const char *version) override;

  /// @brief Display a row using formatting modifiers
  /// @param row Row ID to display
  /// @param column Column at which to display text (not pixels)
  /// @param attributes RowAttributes structure containing modifier details
  /// @param text Text to display
  /// @param append Flag if this is appending to an existing row and should not clear the row first
  virtual void displayFormattedRow(uint8_t row, uint8_t column, RowAttributes attributes, const char *text,
                                   bool append) override;


   /// @brief Test if the TFT_eSPI instance has been initialised - needed for the touch interface
  /// @return true|false
  bool tftInitialised();

  /// @brief Static method to enable the compiler to generate create commands from myDevices.h entries
  /// @param rotation rotation Rotation of the display, 0 - 3, refer to TFT_eSPI documentation for details
  /// @param textFont The identiy of the font for this display.
  /// @param textColour Default 16bit text colour, refer to TFT_eSPI documentation for details
  /// @param backgroundColour Default 16bit background colour, refer to TFT_eSPI documentation for details
  /// @return Pointer to a new TFT_eSPIDisplay instance
  static MCU_Display *create(uint8_t rotation, const GFXfont *textFont, uint16_t textColour,
                                 uint16_t backgroundColour);

  /// @brief Destructor for the TFT_eSPIDisplay
  ~MCU_Display() override;

private:
  static MCUFRIEND *_tft;
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

#endif // MCU_DISPLAY_H