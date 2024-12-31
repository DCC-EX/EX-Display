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

#ifndef MOCKSPIDISPLAY_H
#define MOCKSPIDISPLAY_H

#include "DisplayInterface.h"
#include <gmock/gmock.h>

/// @brief Mock physical display class for an SPI device
/// Use this mock to test manual switching between SPI devices
/// Constructor with no CS pin should never switch, and one with the CS pin should always switch
class MockSPIDisplay : public DisplayInterface {
public:
  MockSPIDisplay() {}

  MockSPIDisplay(int csPin) { _csPin = csPin; }

  MOCK_METHOD(void, begin, (), (override));

  MOCK_METHOD(void, clearScreen, (), (override));

  MOCK_METHOD(void, displayRow, (uint8_t row, const char *text, bool underlined, uint8_t column), (override));

  MOCK_METHOD(void, clearRow, (uint8_t row), (override));

  MOCK_METHOD(void, displayStartupInfo, (const char *version), (override));

  static MockSPIDisplay *create(int csPin = -1) {
    MockSPIDisplay *newDisplay = new MockSPIDisplay(csPin);
    return newDisplay;
  }
};

#endif // MOCKSPIDISPLAY_H
