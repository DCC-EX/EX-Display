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

#include "Version.h"
#include "test/mocks/MockDisplay.h"
#include <gtest/gtest.h>

using namespace testing;

/// @brief Test harness for physical display interface tests
class DisplayInterfaceTests : public Test {
protected:
  MockDisplay display;

  void SetUp() override {}

  void TearDown() override {}
};

TEST_F(DisplayInterfaceTests, TestBasicMethods) {
  // Ensure the basic methods are called once
  EXPECT_CALL(display, begin()).Times(1);
  display.begin();

  EXPECT_CALL(display, clearScreen()).Times(1);
  display.clearScreen();
}

TEST_F(DisplayInterfaceTests, TestParameterMethods) {
  // Test methods requiring SCREEN() parameters
  int expectRow = 2;
  const char *expectRowText = "This is text for row 2";
  bool expectUnderline = true;
  int expectColumn = 1;

  // Setup the expected displayRow call to validate parameters are received and called only once
  EXPECT_CALL(display, displayRow(Truly([=](int row) { return row == expectRow; }), StrEq(expectRowText),
                                  Truly([=](bool underline) { return underline == expectUnderline; }),
                                  Truly([=](int column) { return column == expectColumn; })))
      .Times(1);

  // Call the method that should trigger displayRow
  display.displayRow(2, "This is text for row 2", true, 1);

  // Setup the expected clearRow call
  EXPECT_CALL(display, clearRow(Truly([=](int row) { return row == expectRow; }))).Times(1);

  // Call it
  display.clearRow(2);
}

TEST_F(DisplayInterfaceTests, TestStartupInfo) {
  // Set up version text
  const char *expectedVersion = VERSION;

  // Setup expectation
  EXPECT_CALL(display, displayStartupInfo(StrEq(expectedVersion))).Times(1);

  // Call it
  display.displayStartupInfo(VERSION);
}
