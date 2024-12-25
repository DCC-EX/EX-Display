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

InputManager::InputManager() : _display(nullptr), _input(nullptr) {}

void InputManager::createInput(CallbackInterface *callback) {
// Do not load when testing, TFT_eSPI library is incompatible and will cause failures.
#ifndef PIO_UNIT_TESTING
  // Create TFT_eSPITouch instance here
  TFT_eSPITouch *touch = new TFT_eSPITouch();
  addInput(touch, callback);
#endif // PIO_UNIT_TESTING
}

void InputManager::addInput(InputInterface *input, CallbackInterface *callback) {
  if (input == nullptr) {
    return;
  }
  _input = input;
  if (callback != nullptr) {
    _input->setCallback(callback);
  }
}

InputInterface *InputManager::getInput() { return _input; }

void InputManager::setDisplay(DisplayInterface *display) { _display = display; }

void InputManager::startInput() {
  if (_input != nullptr) {
    _input->begin();
  }
}

InputManager::~InputManager() {
  if (_input != nullptr) {
    delete _input;
    _input = nullptr;
  }
}
