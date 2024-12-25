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

#include "Controller.h"
#include "DisplayManager.h"
#include "ScreenManager.h"
#include "test/mocks/MockDisplay.h"
#include <gtest/gtest.h>

using namespace testing;

/// @brief Integration test harness for ensuring displays are set to display valid screens
class ValidDisplayScreenTests : public Test {
protected:
  DisplayManager *displayManager = new DisplayManager;
  ScreenManager *screenManager = new ScreenManager;
  Controller *controller = new Controller(nullptr, nullptr, displayManager, screenManager, nullptr, 0);

  void SetUp() override {}

  void TearDown() override {
    delete controller;
    delete displayManager;
    delete screenManager;
  }
};

/// @brief Ensure the first display has a valid screen ID to display
TEST_F(ValidDisplayScreenTests, CreateDisplay) {
  // Create first mock display and add it to the DisplayManager
  MockDisplay *display0 = new MockDisplay;
  displayManager->addDisplay(display0);

  // Expect our display will start with an invalid screen ID
  EXPECT_EQ(display0->getScreenId(), -1);

  // Call controller->update() should continue to have an invalid ID with no screens
  controller->update();
  EXPECT_EQ(display0->getScreenId(), -1);

  // Create a screen and validate the first one has this ID
  screenManager->updateScreen(10);
  EXPECT_EQ(screenManager->getFirstScreen()->getId(), 10);

  // Call controller->update() and display should now have the first screen ID
  controller->update();
  EXPECT_EQ(display0->getScreenId(), 10);

  // Add another screen and make sure display screen ID is unchanged
  screenManager->updateScreen(0);
  EXPECT_EQ(display0->getScreenId(), 10);
}