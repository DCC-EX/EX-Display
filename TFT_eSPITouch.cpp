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
#include "CallbackInterface.h"

// Do not load when testing, TFT_eSPI library is incompatible and will cause failures.
#ifndef PIO_UNIT_TESTING

TFT_eSPITouch::TFT_eSPITouch(int displayId) : _tft(nullptr) {
  _needsDisplay = displayId;
  _isCalibrating = false;
}

void TFT_eSPITouch::begin() {
  LOG(LogLevel::DEBUG, "TFT_eSPITouch::begin()");
  // Can't do anything without a TFT_eSPIDisplay or TFT_eSPI instance
  if (_display == nullptr) {
    LOG(LogLevel::ERROR, "An existing DisplayInterface instance is not set, cannot use touch");
    return;
  }
  // The display must be able to be cast to a TFT_eSPIDisplay instance to be valid
  TFT_eSPIDisplay *display = static_cast<TFT_eSPIDisplay *>(_display);
  if (!display) {
    LOG(LogLevel::ERROR, "Provided DisplayInterface is not a TFT_eSPIDisplay type, cannot use touch");
    return;
  }
  _tft = display->getTFT_eSPIInstance();
  if (!_tft) {
    LOG(LogLevel::ERROR, "An existing TFT_eSPI instance is not set, cannot use touch");
    return;
  }
  // If the display instance didn't initialised the tft instance, it must be done first, call begin()
  if (!display->tftInitialised()) {
    LOG(LogLevel::WARN, "The associated TFT_eSPIDislay instance %d has not been initialised, initialising now",
        display->getId());
    display->begin();
  }
  // If the touch input isn't calibrated, do it first
  if (!_calibrated()) {
    LOG(LogLevel::DEBUG, "TFT_eSPI touch input not calibrated, starting");
    _isCalibrating = true;
    // If calibration fails, or data can't be saved, show the user an error and halt for 5 secs
    // This will allow normal display operationg to resume, but input won't be reliable
    if (!_doCalibration()) {
      LOG(LogLevel::ERROR, "TFT_eSPI touch input calibration failed");
      display->clearScreen();
      display->displayRow(0, "ERROR!");
      display->displayRow(1, "TFT_eSPI touch input calibration failed");
      display->displayRow(2, "Touch input will be unreliable");
      display->displayRow(3, "Operation resumes in 5 seconds");
      delay(5000);
      display->clearScreen();
      _isCalibrating = false;
    } else {
      // Otherwise clear the screen and continue
      LOG(LogLevel::DEBUG, "TFT_eSPI touch input calibrated successfully");
      display->clearScreen();
      _isCalibrating = false;
    }
  }
  // Need to calculate touch screen locations for inputs here
}

void TFT_eSPITouch::check() {
  if (_tft == nullptr) {
    return;
  }
  uint16_t touchX;
  uint16_t touchY;
  if (_tft->getTouch(&touchX, &touchY)) {
    LOG(LogLevel::DEBUG, "TFT_eSPITouch::check() - touchX=%d|touchY=%d", touchX, touchY);
    InputAction action = _debounceOrHeld(InputAction::PRESS_UP);
    if (_callback != nullptr) {
      _callback->onInputAction(action);
    }
  }
}

bool TFT_eSPITouch::_calibrated() {
  bool isCalibrated = true;
  LOG(LogLevel::DEBUG, "TFT_eSPITouch::_calibrated() - %s", (isCalibrated ? "true" : "false"));
  return isCalibrated;
}

bool TFT_eSPITouch::_doCalibration() { return true; }

#endif // PIO_UNIT_TESTING
