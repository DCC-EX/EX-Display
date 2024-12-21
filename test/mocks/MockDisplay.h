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

#ifndef MOCKDISPLAY_H
#define MOCKDISPLAY_H

#include "DisplayInterface.h"
#include <gmock/gmock.h>

/// @brief Mock physical display class
class MockDisplay : public DisplayInterface<int> {
public:
  MOCK_METHOD(void, begin, (), (override));

  MOCK_METHOD(void, clearScreen, (), (override));

  MOCK_METHOD(void, displayRow, (int row, const char *text, bool underlined, int column), (override));

  MOCK_METHOD(void, clearRow, (int row), (override));

  MOCK_METHOD(void, displayStartupInfo, (const char *version), (override));
};

#endif // MOCKDISPLAY_H
