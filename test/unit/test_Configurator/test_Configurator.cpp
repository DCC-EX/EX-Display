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

/// @brief Ensure the Configurator can be created successfully
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

  // Validate the Controller is created
  EXPECT_NE(configurator.getController(), nullptr);

  // Validate the DisplayManager is created
  EXPECT_NE(configurator.getDisplayManager(), nullptr);

  // Verify all expectations were made
  testing::Mock::VerifyAndClearExpectations(&console);
  testing::Mock::VerifyAndClearExpectations(&commandStation);
}

/// @brief Ensure the Configurator is created with the provided log level set
TEST_F(ConfiguratorTests, SetLogLevel) {
  // Create two mock streams
  Stream console;
  Stream commandStation;

  // Create a Configurator using these and a log level of debug
  Configurator configurator(&console, &commandStation, LogLevel::LOG_DEBUG);

  // Validate logger is set to DEBUG
  Logger *logger = configurator.getLogger();
  EXPECT_EQ(logger->getLogLevel(), LogLevel::LOG_DEBUG);
}

/// @brief Ensure the Configurator is created and all attributes are as expected
TEST_F(ConfiguratorTests, TestInitialisation) {
  // Create two mock streams
  Stream console;
  Stream commandStation;

  // Create a Configurator using these
  Configurator *configurator = new Configurator(&console, &commandStation);

  // Initialise the Configurator and make sure we have all attributes
  configurator->initialise();

  EXPECT_EQ(configurator->getConsoleStream(), &console);
  EXPECT_EQ(configurator->getCommandStationStream(), &commandStation);
  EXPECT_EQ(configurator->getLogger()->getLogLevel(), LogLevel::LOG_WARN);
  EXPECT_NE(configurator->getDisplayManager(), nullptr);
  EXPECT_NE(configurator->getInputManager(), nullptr);
  EXPECT_NE(configurator->getScreenManager(), nullptr);
  EXPECT_NE(configurator->getController(), nullptr);

  // Clean up
  delete configurator;
}
