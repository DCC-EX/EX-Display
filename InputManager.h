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

#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "CallbackInterface.h"
#include "Defines.h"
#include "DisplayInterface.h"
#include "InputInterface.h"
#include "Logger.h"

class InputManager {
public:
  /// @brief Constructor for the InputManager
  InputManager();

  /// @brief Call once to create the InputInterface derived input
  void createInput();

  /// @brief Set the InputInterface
  /// @param input Pointer to the InputInterface
  void addInput(InputInterface *input);

  /// @brief Get the configured InputInterface
  /// @return Pointer to the input
  InputInterface *getInput();

  /// @brief Set the display interface to retrieve required attributes - note this should only be required for TFT_eSPI
  /// touch screens that share the same instance between display and touch
  /// @param display Pointer to the DisplayInterface
  void setDisplay(DisplayInterface *display);

  /// @brief Start the configured input - calls the InputInterface::begin() method
  void startInput();

  /// @brief Set the Logger instance
  /// @param logger Pointer to the Logger
  void setLogger(Logger *logger);

  /// @brief Set the CallbackInterface derived instance for user input to use for callbacks
  /// @param callback Pointer to the instance
  void setCallback(CallbackInterface *callback);

  /// @brief Destructor for the InputManager
  ~InputManager();

private:
  DisplayInterface *_display;
  InputInterface *_input;
  Logger *_logger;
  CallbackInterface *_callback;
};

#endif // INPUTMANAGER_H
