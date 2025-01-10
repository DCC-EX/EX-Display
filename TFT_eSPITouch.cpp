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

// Do not load when testing, TFT_eSPI library is incompatible and will cause failures.
#ifndef PIO_UNIT_TESTING

// Must include SPIFFS before any other includes - Espressif limitation
#include "SPIFFS.h"

// Others here
#include "CallbackInterface.h"
#include "TFT_eSPITouch.h"

TFT_eSPITouch::TFT_eSPITouch(int displayId) : _tft(nullptr), _calibrationFile("/calibrationData") {
  _needsDisplay = displayId;
  _isCalibrating = false;
}

void TFT_eSPITouch::begin() {
  LOG(LogLevel::LOG_DEBUG, "TFT_eSPITouch::begin()");
  // Can't do anything without a TFT_eSPIDisplay or TFT_eSPI instance
  if (_display == nullptr) {
    LOG(LogLevel::LOG_ERROR, "An existing DisplayInterface instance is not set, cannot use touch");
    return;
  }
  // The display must be able to be cast to a TFT_eSPIDisplay instance to be valid
  TFT_eSPIDisplay *display = static_cast<TFT_eSPIDisplay *>(_display);
  if (!display) {
    LOG(LogLevel::LOG_ERROR, "Provided DisplayInterface is not a TFT_eSPIDisplay type, cannot use touch");
    return;
  }
  _tft = display->getTFT_eSPIInstance();
  if (!_tft) {
    LOG(LogLevel::LOG_ERROR, "An existing TFT_eSPI instance is not set, cannot use touch");
    return;
  }
  // If the display instance didn't initialised the tft instance, it must be done first, call begin()
  if (!display->tftInitialised()) {
    LOG(LogLevel::LOG_WARN, "The associated TFT_eSPIDislay instance %d has not been initialised, initialising now",
        display->getId());
    display->begin();
  }
  // If SPIFFS isn't setup or can't be formatted etc., we can't save calibration, don't do it
  if (!_setupSPIFFS()) {
    LOG(LogLevel::LOG_ERROR, "SPIFFS filesystem unable to begin, calibration not possible");
    return;
  }
  // If the touch input isn't calibrated, do it first
  if (!_calibrated()) {
    LOG(LogLevel::LOG_DEBUG, "TFT_eSPI touch input not calibrated, starting");
    _isCalibrating = true;
    // If calibration fails, or data can't be saved, show the user an error and halt for 5 secs
    // This will allow normal display operationg to resume, but input won't be reliable
    if (!_doCalibration()) {
      LOG(LogLevel::LOG_ERROR, "TFT_eSPI touch input calibration failed");
      _displayCalibrationError(display);
      _isCalibrating = false;
    } else {
      // Otherwise clear the screen and continue
      LOG(LogLevel::LOG_DEBUG, "TFT_eSPI touch input calibrated successfully");
      display->clearScreen();
      _isCalibrating = false;
    }
  }
}

void TFT_eSPITouch::check() {
  if (_tft == nullptr) {
    return;
  }
  InputAction action = InputAction::PRESS_NONE;
  uint16_t touchX;
  uint16_t touchY;
  if (_tft->getTouch(&touchX, &touchY)) {
    LOG(LogLevel::LOG_DEBUG, "TFT_eSPITouch::check() - touchX=%d|touchY=%d", touchX, touchY);
    action = _calculateInputAction(touchX, touchY, _tft->width(), _tft->height());
  }
  action = _debounceOrHeld(action);
  if (_callback != nullptr && action != InputAction::PRESS_NONE) {
    _callback->onInputAction(action);
  }
}

TFT_eSPITouch *TFT_eSPITouch::create(int displayId) {
  TFT_eSPITouch *newTouch = new TFT_eSPITouch(displayId);
  return newTouch;
}

bool TFT_eSPITouch::_calibrated() {
  if (_forceCalibration) {
    return false;
  }
  uint16_t calibrationData[5];
  File file = SPIFFS.open(_calibrationFile, "r");
  if (!file) {
    LOG(LogLevel::LOG_WARN, "Calibration file not available, calibration required");
    return false;
  }
  bool dataValid = false;
  if (file.readBytes((char *)calibrationData, 14) == 14) {
    dataValid = true;
    file.close();
  }
  if (!dataValid) {
    LOG(LogLevel::LOG_WARN, "Saved calibration data not valid, calibration required");
    return false;
  }
  _tft->setTouch(calibrationData);
  return true;
}

bool TFT_eSPITouch::_doCalibration() {
  LOG(LogLevel::LOG_WARN, "Calibration process commenced");
  uint16_t calibrationData[5];
  _tft->calibrateTouch(calibrationData, TFT_WHITE, TFT_RED, 15);
  File file = SPIFFS.open(_calibrationFile, "w");
  if (file) {
    file.write((const unsigned char *)calibrationData, 14);
    file.close();
    LOG(LogLevel::LOG_MESSAGE, "Calibration succeeded");
    return true;
  }
  LOG(LogLevel::LOG_ERROR, "Calibration process failed");
  return false;
}

bool TFT_eSPITouch::_setupSPIFFS() {
  bool setup = false;
  if (!SPIFFS.begin()) {
    LOG(LogLevel::LOG_WARN, "SPIFFS filesystem has not been initialised, formatting now, calibration required");
    SPIFFS.format();
    if (SPIFFS.begin()) {
      setup = true;
    }
  } else {
    setup = true;
  }
  return setup;
}

void TFT_eSPITouch::_displayCalibrationError(TFT_eSPIDisplay *display) {
  display->clearScreen();
  DisplayInterface::formatRow(display, 0, "`_``#FF0000`ERROR!");
  DisplayInterface::formatRow(display, 1, "TFT_eSPI touch input calibration failed");
  DisplayInterface::formatRow(display, 2, "Touch input will be unreliable");
  DisplayInterface::formatRow(display, 3, "Operation resumes in 5 seconds");
  delay(5000);
  display->clearScreen();
}

#endif // PIO_UNIT_TESTING
