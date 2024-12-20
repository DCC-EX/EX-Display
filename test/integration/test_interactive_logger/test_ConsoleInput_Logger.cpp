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

#include "ConsoleInput.h"
#include "Logger.h"
#include "test/mocks/Stream.h"
#include <gtest/gtest.h>

using namespace testing;

/// @brief Test harness integration testing of ConsoleInput and Logger classes
/// Note that the mock Stream class cannot cope with input/output to the same stream, hence separate streams for these
/// purposes
class ConsoleInputLoggerIntegrationTests : public Test {
protected:
  Stream inputStream;
  Stream outputStream;
  Logger *logger;
  ConsoleInput *input;

  void SetUp() override {
    logger = new Logger(&outputStream);
    input = new ConsoleInput(&inputStream);
    input->setLogger(logger);
    inputStream.clear();
    outputStream.clear();
  }

  void TearDown() override {
    delete input;
    delete logger;
  }
};

/// @brief Basic test to ensure debug output can be logged
TEST_F(ConsoleInputLoggerIntegrationTests, IntegrationTest) {
  // Define a valid test command and send to the stream buffer
  const char *testCommand = "[test command]";
  inputStream.buffer = testCommand;

  // Set debug level for this test
  logger->setLogLevel(LogLevel::DEBUG);

  // Check for input
  input->check();

  // Expect DEBUG output
  EXPECT_THAT(outputStream.buffer, testing::HasSubstr("[DEBUG] ConsoleInput::_processCommand: [test command]\r\n"));
}

/// @brief Ensure log level can be set via interactive command [L <level>]
TEST_F(ConsoleInputLoggerIntegrationTests, InteractiveSetLogLevel) {
  // Define the command to set log levels
  const char *setNone = "[L NONE]";
  const char *setError = "[L ERROR]";
  const char *setWarn = "[L WARN]";
  const char *setInfo = "[L INFO]";
  const char *setDebug = "[L DEBUG]";

  // Validate default is warning
  EXPECT_EQ(logger->getLogLevel(), LogLevel::WARN);

  // Set to none
  inputStream.buffer = setNone;
  input->check();
  EXPECT_EQ(logger->getLogLevel(), LogLevel::NONE);

  // Set to error
  inputStream.buffer = setError;
  input->check();
  EXPECT_EQ(logger->getLogLevel(), LogLevel::ERROR);

  // Set to warn
  inputStream.buffer = setWarn;
  input->check();
  EXPECT_EQ(logger->getLogLevel(), LogLevel::WARN);

  // Set to info
  inputStream.buffer = setInfo;
  input->check();
  EXPECT_EQ(logger->getLogLevel(), LogLevel::INFO);

  // Set to debug
  inputStream.buffer = setDebug;
  input->check();
  EXPECT_EQ(logger->getLogLevel(), LogLevel::DEBUG);
}
