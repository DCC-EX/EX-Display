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
#include "test/mocks/MockSPIDisplay.h"
#include <gtest/gtest.h>

// Include CreateDeviceMacros last
#include "CreateDeviceMacros.h"

using namespace testing;

/// @brief Test harness for creating user defined devices via the compiler macros
/// This test harness uses devices defined in test/mocks/MockMyConfig.h
class CompilerCreationTests : public Test {
protected:
  void SetUp() override {}

  void TearDown() override {}
};

/// @brief user devices and ensure all attributes are valid
TEST_F(CompilerCreationTests, CreateDisplays) {
  // Create DisplayManager instance and create displays
  DisplayManager *displayManager = new DisplayManager();
  displayManager->createDisplays();

  // Ensure three displays have been created with correct IDs and attributes
  MockDisplay *display0 = static_cast<MockDisplay *>(displayManager->getDisplayById(0));
  MockSPIDisplay *display1 = static_cast<MockSPIDisplay *>(displayManager->getDisplayById(1));
  MockSPIDisplay *display2 = static_cast<MockSPIDisplay *>(displayManager->getDisplayById(2));

  ASSERT_NE(display0, nullptr);
  ASSERT_NE(display1, nullptr);
  ASSERT_NE(display2, nullptr);

  // Validate the list is as expected
  ASSERT_NE(displayManager->getFirstDisplay(), nullptr);
  EXPECT_EQ(displayManager->getFirstDisplay()->getId(), 0);
  ASSERT_NE(displayManager->getFirstDisplay()->getNext(), nullptr);
  DisplayInterface *next = displayManager->getFirstDisplay()->getNext();
  EXPECT_EQ(next->getCSPin(), 22);
  ASSERT_NE(next->getNext(), nullptr);
  next = next->getNext();
  EXPECT_EQ(next->getNext(), nullptr);
  EXPECT_EQ(next->getCSPin(), 23);

  // MockSPIDisplay instances should have CS pin set
  EXPECT_EQ(display1->getCSPin(), 22);
  EXPECT_EQ(display2->getCSPin(), 23);

  // All three displays should have begin() called from DisplayManager
  EXPECT_CALL(*display0, begin()).Times(1);
  EXPECT_CALL(*display1, begin()).Times(1);
  EXPECT_CALL(*display2, begin()).Times(1);

  displayManager->startDisplays();

  // Verify all expectations
  testing::Mock::VerifyAndClearExpectations(display0);
  testing::Mock::VerifyAndClearExpectations(display1);
  testing::Mock::VerifyAndClearExpectations(display2);

  // Clean up
  delete displayManager;
}
