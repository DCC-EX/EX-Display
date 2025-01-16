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
#ifdef NEEDS_TFT

#ifndef TFT_ESPITOUCH_H
#define TFT_ESPITOUCH_H

// Do not load when testing, TFT_eSPI library is incompatible and will cause failures.
#ifndef PIO_UNIT_TESTING

#include "Defines.h"
#include "InputInterface.h"
#include "TFT_eSPIDisplay.h"
#include <SPI.h>
#include <TFT_eSPI.h>

/// @brief Display class for TFT_eSPI touch screens
class TFT_eSPITouch : public InputInterface {
public:
  /// @brief Constructor for the TFT_eSPITouch instance
  /// @param displayId ID of the display to retrieve the TFT_eSPI instance from
  TFT_eSPITouch(int displayId);

  /// @brief Perform any initial once off setup or configuration here and call only once
  void begin() override;

  /// @brief Call this method at least once per main loop to monitor for input actions
  /// Any actions should call the callback set in the _callback attribute
  void check() override;

  /// @brief Static method to enable the compiler to generate create commands from myDevices.h entries
  /// @param displayId ID of the display to retrieve the TFT_eSPI instance from
  /// @return Pointer to the new TFT_eSPITouch instance
  static TFT_eSPITouch *create(int displayId);

private:
  TFT_eSPI *_tft;
  const char _calibrationFile[20];

  /// @brief Test if valid calibration data is available for this touch interface
  /// @return true|false
  bool _calibrated();

  /// @brief Run the TFT_eSPI calibration sequence
  /// @return true if successful and saved, otherwise false
  bool _doCalibration();

  /// @brief Ensure SPIFFS filesystem is up and running
  /// @return true|false
  bool _setupSPIFFS();

  /// @brief Display calibration error on screen and pause for 5 seconds
  /// @param display Pointer to the TFT_eSPIDisplay instance to use
  void _displayCalibrationError(TFT_eSPIDisplay *display);
};

#endif // PIO_UNIT_TESTING

#endif // TFT_ESPITOUCH_H

#endif // NEEDS_TFT
