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

#include "ScreenManager.h"
#include <gtest/gtest.h>

using namespace testing;

class ScreenManagerTests : public Test {
protected:
  void SetUp() override {}

  void TearDown() override {}
};

/// @brief Create a ScreenManager
TEST_F(ScreenManagerTests, CreateScreenManager) {
  ScreenManager *screenManager = new ScreenManager();

  // Clean up
  delete screenManager;
}

/// @brief Create a list of Screens with ScreenManager
TEST_F(ScreenManagerTests, CreateScreenList) {
  ScreenManager *screenManager = new ScreenManager();

  // Add some screens
  screenManager->addScreen(0);
  screenManager->addScreen(8);
  screenManager->addScreen(2);

  // Validate screens are in the list
  Screen *screen = screenManager->getFirstScreen();
  EXPECT_EQ(screen->getId(), 0);
  screen = screen->getNext();
  EXPECT_EQ(screen->getId(), 8);
  screen = screen->getNext();
  EXPECT_EQ(screen->getId(), 2);
  EXPECT_EQ(screen->getNext(), nullptr);

  // Validate screens can be retrieved by ID
  EXPECT_EQ(screenManager->getScreenById(0)->getId(), 0);
  EXPECT_EQ(screenManager->getScreenById(8)->getId(), 8);
  EXPECT_EQ(screenManager->getScreenById(2)->getId(), 2);

  // Validate an unknown ID is nullptr
  EXPECT_EQ(screenManager->getScreenById(11), nullptr);

  // Clean up
  delete screenManager;
}
