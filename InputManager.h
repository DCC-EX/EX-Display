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

#include "InputInterface.h"

class InputManager {
public:
  /// @brief Constructor for the InputManager
  InputManager();

  /// @brief Call once to create the InputInterface derived input
  void createInput();

  /// @brief Set the InputInterface
  /// @param input 
  void setInput(InputInterface *input);

  /// @brief Get the configured InputInterface
  /// @return Pointer to the input
  InputInterface *getInput();

  /// @brief Start the configured input - calls the InputInterface::begin() method
  void startInput();

  /// @brief Destructor for the InputManager
  ~InputManager();

private:
  InputInterface *_input;
};

#endif // INPUTMANAGER_H
