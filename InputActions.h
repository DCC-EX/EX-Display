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

#ifndef INPUTACTION_H
#define INPUTACTION_H

/// @brief Input action to be returned from the user interface to control screens and displays
enum InputAction {
  PRESS_NONE,
  PRESS_UP,
  PRESS_DOWN,
  PRESS_LEFT,
  PRESS_RIGHT,
  PRESS_CENTRE,
  HOLD_UP,
  HOLD_DOWN,
  HOLD_LEFT,
  HOLD_RIGHT,
  HOLD_CENTRE
};

#endif // INPUTACTION_H
