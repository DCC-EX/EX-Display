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

#include "Configurator.h"
#include "test/mocks/Stream.h"
#include <gtest/gtest.h>

using namespace testing;

class ConfiguratorTests : public Test {
protected:
  void SetUp() override {}

  void TearDown() override {}
};

/// @brief Create a ScreenRow and check all attributes are valid
TEST_F(ConfiguratorTests, CreateConfiguration) {
  // Create two mock streams
  Stream console;
  Stream commandStation;

  // Create a Configurator using these
  Configurator configurator(&console, &commandStation);

  // Validate the streams are set and Stream types
  Stream *consoleResult = configurator.getConsoleStream();
  EXPECT_NE(consoleResult, nullptr);
  EXPECT_NE(nullptr, dynamic_cast<Stream *>(consoleResult));

  Stream *commandStationResult = configurator.getCommandStationStream();
  EXPECT_NE(commandStationResult, nullptr);
  EXPECT_NE(nullptr, dynamic_cast<Stream *>(commandStationResult));
}

TEST_F(ConfiguratorTests, SetLogLevel) {
  // Create two mock streams
  Stream console;
  Stream commandStation;

  // Create a Configurator using these and a log level of debug
  Configurator configurator(&console, &commandStation, LogLevel::DEBUG);

  // Validate logger is set to DEBUG
  Logger *logger = configurator.getLogger();
  EXPECT_EQ(logger->getLogLevel(), LogLevel::DEBUG);
}
