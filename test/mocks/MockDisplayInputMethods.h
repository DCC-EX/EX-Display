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

#ifndef MOCKINPUTDISPLAYMETHODS_H
#define MOCKINPUTDISPLAYMETHODS_H

// createDisplays() dummy implementation due to not using compiler to create them
#include "DisplayManager.h"
void DisplayManager::createDisplays() {}

// createInput() dummy implementation due to not using compiler to create it
#include "InputManager.h"
void InputManager::createInput() {}

#endif // MOCKINPUTDISPLAYMETHODS_H
