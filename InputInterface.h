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

#ifndef INPUTINTERFACE_H
#define INPUTINTERFACE_H

#include "Logger.h"

class CallbackInterface;

/// @brief Input action to be returned from the user interface to control screens and displays
enum InputAction { PRESS_UP, PRESS_DOWN, PRESS_LEFT, PRESS_RIGHT, PRESS_CENTRE };

/// @brief Class to abstract away all physical input implementatio to enable multiple input types
/// Default return should be PRESS_NONE
class InputInterface {
public:
  /// @brief Perform any initial once off setup or configuration here and call only once
  virtual void begin() = 0;

  /// @brief Call this method at least once per main loop to monitor for input actions
  /// Any actions should call the callback set in the _callback attribute
  virtual void check() = 0;

  /// @brief Set the instance for callbacks when users trigger an input action
  /// @param callback Class instance derived from the CallbackInterface class
  /// Must call the method onInputAction(InputAction);
  void setCallback(CallbackInterface *callback) { _callback = callback; }

  /// @brief Set the logger instance to use for diagnostic logging
  /// @param logger Pointer to the Logger instance to use
  void setLogger(Logger *logger) { _logger = logger; }

  /// @brief Destructor for an InputInterface
  virtual ~InputInterface() = default;

protected:
  CallbackInterface *_callback = nullptr;
  Logger *_logger = nullptr;
};

#endif // INPUTINTERFACE_H
