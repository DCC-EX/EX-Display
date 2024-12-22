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
#include "test/mocks/MockInput.h"
#include <gtest/gtest.h>

using namespace testing;

/// @brief Test harness for physical input interface tests
class InputInterfaceTests : public Test {
protected:
  MockInput input;
  MockCallback callback;

  void SetUp() override {
    input.setCallback(&callback);
  }

  void TearDown() override {}
};

TEST_F(InputInterfaceTests, TestInputMethods) {
  // Expect check() to be called once
  EXPECT_CALL(input, check())
      .WillOnce(Invoke([this]() {
        // Simulate a button press by calling the callback
        this->callback.onInputAction(InputAction::PRESS_UP);
      }));

  // Expect onInputAction to be called with PRESS_UP
  EXPECT_CALL(callback, onInputAction(InputAction::PRESS_UP))
      .Times(1);

  // Act
  input.check(); 
}
