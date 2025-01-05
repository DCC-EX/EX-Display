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

#ifndef MOCKBUTTONINPUT_H
#define MOCKBUTTONINPUT_H

#include "CallbackInterface.h"
#include "InputInterface.h"
#include <gmock/gmock.h>

/// @brief Mock button input class using debounce and hold methods
/// Use setRawAction() to simulate what a button press will provide
/// Call check() before/after time advances to test debounce and hold
class MockButtonInput : public InputInterface {
public:
  MOCK_METHOD(void, begin, (), (override));

  void check() override {
    InputAction action = _debounceOrHeld(_rawAction);
    if (action != InputAction::PRESS_NONE && _callback != nullptr) {
      _callback->onInputAction(action);
    }
  }

  void setRawAction(InputAction action) { _rawAction = action; }

  void setIsCalibrating(bool isCalibrating) { _isCalibrating = isCalibrating; }

  void setNeedsDisplay(int displayId) { _needsDisplay = displayId; }

private:
  InputAction _rawAction;
};

#endif // MOCKBUTTONINPUT_H
