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

/**
 * @brief Preprocessor macros to create user specified devices from myDevices.h
 */

#ifndef CREATEDEVICEMACROS_H
#define CREATEDEVICEMACROS_H

// Process USER_DISPLAY entries
#include "CreateDeviceMacroReset.h"
#undef USER_DISPLAY
#define USER_DISPLAY(type, params...) this->addDisplay(type::create(params));
void DisplayManager::createDisplays() {
#ifndef PIO_UNIT_TESTING
#if __has_include("myDevices.h")
#include "myDevices.h"
#else
#error No myDevices.h created, no displays or input devices available
#endif // myDevices.h
#else
#include "test/mocks/MockMyDevices.h"
#endif // PIO_UNIT_TESTING
}

// Process USER_INPUT entry
#include "CreateDeviceMacroReset.h"
#undef USER_INPUT
#define USER_INPUT(type, params...) this->addInput(type::create(params));
void InputManager::createInput() {
#ifndef PIO_UNIT_TESTING
#if __has_include("myDevices.h")
#include "myDevices.h"
#else
#error No myDevices.h created, no displays or input devices available
#endif // myDevices.h
#else
#include "test/mocks/MockMyDevices.h"
#endif // PIO_UNIT_TESTING
}

#endif // CREATEDEVICEMACROS_H
