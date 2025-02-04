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

#include "InputManager.h"

// Do not load when testing, TFT_eSPI library is incompatible and will cause failures.
#ifndef PIO_UNIT_TESTING
#include "TFT_eSPITouch.h"
#endif // PIO_UNIT_TESTING

InputManager::InputManager() : _display(nullptr), _input(nullptr), _logger(nullptr), _callback(nullptr) {}

void InputManager::addInput(InputInterface *input) {
  LOG(LogLevel::LOG_DEBUG, "InputManager::addInput()");
  if (input == nullptr) {
    LOG(LogLevel::LOG_ERROR, "InputInterface doesn't exist, user input will not be available");
    return;
  }
  _input = input;
  if (_logger) {
    _input->setLogger(_logger);
  }
  if (_callback == nullptr) {
    LOG(LogLevel::LOG_ERROR, "InputInterface callback not set, user input will not be available");
    return;
  }
  _input->setCallback(_callback);
#ifdef DEBOUNCE_DELAY
  _input->setDebounceDelay(DEBOUNCE_DELAY);
#endif // DEBOUNCE DELAY
#ifdef HOLD_THRESHOLD
  _input->setHoldThreshold(HOLD_THRESHOLD);
#endif // HOLD_THRESHOLD
#ifdef FORCE_CALIBRATION
  _input->forceCalibration();
#endif // FORCE_CALIBRATION
}

InputInterface *InputManager::getInput() { return _input; }

void InputManager::setDisplay(DisplayInterface *display) {
  if (display == nullptr || _input == nullptr) {
    return;
  }
  LOG(LogLevel::LOG_DEBUG, "InputManager::setDisplay() - display ID %d", display->getId());
  _input->setDisplay(display);
}

void InputManager::startInput() {
  LOG(LogLevel::LOG_DEBUG, "InputManager::startInput()");
  if (_input != nullptr) {
    _input->begin();
  }
}

void InputManager::setLogger(Logger *logger) { _logger = logger; }

void InputManager::setCallback(CallbackInterface *callback) { _callback = callback; }

InputManager::~InputManager() {
  if (_input != nullptr) {
    delete _input;
    _input = nullptr;
  }
}
