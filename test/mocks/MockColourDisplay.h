/*
 *  © 2025 Peter Cole
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

#ifndef MOCKCOLOURDISPLAY_H
#define MOCKCOLOURDISPLAY_H

#include "DisplayInterface.h"
#include "Screen.h"
#include <gmock/gmock.h>

/// @brief Mock colour display class for format testing
class MockColourDisplay : public DisplayInterface {
public:
  MOCK_METHOD(void, begin, (), (override));

  MOCK_METHOD(void, clearScreen, (), (override));

  MOCK_METHOD(void, displayScreen, (Screen * screen), (override));

  MOCK_METHOD(void, displayStartupInfo, (const char *version), (override));

  void displayRow(int row, const char *text) { formatRow(row, text); }

  MOCK_METHOD(void, displayFormattedRow,
              (uint8_t row, uint8_t column, RowAttributes attributes, const char *text, bool append), (override));

  static MockColourDisplay *create() {
    MockColourDisplay *newDisplay = new MockColourDisplay();
    return newDisplay;
  }
};

#endif // MOCKCOLOURDISPLAY_H
