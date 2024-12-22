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
#include "test/mocks/MockDisplay.h"
#include <gtest/gtest.h>

using namespace testing;

/// @brief Test harness for testing DisplayManager
class DisplayManagerTests : public Test {
protected:
  void SetUp() override {}

  void TearDown() override {}
};

/// @brief Create DisplayManager and validate attributes are as expected
TEST_F(DisplayManagerTests, CreateDisplayManager) {
  DisplayManager *displayManager = new DisplayManager();

  EXPECT_NE(displayManager, nullptr);
  EXPECT_EQ(displayManager->getFirstDisplay(), nullptr);

  delete displayManager;
}

/// @brief Create a list of mock displays and validate they are created and operate correctly
TEST_F(DisplayManagerTests, CreateDisplayList) {
  DisplayManager *displayManager = new DisplayManager();
  MockDisplay *display0 = new MockDisplay();
  MockDisplay *display1 = new MockDisplay();
  MockDisplay *display2 = new MockDisplay();

  // These should all have ID 0 to start
  EXPECT_EQ(display0->getId(), 0);
  EXPECT_EQ(display1->getId(), 0);
  EXPECT_EQ(display2->getId(), 0);

  // Add to DisplayManager and should now have correct IDs
  displayManager->addDisplay(display0);
  displayManager->addDisplay(display1);
  displayManager->addDisplay(display2);

  EXPECT_EQ(display0->getId(), 0);
  EXPECT_EQ(display1->getId(), 1);
  EXPECT_EQ(display2->getId(), 2);

  // Validate the list is ordered as expected
  auto *test = displayManager->getFirstDisplay();
  EXPECT_EQ(test, display0);
  test = test->getNext();
  EXPECT_EQ(test, display1);
  test = test->getNext();
  EXPECT_EQ(test, display2);
  EXPECT_EQ(test->getNext(), nullptr);

  delete displayManager;
}
