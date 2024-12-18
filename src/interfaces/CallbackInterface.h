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

#include <Arduino.h>

/// @brief Interface class to use for callbacks
class CallbackInterface {
public:
  /// @brief Method to implement updating a screen
  /// @param screenId ID of the screen to update
  /// @param row Row number to update
  /// @param text Text to update
  virtual void updateScreen(uint8_t screenId, uint8_t row, char *text) = 0;
};

#endif // CALLBACKINTERFACE_H
