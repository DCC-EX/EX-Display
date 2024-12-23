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

#include "AtFinder.h"
#include "Controller.h"
#include "DisplayManager.h"
#include "ScreenManager.h"
#include "test/mocks/MockCallback.h"
#include "test/mocks/Stream.h"
#include <gtest/gtest.h>

using namespace testing;

class ControllerTests : public Test {
protected:
  Stream console;
  Stream commandStation;
  DisplayManager displayManager;
  ScreenManager screenManager;

  void SetUp() override {}

  void TearDown() override {}
};

/// @brief Create a Controller and check all attributes are valid
TEST_F(ControllerTests, CreateController) {
  // Create Controller with mock streams
  Controller *controller = new Controller(&console, &commandStation, &displayManager, &screenManager, nullptr);

  // Make sure it is created
  EXPECT_NE(controller, nullptr);

  // Clean up
  delete controller;
}

/// @brief Ensure update() method correctly calls the mock callback
TEST_F(ControllerTests, TestUpdate) {
  // Setup AtFinder first
  MockCallback callback;
  AtFinder::setup(100, &callback);

  // Create controller with mock streams
  Controller *controller = new Controller(&console, &commandStation, &displayManager, &screenManager, nullptr);

  // Setup expected console results
  uint8_t expectScreenId = 0;
  uint8_t expectScreenRow = 3;
  const char *expectConsoleText = "Screen 0, row 3 text";

  // Set up expectation for sending to the console
  EXPECT_CALL(callback,
              updateScreen(Truly([=](uint8_t screenId) { return screenId == expectScreenId; }),
                           Truly([=](uint8_t row) { return row == expectScreenRow; }), StrEq(expectConsoleText)))
      .Times(1);

  // Send to console stream
  const char *sendConsole = R"(<@ 0 3 "Screen 0, row 3 text")";
  console.buffer = sendConsole;
  for (size_t i = 0; i < strlen(sendConsole); i++) {
    controller->update();
  }

  // Setup expected CommandStation results
  expectScreenId = 2;
  expectScreenRow = 21;
  const char *expectCommandStationText = "Screen 2, row 21 text";

  // Set up expectation for sending to the CommandStation
  EXPECT_CALL(callback,
              updateScreen(Truly([=](uint8_t screenId) { return screenId == expectScreenId; }),
                           Truly([=](uint8_t row) { return row == expectScreenRow; }), StrEq(expectCommandStationText)))
      .Times(1);

  // Send to CommandStation stream
  const char *sendCommandStation = R"(<@ 2 21 "Screen 2, row 21 text")";
  console.buffer = sendCommandStation;
  for (size_t i = 0; i < strlen(sendCommandStation); i++) {
    controller->update();
  }

  // Clean up
  delete controller;
  AtFinder::cleanUp();
}

/// @brief Ensure update() method correctly ignores an invalid stream input
TEST_F(ControllerTests, TestInvalidUpdate) {
  // Setup AtFinder first
  MockCallback callback;
  AtFinder::setup(100, &callback);

  // Create controller with mock streams
  Controller *controller = new Controller(&console, &commandStation, &displayManager, &screenManager, nullptr);

  // Set up expectation for sending to the console
  EXPECT_CALL(callback, updateScreen(testing::_, testing::_, testing::_)).Times(0);

  // Send to console stream
  const char *sendConsole = R"(<0 3 "Screen 0, row 3 text")";
  console.buffer = sendConsole;
  for (size_t i = 0; i < strlen(sendConsole); i++) {
    controller->update();
  }

  // Set up expectation for sending to the CommandStation
  EXPECT_CALL(callback, updateScreen(testing::_, testing::_, testing::_)).Times(0);

  // Send to CommandStation stream
  const char *sendCommandStation = R"(@ 2 21 "Screen 2, row 21 text")";
  console.buffer = sendCommandStation;
  for (size_t i = 0; i < strlen(sendCommandStation); i++) {
    controller->update();
  }

  // Clean up
  delete controller;
  AtFinder::cleanUp();
}
