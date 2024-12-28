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

#include "test/mocks/MockCallback.h"
#include "test/mocks/MockTouchScreenInput.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace testing;

/// @brief Test harness for touch screen inputs requiring calculation of where the user has touched to be converted to a
/// valid InputAction
class TouchScreenInputTests : public Test {
protected:
  MockTouchScreenInput input;
  MockCallback callback;

  void SetUp() override {
    millis(); // Must call this to force time to be initialised
    input.setCallback(&callback);
  }

  void TearDown() override {}
};

/// @brief Simple test of attributes related to calibration of touch screens and reliance on a display instance
TEST_F(TouchScreenInputTests, TestAttributes) {
  // Default should be no calibration in progress, and a display ID of -1 to say there's no dependency
  EXPECT_FALSE(input.isCalibrating());
  EXPECT_EQ(input.needsDisplay(), -1);

  // Set calibration in progress and set a dependent display ID and validate
  input.setIsCalibrating(true);
  input.setNeedsDisplay(1);

  EXPECT_TRUE(input.isCalibrating());
  EXPECT_EQ(input.needsDisplay(), 1);
}

/// @brief Simple test to validate the formula for calculating the correct InputAction works
TEST_F(TouchScreenInputTests, ValidateAreaCalculation) {
  // For simplicity given "button" areas are all in thirds of the screen size, set 300 x 300 and disable debounce
  input.setScreenResolution(300, 300);
  input.setDebounceHold(false);

  // Expect PRESS_LEFT callback for:
  // - top and bottom left
  // - centre of the right edge of the left third
  EXPECT_CALL(callback, onInputAction(InputAction::PRESS_LEFT)).Times(3);
  input.setTouch(0, 0);
  input.check();
  input.setTouch(0, 300);
  input.check();
  input.setTouch(100, 150);
  input.check();

  // Expect PRESS_RIGHT callback for:
  // - top and bottom right
  // - centre of the left edge of the right third
  EXPECT_CALL(callback, onInputAction(InputAction::PRESS_RIGHT)).Times(3);
  input.setTouch(300, 0);
  input.check();
  input.setTouch(300, 300);
  input.check();
  input.setTouch(200, 150);
  input.check();

  // Expect PRESS_UP for:
  // - centre of top
  // - third way down in the centre
  EXPECT_CALL(callback, onInputAction(InputAction::PRESS_UP)).Times(2);
  input.setTouch(150, 0);
  input.check();
  input.setTouch(150, 100);
  input.check();

  // Expect PRESS_DOWN for:
  // - centre of bottom
  // - two thirds the way down in the centre
  EXPECT_CALL(callback, onInputAction(InputAction::PRESS_DOWN)).Times(2);
  input.setTouch(150, 300);
  input.check();
  input.setTouch(150, 200);
  input.check();

  // Expect PRESS_CENTRE for:
  // - centre
  // - just inside edges of left/right/up/down
  EXPECT_CALL(callback, onInputAction(InputAction::PRESS_CENTRE)).Times(5);
  input.setTouch(150, 150);
  input.check();
  input.setTouch(150, 101);
  input.check();
  input.setTouch(150, 199);
  input.check();
  input.setTouch(101, 150);
  input.check();
  input.setTouch(199, 150);
  input.check();
}
