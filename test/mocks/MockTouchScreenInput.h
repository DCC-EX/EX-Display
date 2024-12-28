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

#ifndef MOCKTOUCHSCREENINPUT_H
#define MOCKTOUCHSCREENINPUT_H

#include "CallbackInterface.h"
#include "InputInterface.h"
#include <gmock/gmock.h>

/// @brief Mock touch screen input class using debounce and hold methods and calculating touch position to determine the
/// "button" area of the screen that's been touched.
/// @details Use setTouch(int touchX, int touchY) and setScreenResolution(int width, int height) to set the
/// screen dimensions and simulate user touches (default 320 x 240). Call setDebounceHold(bool debounceHold) to enable
/// and disable debounce tests as well as touch position (default false). Call check() before/after time advances to
/// test debounce and hold.
class MockTouchScreenInput : public InputInterface {
public:
  MOCK_METHOD(void, begin, (), (override));

  void check() override {
    InputAction action = _calculateInputAction(_touchX, _touchY, _screenWidth, _screenHeight);
    if (_debounceHold) {
      action = _debounceOrHeld(action);
    }
    if (action != InputAction::PRESS_NONE && _callback != nullptr) {
      _callback->onInputAction(action);
    }
  }

  void setScreenResolution(int width, int height) {
    _screenWidth = width;
    _screenHeight = height;
  }

  void setTouch(int touchX, int touchY) {
    _touchX = touchX;
    _touchY = touchY;
  }

  void setDebounceHold(bool debounceHold) { _debounceHold = debounceHold; }

  void setIsCalibrating(bool isCalibrating) { _isCalibrating = isCalibrating; }

  void setNeedsDisplay(int displayId) { _needsDisplay = displayId; }

private:
  int _screenWidth = 320;
  int _screenHeight = 240;
  int _touchX = 0;
  int _touchY = 0;
  bool _debounceHold = false;
};

#endif // MOCKTOUCHSCREENINPUT_H
