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
#include "test/mocks/MockDisplay.h"
#include "test/mocks/Stream.h"
#include <gtest/gtest.h>

using namespace testing;

/// @brief Test harness for ensuring displays are updated when screen updates are received
class ControllerDisplayUpdateTests : public Test {
protected:
  Stream console;
  Stream commandStation;
  DisplayManager displayManager;
  ScreenManager screenManager;
  Controller *controller = new Controller(&console, &commandStation, &displayManager, nullptr, &screenManager, nullptr);

  void SetUp() override {}

  void TearDown() override { delete controller; }
};

/// @brief Test to ensure a mock display correctly receives screen updates from the Controller
TEST_F(ControllerDisplayUpdateTests, OneScreenOneDisplay) {
  // Set up some screen commands to send and validate via the mock display
  const char *screen0row0 = R"(<@ 0 0 "Screen 0 row 0")";
  const char *screen0row2 = R"(<@ 0 2 "Screen 0 row 2")";
  const char *screen0row5 = R"(<@ 0 5 "Screen 0 row 5")";

  // Set up our mock display
  MockDisplay *display0 = new MockDisplay();
  displayManager.addDisplay(display0);

  // Validate the display is set with the correct ID
  EXPECT_EQ(displayManager.getFirstDisplay()->getId(), 0);

  // Set up AtFinder
  AtFinder::setup(100, controller);

  // Validate screen 0 row 0 updates
  commandStation.buffer = screen0row0;

  // Ensure the buffer contains it as expected
  EXPECT_THAT(commandStation.buffer, testing::HasSubstr(screen0row0));

  // We should always get a clearScreen() first when a display needs redrawing
  EXPECT_CALL(*display0, clearScreen()).Times(1);
  // Set up expectation that our display will have displayRow(uint8_t row, const char *text, bool underlined, uint8_t
  // column) called once for each row
  EXPECT_CALL(*display0, displayRow(Truly([=](uint8_t row) { return row == 0; }), StrEq("Screen 0 row 0"),
                                    Truly([=](bool underlined) { return underlined == false; }),
                                    Truly([=](uint8_t column) { return column == 0; })))
      .Times(1);

  for (size_t i = 0; i < strlen(screen0row0); i++) {
    controller->update();
  }

  // Validate screen 0 now exists and is the first one
  Screen *screen0 = screenManager.getScreenById(0);
  EXPECT_NE(screen0, nullptr);
  EXPECT_EQ(screenManager.getFirstScreen(), screen0);

  // Validate screen 0 row 2 updates
  commandStation.buffer = screen0row2;

  // Ensure the buffer contains it as expected
  EXPECT_THAT(commandStation.buffer, testing::HasSubstr(screen0row2));

  // Set up expectation that our display will have displayRow(uint8_t row, const char *text, bool underlined, uint8_t
  // column) called once for each row
  EXPECT_CALL(*display0, displayRow(Truly([=](uint8_t row) { return row == 2; }), StrEq("Screen 0 row 2"),
                                    Truly([=](bool underlined) { return underlined == false; }),
                                    Truly([=](uint8_t column) { return column == 0; })))
      .Times(1);

  for (size_t i = 0; i < strlen(screen0row2); i++) {
    controller->update();
  }

  // Validate screen 0 row 5 updates
  commandStation.buffer = screen0row5;

  // Ensure the buffer contains it as expected
  EXPECT_THAT(commandStation.buffer, testing::HasSubstr(screen0row5));

  // Set up expectation that our display will have displayRow(uint8_t row, const char *text, bool underlined, uint8_t
  // column) called once for each row
  EXPECT_CALL(*display0, displayRow(Truly([=](uint8_t row) { return row == 5; }), StrEq("Screen 0 row 5"),
                                    Truly([=](bool underlined) { return underlined == false; }),
                                    Truly([=](uint8_t column) { return column == 0; })))
      .Times(1);

  for (size_t i = 0; i < strlen(screen0row5); i++) {
    controller->update();
  }

  // Validate there are now three rows in screen 0 with the correct attributes
  ScreenRow *row = screenManager.getFirstScreen()->getFirstScreenRow();
  EXPECT_STREQ(row->getText(), "Screen 0 row 0");
  EXPECT_EQ(row->getNext()->getId(), 2);
  row = row->getNext();
  EXPECT_STREQ(row->getText(), "Screen 0 row 2");
  EXPECT_EQ(row->getNext()->getId(), 5);
  row = row->getNext();
  EXPECT_STREQ(row->getText(), "Screen 0 row 5");
  EXPECT_EQ(row->getNext(), nullptr);

  // Verify all expectations were made
  testing::Mock::VerifyAndClearExpectations(display0);

  // Clean up
  AtFinder::cleanUp();
}