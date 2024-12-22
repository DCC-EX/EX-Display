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

#ifndef CALLBACKINTERFACE_H
#define CALLBACKINTERFACE_H

#include "InputInterface.h"
#include "Logger.h"
#include <Arduino.h>

/// @brief Interface class to use for callbacks
class CallbackInterface {
public:
  /// @brief Method to implement updating a screen
  /// @param screenId ID of the screen to update
  /// @param row Row number to update
  /// @param text Text to update
  virtual void updateScreen(uint8_t screenId, uint8_t row, const char *text) = 0;

  /// @brief Method to implement to respond to an input action
  /// @param action PRESS_UP, PRESS_DOWN, PRESS_LEFT, PRESS_RIGHT, PRESS_CENTRE
  virtual void onInputAction(InputAction action) = 0;

  /// @brief Set the logger instance to use for diagnostic logging
  /// @param logger Pointer to the Logger instance to use
  void setLogger(Logger *logger) { _logger = logger; }

  /// @brief Virtual destructor for the CallBackInterface
  virtual ~CallbackInterface() = default;

protected:
  /// @brief Pointer to the logger interface
  Logger *_logger = nullptr;
};

#endif // CALLBACKINTERFACE_H
