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
 * @brief Preprocessor macros to create user specified devices from myConfig.h
 */

#ifndef CREATEDEVICEMACROS_H
#define CREATEDEVICEMACROS_H

#include "CreateDeviceMacroReset.h"
#undef DISPLAY
#define DISPLAY(type, params...) this->addDisplay(type::create(params));
void DisplayManager::createDisplays() {
#ifndef PIO_UNIT_TESTING
#if __has_include("myConfig.h")
#include "myConfig.h"
#else
#error No myConfig.h created, no displays or input devices available
#endif // myConfig.h
#else
#include "test/mocks/MockMyConfig.h"
#endif // PIO_UNIT_TESTING
}

#endif // CREATEDEVICEMACROS_H
