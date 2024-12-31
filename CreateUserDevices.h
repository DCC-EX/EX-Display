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
 * @brief Include this file in Configurator.h to ensure all user devices in myConfig.h are created
 * 
 */

#ifndef CREATEUSERDEVICES_H
#define CREATEUSERDEVICES_H

// Always include DisplayManager and InputManager for both testing and running
#include "DisplayManager.h"
// #include "InputManager.h"

#ifndef PIO_UNIT_TESTING
#include "TFT_eSPIDisplay.h"
#else
#include "test/mocks/MockDisplay.h"
#include "test/mocks/MockSPIDisplay.h"
#endif // PIO_UNIT_TESTING

// Include CreateDeviceMacros last to build the DisplayManager and InputManager implementation methods
#include "CreateDeviceMacros.h"

#endif // CREATEUSERDEVICES_H
