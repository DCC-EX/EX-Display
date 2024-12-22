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

#ifndef MOCKCALLBACK_H
#define MOCKCALLBACK_H

#include "CallbackInterface.h"
#include <gmock/gmock.h>

/// @brief Mock class to test callbacks
class MockCallback : public CallbackInterface {
public:
  MOCK_METHOD(void, updateScreen, (uint8_t screenId, uint8_t row, const char *text), ());

  MOCK_METHOD(void, onInputAction, (InputAction action), ());
};

#endif // MOCKCALLBACK_H
