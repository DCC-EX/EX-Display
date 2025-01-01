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

#include "DisplayManager.h"
#include "ScreenManager.h"
#include "test/mocks/MockDisplay.h"
#include <gtest/gtest.h>

using namespace testing;

/// @brief Test harness for testing DisplayManager
class DisplayScreenTests : public Test {
protected:
  DisplayManager *displayManager = new DisplayManager();
  ScreenManager *screenManager = new ScreenManager();

  void SetUp() override {}

  void TearDown() override {
    delete displayManager;
    delete screenManager;
  }
};

/// @brief Ensure the first display has a valid screen ID to display
TEST_F(DisplayScreenTests, CreateDisplay) {
  // Create first mock display and add it to the DisplayManager
  MockDisplay *display0 = new MockDisplay;
  displayManager->addDisplay(display0);

  // Expect our display will start with an invalid screen ID
  EXPECT_EQ(display0->getScreenId(), -1);

  // Call displayManager->update() should default its screen ID to its display ID
  displayManager->update(screenManager);
  EXPECT_EQ(display0->getScreenId(), 0);

  // Create a screen and validate the first one has this ID
  screenManager->updateScreen(0);
  EXPECT_EQ(screenManager->getFirstScreen()->getId(), 0);

  // First update of a display with a screen should cause a clearScreen() call
  EXPECT_CALL(*display0, clearScreen()).Times(1);

  // Call controller->update() and display should still have the first screen ID
  displayManager->update(screenManager);
  EXPECT_EQ(display0->getScreenId(), 0);

  // Add another screen and make sure display screen ID is unchanged
  screenManager->updateScreen(10);
  EXPECT_EQ(display0->getScreenId(), 0);

  // Verify all expectations were made
  testing::Mock::VerifyAndClearExpectations(display0);
}

/// @brief Validate that update() correctly calls display instance updates
TEST_F(DisplayScreenTests, UpdateDisplays) {
  // Create some mock displays
  MockDisplay *display0 = new MockDisplay();
  MockDisplay *display1 = new MockDisplay();
  displayManager->addDisplay(display0);
  displayManager->addDisplay(display1);

  // Setup two screens and a row each
  screenManager->updateScreen(0);
  screenManager->updateScreen(1);
  screenManager->getScreenById(0)->updateScreenRow(0, "Screen 0 row 0");
  screenManager->getScreenById(1)->updateScreenRow(0, "Screen 1 row 0");

  // When calling displayManager->update(screenManager), both displays should have update called
  EXPECT_CALL(*display0, displayRow(Truly([=](int row) { return row == 0; }), StrEq("Screen 0 row 0"),
                                    Truly([=](bool underline) { return underline == false; }),
                                    Truly([=](int column) { return column == 0; })))
      .Times(1);
  EXPECT_CALL(*display1, displayRow(Truly([=](int row) { return row == 0; }), StrEq("Screen 1 row 0"),
                                    Truly([=](bool underline) { return underline == false; }),
                                    Truly([=](int column) { return column == 0; })))
      .Times(1);

  // First update of a display with a screen should cause a clearScreen() call
  EXPECT_CALL(*display0, clearScreen()).Times(1);
  EXPECT_CALL(*display1, clearScreen()).Times(1);

  // Call update
  displayManager->update(screenManager);

  // Verify all expectations were made
  testing::Mock::VerifyAndClearExpectations(display0);
  testing::Mock::VerifyAndClearExpectations(display1);
}
