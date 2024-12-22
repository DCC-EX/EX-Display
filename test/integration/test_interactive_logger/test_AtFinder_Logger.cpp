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
#include "Logger.h"
#include "test/mocks/MockCallback.h"
#include "test/mocks/Stream.h"
#include <gtest/gtest.h>

using namespace testing;

/// @brief Test harness integration testing of ConsoleInput and Logger classes
class AtFinderLoggerIntegrationTests : public Test {
protected:
  Stream stream;
  Logger *logger;
  MockCallback callback;

  void SetUp() override {
    logger = new Logger(&stream);
    stream.clear();
  }

  void TearDown() override { delete logger; }
};

TEST_F(AtFinderLoggerIntegrationTests, IntegrationTest) {
  // Set logging to debug
  logger->setLogLevel(LogLevel::DEBUG);

  // Set AtFinder logger
  AtFinder::setLogger(logger);

  // Setup AtFinder
  AtFinder::setup(100, &callback);

  EXPECT_THAT(stream.buffer, testing::HasSubstr("[DEBUG] AtFinder::setup with _maxTextLength 100\r\n"));

  // Clean up
  AtFinder::cleanUp();
}
