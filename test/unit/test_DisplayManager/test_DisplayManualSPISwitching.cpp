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

#include "DisplayManager.h"
#include "Version.h"
#include "test/mocks/MockSPIDisplay.h"
#include <gtest/gtest.h>

using namespace testing;

/// @brief Test harness for testing DisplayManager
class DisplayManualSPISwitchingTests : public Test {
protected:
  void SetUp() override {}

  void TearDown() override {}
};

/// @brief Test that SPI displays can be switched manually if their library doesn't support it (eg. TFT_eSPI)
TEST_F(DisplayManualSPISwitchingTests, TestSPISwitching) {
  // Create DisplayManager with 3 mock SPI displays, two of which need manual switching
  DisplayManager *displayManager = new DisplayManager();
  MockSPIDisplay *display0 = new MockSPIDisplay(22); // SPI CS connected to mock pin 22
  MockSPIDisplay *display1 = new MockSPIDisplay(23); // SPI CS connected to mock pin 23
  MockSPIDisplay *display2 = new MockSPIDisplay();   // No CS pin specified, no manual switching
  displayManager->addDisplay(display0);
  displayManager->addDisplay(display1);
  displayManager->addDisplay(display2);

  // Expect our CS pins to be set correctly
  EXPECT_EQ(display0->getCSPin(), 22);
  EXPECT_EQ(display1->getCSPin(), 23);
  EXPECT_EQ(display2->getCSPin(), -1);

  // Set the current version
  const char *version = VERSION;

  // Mock displayStartupInfo() should be called for each display
  EXPECT_CALL(*display0, displayStartupInfo(version)).Times(1);
  EXPECT_CALL(*display1, displayStartupInfo(version)).Times(1);
  EXPECT_CALL(*display2, displayStartupInfo(version)).Times(1);

  // Expect that:
  // - digitalWrite(22, LOW) called once - display0 CS pin enabled
  // - digitalWrite(22, HIGH) called once - display0 CS pin disabled
  // - digitalWrite(23, LOW) called once - display1 CS pin enabled
  // - digitalWrite(23, HIGH) called once - display1 CS pin disabled
  // - Should be no more digitalWrite calls after those
  EXPECT_CALL(MockArduino::getInstance(), mockDigitalWrite(22, LOW)).Times(1);
  EXPECT_CALL(MockArduino::getInstance(), mockDigitalWrite(22, HIGH)).Times(1);
  EXPECT_CALL(MockArduino::getInstance(), mockDigitalWrite(23, LOW)).Times(1);
  EXPECT_CALL(MockArduino::getInstance(), mockDigitalWrite(23, HIGH)).Times(1);
  EXPECT_CALL(MockArduino::getInstance(), mockDigitalWrite(-1, ::testing::_)).Times(0);

  // Call displayStartupInfo which should switch the CS pins for displays 0 and 1 on and off, and do nothing for 2
  displayManager->displayStartupInfo(version);

  // Verify all expectations were made
  testing::Mock::VerifyAndClearExpectations(display0);
  testing::Mock::VerifyAndClearExpectations(display1);
  testing::Mock::VerifyAndClearExpectations(display2);

  // Clean up
  delete displayManager;
}
