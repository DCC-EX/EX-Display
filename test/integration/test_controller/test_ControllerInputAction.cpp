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
  ScreenManager *screenManager = new ScreenManager;
  Controller *controller = new Controller(console, commandStation, displayManager, screenManager, nullptr, 0);

  void SetUp() override { input->setCallback(controller); }

  void TearDown() override {
    delete controller;
    delete screenManager;
    delete displayManager;
    delete commandStation;
    delete console;
    delete input;
  }
};

/// @brief This test ensures left/right buttons or touches switch the active screen
TEST_F(ControllerInputActionTests, SwitchActiveScreen) {
  // Set up mock display
  MockDisplay *display0 = new MockDisplay();
  displayManager->addDisplay(display0);

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

  // Expect a single controller->update() should now ensure display is set to screen 0 (first)
  controller->update();
  EXPECT_EQ(display0->getScreenId(), 0);

  // Single left press/touch should select the previous screen ID which is 8
  EXPECT_CALL(*input, check()).WillOnce(Invoke([this]() { this->controller->onInputAction(InputAction::PRESS_LEFT); }));

  // Now call input->check() to action the left press
  input->check();

  // Display0's screen ID should now be 8
  EXPECT_EQ(display0->getScreenId(), 8);

  // Press again to go to 2
  EXPECT_CALL(*input, check()).WillOnce(Invoke([this]() { this->controller->onInputAction(InputAction::PRESS_LEFT); }));

  // Now call input->check() to action the left press
  input->check();

  // Display0's screen ID should now be 2
  EXPECT_EQ(display0->getScreenId(), 2);

  // Once more to go to the start at 0
  EXPECT_CALL(*input, check()).WillOnce(Invoke([this]() { this->controller->onInputAction(InputAction::PRESS_LEFT); }));

  // Now call input->check() to action the left press
  input->check();

  // Display0's screen ID should now be 0
  EXPECT_EQ(display0->getScreenId(), 0);

  // Pressing/touching right twice should get us to ID 8
  EXPECT_CALL(*input, check())
      .Times(2)
      .WillOnce(Invoke([this]() { this->controller->onInputAction(InputAction::PRESS_RIGHT); }))
      .WillOnce(Invoke([this]() { this->controller->onInputAction(InputAction::PRESS_RIGHT); }));
  
  // Call input-check() twice
  input->check();
  input->check();

  // Display0's screen ID should now be 8
  EXPECT_EQ(display0->getScreenId(), 8);
}

/// @brief This test ensures up/down buttons or touches scrolls the active screen
// TEST_F(ControllerInputActionTests, ScrollActiveScreen) {}

/// @brief This test ensures a centre button or touch switches control between displays
// TEST_F(ControllerInputActionTests, SwitchDisplayControl) {}
