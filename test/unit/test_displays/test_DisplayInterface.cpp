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
  MockDisplay *display;

  void SetUp() override { display = new MockDisplay(); }

  void TearDown() override { delete display; }
};

/// @brief Test basic DisplayInterface methods
TEST_F(DisplayInterfaceTests, TestBasicMethods) {
  // Ensure the basic methods are called once
  EXPECT_CALL(*display, begin()).Times(1);
  display->begin();

  EXPECT_CALL(*display, clearScreen()).Times(1);
  display->clearScreen();

  // Validate there is no next display
  EXPECT_EQ(display->getNext(), nullptr);

  // First display should have ID 0
  EXPECT_EQ(display->getId(), 0);

  // Screen ID this display is displaying should start at 0
  EXPECT_EQ(display->getScreenId(), 0);
}

/// @brief Test DisplayInterface methods that should interact with a physical display
TEST_F(DisplayInterfaceTests, TestParameterMethods) {
  // Test methods requiring SCREEN() parameters
  int expectRow = 2;
  const char *expectRowText = "This is text for row 2";
  bool expectUnderline = true;
  int expectColumn = 1;

  // Setup the expected displayRow call to validate parameters are received and called only once
  EXPECT_CALL(*display, displayRow(Truly([=](int row) { return row == expectRow; }), StrEq(expectRowText),
                                   Truly([=](bool underline) { return underline == expectUnderline; }),
                                   Truly([=](int column) { return column == expectColumn; })))
      .Times(1);

  // Call the method that should trigger displayRow
  display->displayRow(2, "This is text for row 2", true, 1);

  // Setup the expected clearRow call
  EXPECT_CALL(*display, clearRow(Truly([=](int row) { return row == expectRow; }))).Times(1);

  // Call it
  display->clearRow(2);

  // Make sure the screen ID is updated
  display->setScreenId(4);
  EXPECT_EQ(display->getScreenId(), 4);
  display->setScreenId(1);
  EXPECT_EQ(display->getScreenId(), 1);
}

/// @brief Test to ensure the startup info sets the EX-Display version correctly
TEST_F(DisplayInterfaceTests, TestStartupInfo) {
  // Set up version text
  const char *expectedVersion = VERSION;

  // Setup expectation
  EXPECT_CALL(*display, displayStartupInfo(StrEq(expectedVersion))).Times(1);

  // Call it
  display->displayStartupInfo(VERSION);
}

/// @brief Test a second display can be accessed via the first in a list
TEST_F(DisplayInterfaceTests, TestTwoDisplays) {
  // Create a second mock display
  MockDisplay *display2 = new MockDisplay();
  display2->setId(1);
  EXPECT_EQ(display2->getId(), 1);

  // Ensure the basic methods are called once
  EXPECT_CALL(*display2, begin()).Times(1);
  display2->begin();

  EXPECT_CALL(*display2, clearScreen()).Times(1);
  display2->clearScreen();

  // Validate there is no next display
  EXPECT_EQ(display2->getNext(), nullptr);

  // Add to the first and validate
  display->setNext(display2);
  EXPECT_EQ(display->getNext(), display2);

  // Clean up
  delete display2;
}
