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

#include "Controller.h"
#include "ScreenManager.h"
#include <gtest/gtest.h>

using namespace testing;

/// @brief Test harness for ensuring displays are updated when screen updates are received
class ControllerScreenCreation : public Test {
protected:
  Stream console;
  Stream commandStation;
  ScreenManager screenManager;
  Controller *controller = new Controller(&console, &commandStation, nullptr, nullptr, &screenManager, nullptr);

  void SetUp() override {}

  void TearDown() override { delete controller; }
};

/// @brief Validates that the Controller->updateScreen() method creates a screen and updates rows correctly
TEST_F(ControllerScreenCreation, CreateScreenRows) {
  // Create screens/rows via Controller::updateScreen(screen, row, text)
  controller->updateScreen(0, 0, "Screen 0 row 0");
  controller->updateScreen(0, 4, "Screen 0 row 4");
  controller->updateScreen(0, 20, "Screen 0 row 20");
  controller->updateScreen(20, 10, "Screen 20 row 10");
  controller->updateScreen(20, 30, "Screen 20 row 30");
  controller->updateScreen(20, 40, "Screen 20 row 40");

  // Validate the screen list is as expected
  EXPECT_EQ(screenManager.getFirstScreen()->getId(), 0);
  EXPECT_EQ(screenManager.getFirstScreen()->getNext()->getId(), 20);
  EXPECT_EQ(screenManager.getScreenById(20)->getNext(), nullptr);

  // Validate the rows are as expected
  Screen *screen0 = screenManager.getScreenById(0);
  EXPECT_EQ(screen0->getFirstScreenRow()->getId(), 0);
  EXPECT_STREQ(screen0->getFirstScreenRow()->getText(), "Screen 0 row 0");
  EXPECT_EQ(screen0->getFirstScreenRow()->getNext()->getId(), 4);
  EXPECT_STREQ(screen0->getScreenRowById(4)->getText(), "Screen 0 row 4");
  EXPECT_EQ(screen0->getScreenRowById(4)->getNext()->getId(), 20);
  EXPECT_STREQ(screen0->getScreenRowById(20)->getText(), "Screen 0 row 20");
  EXPECT_EQ(screen0->getScreenRowById(20)->getNext(), nullptr);

  Screen *screen20 = screenManager.getScreenById(20);
  EXPECT_EQ(screen20->getFirstScreenRow()->getId(), 10);
  EXPECT_STREQ(screen20->getFirstScreenRow()->getText(), "Screen 20 row 10");
  EXPECT_EQ(screen20->getFirstScreenRow()->getNext()->getId(), 30);
  EXPECT_STREQ(screen20->getScreenRowById(30)->getText(), "Screen 20 row 30");
  EXPECT_EQ(screen20->getScreenRowById(30)->getNext()->getId(), 40);
  EXPECT_STREQ(screen20->getScreenRowById(40)->getText(), "Screen 20 row 40");
  EXPECT_EQ(screen20->getScreenRowById(40)->getNext(), nullptr);
}