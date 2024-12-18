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
#include <gtest/gtest.h>

using namespace testing;

class LoggerTests : public Test {
protected:
  Stream stream;
  Logger *logger;

  // Optional setup method
  void SetUp() override {
    // Initialize any test resources
    logger = new Logger(&stream);
    stream.clear();
  }

  // Optional teardown method
  void TearDown() override {
    // Clean up test resources
    delete logger;
  }
};

TEST_F(LoggerTests, SetLogLevel) {
  // Check the default level is warn
  EXPECT_EQ(logger->getLogLevel(), LogLevel::WARN);

  // Set debug and validate
  logger->setLogLevel(LogLevel::DEBUG);
  EXPECT_EQ(logger->getLogLevel(), LogLevel::DEBUG);
}

TEST_F(LoggerTests, LogErrorMessage) {
  // Setup a dummy error code and message
  const char *errorMessage = "Unknown error";
  int errorNumber = 2;
  // Log this as an error
  logger->log(LogLevel::ERROR, "Encountered an error: %d - %s", errorNumber, errorMessage);

  // Construct expected output
  std::string expectedOutput = "[ERROR] Encountered an error: 2 - Unknown error\r\n";

  // Check the buffer to see if it contains this
  EXPECT_EQ(stream.buffer, expectedOutput);
}

TEST_F(LoggerTests, LogLevels) {
  // Setup some dummy messages
  const char *errorMessage = "This is an error";
  const char *debugMessage = "This is a debug message";

  // Expect no output for a debug message with default warning, then output at debug level
  logger->log(LogLevel::DEBUG, debugMessage);
  EXPECT_EQ(stream.buffer, "");
  stream.clear();
  logger->setLogLevel(LogLevel::DEBUG);
  logger->log(LogLevel::DEBUG, debugMessage);
  EXPECT_EQ(stream.buffer, "[DEBUG] This is a debug message\r\n");
  stream.clear();

  // Should not get the debug message at info, but we should get error
  logger->setLogLevel(LogLevel::INFO);
  logger->log(LogLevel::DEBUG, debugMessage);
  EXPECT_EQ(stream.buffer, "");
  stream.clear();
  logger->log(LogLevel::ERROR, errorMessage);
  EXPECT_EQ(stream.buffer, "[ERROR] This is an error\r\n");
  stream.clear();

  // We should not get an error message with log level none
  logger->setLogLevel(LogLevel::NONE);
  logger->log(LogLevel::ERROR, errorMessage);
  EXPECT_EQ(stream.buffer, "");
}

TEST_F(LoggerTests, TestMacroWithNullptr) {
  // Make sure this compiles when _logger is nullptr
  Logger *_logger = nullptr;

  // Error default level, so this would normally log
  LOG(LogLevel::ERROR, "Test message");

  // Clean up
  delete _logger;

  // If it compiled and run, success
  SUCCEED();
}

TEST_F(LoggerTests, TestMacro) {
  // Setup a dummy error code and message
  const char *errorMessage = "Unknown error";
  int errorNumber = 2;

  // Setup _logger
  Logger *_logger = new Logger(&stream);

  // Log this as an error
  LOG(LogLevel::ERROR, "Encountered an error: %d - %s", errorNumber, errorMessage);

  // Construct expected output
  std::string expectedOutput = "[ERROR] Encountered an error: 2 - Unknown error\r\n";

  // Check the buffer to see if it contains this
  EXPECT_EQ(stream.buffer, expectedOutput);
  stream.clear();

  // Now log as info, which shouldn't log
  LOG(LogLevel::INFO, "Encountered an error: %d - %s", errorNumber, errorMessage);
  EXPECT_EQ(stream.buffer, "");

  // Clean up
  delete _logger;
}
