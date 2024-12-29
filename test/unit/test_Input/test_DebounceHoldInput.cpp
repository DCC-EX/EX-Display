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

#include "test/mocks/MockButtonInput.h"
#include "test/mocks/MockCallback.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace testing;

/// @brief Test harness for inputs utilising debounce and hold options
class DebounceHoldInputTests : public Test {
protected:
  MockButtonInput input;
  MockCallback callback;

  void SetUp() override {
    millis(); // Must call this to force time to be initialised
    input.setCallback(&callback);
  }

  void TearDown() override {}
};

/// @brief Test case for a single press with no time advance
TEST_F(DebounceHoldInputTests, TestSingleInputAction) {
  // For a single press we should get no callback
  EXPECT_CALL(callback, onInputAction(::testing::_)).Times(0);

  // Set a press up
  input.setRawAction(InputAction::PRESS_UP);

  // Call check
  input.check();

  // Verify all expectations were made
  testing::Mock::VerifyAndClearExpectations(&callback);
}

/// @brief Test case for a press that should be debounced
TEST_F(DebounceHoldInputTests, TestDebouncedAction) {
  // For a single press we should get no callback
  EXPECT_CALL(callback, onInputAction(::testing::_)).Times(0);

  // Set a press up and check
  input.setRawAction(InputAction::PRESS_UP);
  input.check();

  // Advance time but before debounce delay
  advanceMillis(40);

  // Should still expect no callback when checked
  EXPECT_CALL(callback, onInputAction(::testing::_)).Times(0);
  input.check();

  // Advance time now beyond debounce delay
  advanceMillis(20);

  // Should still not receive a call while our input hasn't changed
  EXPECT_CALL(callback, onInputAction(::testing::_)).Times(0);
  input.check();

  // Expect a single callback when the input released
  EXPECT_CALL(callback, onInputAction(InputAction::PRESS_UP)).Times(1);
  input.setRawAction(InputAction::PRESS_NONE);
  input.check();

  // Expect no more callbacks after button let go
  EXPECT_CALL(callback, onInputAction(::testing::_)).Times(0);
  input.check();

  // Check again after the hold threshold
  advanceMillis(600);

  // Expect no callbacks
  EXPECT_CALL(callback, onInputAction(::testing::_)).Times(0);
  input.check();

  // Verify all expectations were made
  testing::Mock::VerifyAndClearExpectations(&callback);
}

/// @brief Test case for a button hold
TEST_F(DebounceHoldInputTests, TestHoldAction) {
  // For a single press we should get no callback
  EXPECT_CALL(callback, onInputAction(::testing::_)).Times(0);

  // Set a press left and check
  input.setRawAction(InputAction::PRESS_LEFT);
  input.check();

  // Advance time but before debounce delay
  advanceMillis(40);

  // Should still expect no callback
  EXPECT_CALL(callback, onInputAction(::testing::_)).Times(0);

  // Call check
  input.check();

  // Advance time now beyond debounce delay
  advanceMillis(20);

  // We still shouldn't get a callback for a press when still being held
  EXPECT_CALL(callback, onInputAction(::testing::_)).Times(0);

  // Check again
  input.check();

  // Advance time now beyond hold threshold
  advanceMillis(500);

  // Expect a single callback this time
  EXPECT_CALL(callback, onInputAction(InputAction::HOLD_LEFT)).Times(1);

  // Check it
  input.check();

  // Verify all expectations were made
  testing::Mock::VerifyAndClearExpectations(&callback);
}

/// @brief Test to validate debounce correctly ignores bouncy inputs
TEST_F(DebounceHoldInputTests, TestBouncyInput) {
  // Expect no callback to start
  EXPECT_CALL(callback, onInputAction(::testing::_)).Times(0);

  // Centre press
  input.setRawAction(InputAction::PRESS_CENTRE);
  input.check();

  // Advance clock within debounce time
  advanceMillis(20);

  // Expect no callback when simulated bounce sets to none and back to centre
  EXPECT_CALL(callback, onInputAction(::testing::_)).Times(0);

  input.setRawAction(InputAction::PRESS_NONE);
  input.check();

  // Simulate more bounces while advancing time and expect no callbacks
  EXPECT_CALL(callback, onInputAction(::testing::_)).Times(0);

  advanceMillis(20);
  input.setRawAction(InputAction::PRESS_CENTRE);
  input.check();

  EXPECT_CALL(callback, onInputAction(::testing::_)).Times(0);

  advanceMillis(20);
  input.setRawAction(InputAction::PRESS_NONE);
  input.check();

  EXPECT_CALL(callback, onInputAction(::testing::_)).Times(0);

  advanceMillis(20);
  input.setRawAction(InputAction::PRESS_CENTRE);
  input.check();

  EXPECT_CALL(callback, onInputAction(::testing::_)).Times(0);

  advanceMillis(20);
  input.setRawAction(InputAction::PRESS_NONE);
  input.check();

  EXPECT_CALL(callback, onInputAction(::testing::_)).Times(0);

  advanceMillis(20);
  input.setRawAction(InputAction::PRESS_CENTRE);
  input.check();

  // We should finally get a single callback when debounced and released after debounce delay
  EXPECT_CALL(callback, onInputAction(InputAction::PRESS_CENTRE)).Times(1);

  advanceMillis(60);
  input.setRawAction(InputAction::PRESS_NONE);
  input.check();

  // Verify all expectations were made
  testing::Mock::VerifyAndClearExpectations(&callback);
}
