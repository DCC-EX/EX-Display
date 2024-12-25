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
#include "DisplayInterface.h"
#include "InputInterface.h"

class InputManager {
public:
  /// @brief Constructor for the InputManager
  InputManager();

  /// @brief Call once to create the InputInterface derived input
  /// @param callback CallbackInterface derived instance to call back to when user interacts with the input
  void createInput(CallbackInterface *callback);

  /// @brief Set the InputInterface
  /// @param input Pointer to the InputInterface
  /// @param callback CallbackInterface derived instance to call back to when user interacts with the input
  void addInput(InputInterface *input, CallbackInterface *callback);

  /// @brief Get the configured InputInterface
  /// @return Pointer to the input
  InputInterface *getInput();

  /// @brief Set the display interface to retrieve required attributes - note this should only be required for TFT_eSPI
  /// touch screens that share the same instance between display and touch
  /// @param display Pointer to the DisplayInterface
  void setDisplay(DisplayInterface *display);

  /// @brief Start the configured input - calls the InputInterface::begin() method
  void startInput();

  /// @brief Destructor for the InputManager
  ~InputManager();

private:
  DisplayInterface *_display;
  InputInterface *_input;
};

#endif // INPUTMANAGER_H
