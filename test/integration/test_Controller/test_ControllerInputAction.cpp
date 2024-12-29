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
#include "InputManager.h"
#include "ScreenManager.h"
#include "test/mocks/MockDisplay.h"
#include "test/mocks/MockInput.h"
#include "test/mocks/Stream.h"
#include <gtest/gtest.h>

using namespace testing;

/// @brief Test harness for input actions interacting with the Controller
class ControllerInputActionTests : public Test {
protected:
  MockInput *input = new MockInput;
  Stream *console = new Stream;
  Stream *commandStation = new Stream;
  DisplayManager *displayManager = new DisplayManager;
  InputManager *inputManager = new InputManager;
  ScreenManager *screenManager = new ScreenManager;
  Controller *controller =
      new Controller(console, commandStation, displayManager, inputManager, screenManager, nullptr, 0);

  void SetUp() override { inputManager->addInput(input, controller); }

  void TearDown() override {
    delete controller;
    delete screenManager;
    delete displayManager;
    delete inputManager;
    delete commandStation;
    delete console;
  }
};

/// @brief This test ensures left/right buttons or touches switch the active screen
TEST_F(ControllerInputActionTests, SwitchActiveScreen) {
  // Set up mock display
  MockDisplay *display0 = new MockDisplay();
  displayManager->addDisplay(display0);

  // Validate our input isn't null
  EXPECT_NE(input, nullptr);

  // Current screen for display0 should be invalid
  EXPECT_EQ(display0->getScreenId(), -1);

  // Validate display0 is correctly in displayManager with the right ID
  EXPECT_EQ(displayManager->getFirstDisplay()->getId(), 0);

  // Create some screens out of order to validate switching order is correct
  screenManager->updateScreen(0);
  screenManager->updateScreen(8);
  screenManager->updateScreen(2);

  // Validate screens can be retrieved by ID
  EXPECT_EQ(screenManager->getScreenById(0)->getId(), 0);
  EXPECT_EQ(screenManager->getScreenById(8)->getId(), 8);
  EXPECT_EQ(screenManager->getScreenById(2)->getId(), 2);

  // Set up all call expectations first
  EXPECT_CALL(*input, check())
      .Times(7)           // Expect 7 calls total to input->check()
      .WillOnce(Return()) // First will have no return with no input
      .WillOnce(Invoke([this]() { controller->onInputAction(InputAction::PRESS_LEFT); }))  // First press left
      .WillOnce(Invoke([this]() { controller->onInputAction(InputAction::PRESS_LEFT); }))  // Second press left
      .WillOnce(Invoke([this]() { controller->onInputAction(InputAction::PRESS_LEFT); }))  // Third press left
      .WillOnce(Invoke([this]() { controller->onInputAction(InputAction::PRESS_RIGHT); })) // First press right
      .WillOnce(Invoke([this]() { controller->onInputAction(InputAction::PRESS_RIGHT); })) // Second press right
      .WillOnce(Return()); // Last will have no return with no input

  // Expect a single controller->update() should now ensure display is set to screen 0 (first)
  controller->update();
  EXPECT_EQ(display0->getScreenId(), 0);

  // Now controller->update() should action the left press
  controller->update();

  // Display0's screen ID should now be 8
  EXPECT_EQ(display0->getScreenId(), 8);

  // Now call controller->update() should action the left press
  controller->update();

  // Display0's screen ID should now be 2
  EXPECT_EQ(display0->getScreenId(), 2);

  // Now call controller->update() should action the left press
  controller->update();

  // Display0's screen ID should now be 0
  EXPECT_EQ(display0->getScreenId(), 0);

  // Call controller->update() twice
  controller->update();
  controller->update();

  // Display0's screen ID should now be 8
  EXPECT_EQ(display0->getScreenId(), 8);

  controller->update();

  // Display0's screen ID should be unchanged at 8
  EXPECT_EQ(display0->getScreenId(), 8);

  // Verify all expectations were made
  testing::Mock::VerifyAndClearExpectations(display0);
}

/// @brief This test ensures up/down buttons or touches scrolls the active screen
// TEST_F(ControllerInputActionTests, ScrollActiveScreen) {}

/// @brief This test ensures a centre button or touch switches control between displays
// TEST_F(ControllerInputActionTests, SwitchDisplayControl) {}
