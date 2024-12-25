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

#include "TFT_eSPITouch.h"

// Do not load when testing, TFT_eSPI library is incompatible and will cause failures.
#ifndef PIO_UNIT_TESTING

TFT_eSPITouch::TFT_eSPITouch(TFT_eSPIDisplay *display) : _display(display) {
  _tft = _display->getTFT_eSPIInstance();
}

void TFT_eSPITouch::begin() {
  // If the display instance didn't initialised the tft instance, it must be done first, call begin()
  if (!_display->tftInitialised()) {
    LOG(LogLevel::WARN, "The associated TFT_eSPIDislay instance %d has not been initialised, initialising now", _display->getId());
    _display->begin();
  }
  // If the touch input isn't calibrated, do it first
  if (!_calibrated()) {
    LOG(LogLevel::DEBUG, "TFT_eSPI touch input not calibrated, starting");
    // If calibration fails, or data can't be saved, show the user an error and halt for 5 secs
    // This will allow normal display operationg to resume, but input won't be reliable
    if (!_doCalibration()) {
      LOG(LogLevel::ERROR, "TFT_eSPI touch input calibration failed");
      _display->clearScreen();
      _display->displayRow(0, "ERROR!");
      _display->displayRow(1, "TFT_eSPI touch input calibration failed");
      _display->displayRow(2, "Touch input will be unreliable");
      _display->displayRow(3, "Operation resumes in 5 seconds");
      delay(5000);
      _display->clearScreen();
    } else {
      // Otherwise clear the screen and continue
      LOG(LogLevel::DEBUG, "TFT_eSPI touch input calibrated successfully");
      _display->clearScreen();
    }
  }
  // Need to calculate touch screen locations for inputs here
}

void TFT_eSPITouch::check() {}

bool TFT_eSPITouch::_calibrated() {return true;}

bool TFT_eSPITouch::_doCalibration() {return true;}

#endif // PIO_UNIT_TESTING
