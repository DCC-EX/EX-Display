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

InputManager::InputManager() : _input(nullptr) {}

void InputManager::createInput() {
// Do not load when testing, TFT_eSPI library is incompatible and will cause failures.
#ifndef PIO_UNIT_TESTING
// Create TFT_eSPITouch instance here
#endif // PIO_UNIT_TESTING
}

void InputManager::setInput(InputInterface *input) { _input = input; }

InputInterface *InputManager::getInput() { return _input; }

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
