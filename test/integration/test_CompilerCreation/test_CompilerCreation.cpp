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

#include "CreateUserDevices.h"
#include "test/mocks/MockCallback.h"
#include <gtest/gtest.h>

using namespace testing;

/// @brief Test harness for creating user defined devices via the compiler macros
/// This test harness uses devices defined in test/mocks/MockMyConfig.h
class CompilerCreationTests : public Test {
protected:
  void SetUp() override {}

  void TearDown() override {}
};

/// @brief Ensure devices are created and all attributes are valid
TEST_F(CompilerCreationTests, CreateDevices) {
  // Create instances, displays, and input
  DisplayManager *displayManager = new DisplayManager();
  MockCallback *callback = new MockCallback();
  InputManager *inputManager = new InputManager();
  inputManager->setCallback(callback);
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

  // Now create the input
  inputManager->createInput();

  // Bail out if the input isn't created successfully, otherwise use it
  ASSERT_NE(inputManager->getInput(), nullptr);
  MockInput *input = static_cast<MockInput *>(inputManager->getInput());

  // begin() should be called once when started
  EXPECT_CALL(*input, begin()).Times(1);
  inputManager->startInput();

  // Expect check() to be called once
  // When called, this simulates a user selecting up
  EXPECT_CALL(*input, check()).WillOnce(Invoke([callback]() {
    // Simulate a button press by calling the callback
    callback->onInputAction(InputAction::PRESS_UP);
  }));

  // Expect onInputAction to be called with PRESS_UP
  EXPECT_CALL(*callback, onInputAction(InputAction::PRESS_UP)).Times(1);

  // Act
  input->check();

  // Verify all expectations
  testing::Mock::VerifyAndClearExpectations(display0);
  testing::Mock::VerifyAndClearExpectations(display1);
  testing::Mock::VerifyAndClearExpectations(display2);
  testing::Mock::VerifyAndClearExpectations(callback);
  testing::Mock::VerifyAndClearExpectations(input);

  // Clean up
  delete displayManager;
  delete inputManager;
  delete callback;
}
