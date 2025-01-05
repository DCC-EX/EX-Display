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

#include "InputInterface.h"

void InputInterface::setCallback(CallbackInterface *callback) { _callback = callback; }

void InputInterface::setLogger(Logger *logger) { _logger = logger; }

bool InputInterface::isCalibrating() { return _isCalibrating; }

int InputInterface::needsDisplay() { return _needsDisplay; }

void InputInterface::setDisplay(DisplayInterface *display) {
  if (display == nullptr) {
    return;
  }
  _display = display;
  LOG(LogLevel::LOG_DEBUG, "DisplayInterface::setDisplay() - display ID %d", _display->getId());
}

void InputInterface::setDebounceDelay(unsigned long delay) { _debounceDelay = delay; }

void InputInterface::setHoldThreshold(unsigned long threshold) { _holdThreshold = threshold; }

void InputInterface::forceCalibration() { _forceCalibration = true; }

InputAction InputInterface::_debounceOrHeld(InputAction currentAction) {
  // Record the current time for comparisons
  unsigned long currentTime = millis();
  InputAction returnAction = InputAction::PRESS_NONE;
  // If current and last actions differ, we're not pressing or holding, reset accordingly
  if (currentAction != _lastAction) {
    // If we're going from some action to none and not holding, then it must've been a press
    if ((currentTime - _lastDebounceTime) > _debounceDelay && currentAction == InputAction::PRESS_NONE && !_isHolding) {
      returnAction = _lastAction;
      LOG(LogLevel::LOG_DEBUG, "InputInterface::_debounceOrHeld() - press detected: %d", returnAction);
    }
    _lastDebounceTime = currentTime;
    _lastAction = currentAction;
    _isHolding = false;
    LOG(LogLevel::LOG_DEBUG, "InputInterface::_debounceOrHeld() - action changed, resetting");
    return returnAction;
  }
  // Check if the debounce time has been exceeded
  if (currentAction != InputAction::PRESS_NONE && (currentTime - _lastDebounceTime) > _debounceDelay) {
    // Check if the hold time has been exceeded
    if ((currentTime - _lastDebounceTime) > _holdThreshold) {
      if (!_isHolding) {
        // Flag that we're holding, and change from PRESS to HOLD
        _isHolding = true;
        LOG(LogLevel::LOG_DEBUG, "InputInterface::_debounceOrHeld() - hold detected: %d", currentAction);
        switch (currentAction) {
        case InputAction::PRESS_UP:
          returnAction = InputAction::HOLD_UP;
          break;
        case InputAction::PRESS_DOWN:
          returnAction = InputAction::HOLD_DOWN;
          break;
        case InputAction::PRESS_LEFT:
          returnAction = InputAction::HOLD_LEFT;
          break;
        case InputAction::PRESS_RIGHT:
          returnAction = InputAction::HOLD_RIGHT;
          break;
        case InputAction::PRESS_CENTRE:
          returnAction = InputAction::HOLD_CENTRE;
          break;
        default:
          returnAction = InputAction::PRESS_NONE;
          break;
        }
      }
    }
  }
  return returnAction;
}

InputAction InputInterface::_calculateInputAction(int touchX, int touchY, int displayWidth, int displayHeight) {
  LOG(LogLevel::LOG_DEBUG, "InputInterface::_calculateInputAction(%d, %d, %d, %d)", touchX, touchY, displayWidth,
      displayHeight);
  InputAction action = InputAction::PRESS_NONE;
  int thirdWidth = displayWidth / 3;
  int thirdHeight = displayHeight / 3;

  if (touchX <= thirdWidth) {
    action = InputAction::PRESS_LEFT;
  } else if (touchX >= displayWidth - thirdWidth) {
    action = InputAction::PRESS_RIGHT;
  } else if (touchY <= thirdHeight) {
    action = InputAction::PRESS_UP;
  } else if (touchY >= displayHeight - thirdHeight) {
    action = InputAction::PRESS_DOWN;
  } else {
    action = InputAction::PRESS_CENTRE;
  }
  return action;
}
