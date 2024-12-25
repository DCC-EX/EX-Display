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

#include "InputManager.h"
#include "test/mocks/MockInput.h"
#include <gtest/gtest.h>

using namespace testing;

/// @brief Test harness for input interface tests
class InputManagerTests : public Test {
protected:
  void SetUp() override {}

  void TearDown() override {}
};

/// @brief Test to ensure the InputManager can be created
TEST_F(InputManagerTests, CreateInputManager) {
  // Ensure the instance can be created with no input configured
  InputManager *inputManager = new InputManager();

  EXPECT_NE(inputManager, nullptr);
  EXPECT_EQ(inputManager->getInput(), nullptr);

  // Clean up
  delete inputManager;
}

/// @brief Test to ensure an input can be set, retrieved, and started with the InputManager
TEST_F(InputManagerTests, CreateMockInput) {
  // Create MockInput and InputManager
  InputManager *inputManager = new InputManager();
  MockInput *input = new MockInput();

  // Validate InputManager has no input yet
  EXPECT_EQ(inputManager->getInput(), nullptr);

  // Set the input and validate it can be retrieved
  inputManager->setInput(input);
  EXPECT_NE(inputManager->getInput(), nullptr);

  // Expect the input's begin() method should be called once when starting
  EXPECT_CALL(*input, begin()).Times(1);

  // Start it
  inputManager->startInput();

  // Clean up - the destructor should delete the MockInput also
  delete inputManager;
}
