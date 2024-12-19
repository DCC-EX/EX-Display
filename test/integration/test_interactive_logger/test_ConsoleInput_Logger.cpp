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

#include "infrastructure/Logger/Logger.h"
#include "mocks/Stream.h"
#include "user_interaction/ConsoleInput/ConsoleInput.h"
#include <gtest/gtest.h>

using namespace testing;

/// @brief Test harness integration testing of ConsoleInput and Logger classes
class ConsoleInputLoggerIntegrationTests : public Test {
protected:
  Stream stream;
  Logger *logger;
  ConsoleInput *input;

  void SetUp() override {
    logger = new Logger(&stream);
    input = new ConsoleInput(&stream);
    input->setLogger(logger);
    stream.clear();
  }

  void TearDown() override {
    delete input;
    delete logger;
  }
};

TEST_F(ConsoleInputLoggerIntegrationTests, IntegrationTest) {
  // Define a valid test command and send to the stream buffer
  const char *testCommand = "<test command>";
  stream.buffer = testCommand;

  // Check for input
  input->check();

  // Expect ERROR output
  EXPECT_THAT(stream.buffer, testing::HasSubstr("[ERROR] ConsoleInput::_processCommand: <test command>\r\n"));
}
