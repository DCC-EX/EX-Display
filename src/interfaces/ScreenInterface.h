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

#ifndef SCREENINTERFACE_H
#define SCREENINTERFACE_H

/// @brief Class for all physical screen classes to implement
/// All logical displays must be associated with a screen interface, not directly to a screen implementation
class ScreenInterface {
public:
  /// @brief Perform any initial once off setup or configuration here
  virtual void begin() = 0;

  /// @brief Clear the entire screen
  virtual void clearScreen() = 0;
};

#endif // SCREENINTERFACE_H
