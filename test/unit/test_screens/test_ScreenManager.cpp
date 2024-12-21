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

  // Add some screens and validate max screen ID
  Screen *screen0 = screenManager->updateScreen(0);
  EXPECT_EQ(screenManager->getMaxScreenId(), 0);
  Screen *screen8 = screenManager->updateScreen(8);
  EXPECT_EQ(screenManager->getMaxScreenId(), 8);
  Screen *screen2 = screenManager->updateScreen(2);
  EXPECT_EQ(screenManager->getMaxScreenId(), 8);

  // Validate screens are as expected
  EXPECT_EQ(screen0->getId(), 0);
  EXPECT_EQ(screen8->getId(), 8);
  EXPECT_EQ(screen2->getId(), 2);

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

/// @brief Validate that previous screen is a lower ID, and next is a higher ID, wrapping around the list
TEST_F(ScreenManagerTests, NavigateScreens) {
  // Create a ScreenManager with some screens out of number order
  ScreenManager *screenManager = new ScreenManager;
  Screen *screen1 = screenManager->updateScreen(1);
  Screen *screen5 = screenManager->updateScreen(5);
  Screen *screen35 = screenManager->updateScreen(35);
  Screen *screen8 = screenManager->updateScreen(8);
  Screen *screen3 = screenManager->updateScreen(3);
  Screen *screen42 = screenManager->updateScreen(42);
  Screen *screen2 = screenManager->updateScreen(2);

  // Check a couple to ensure list order is as expected
  EXPECT_EQ(screen1->getNext(), screen5);
  EXPECT_EQ(screen35->getNext(), screen8);
  EXPECT_EQ(screen3->getNext(), screen42);
  EXPECT_EQ(screen2->getNext(), nullptr);

  // Validate min/max
  EXPECT_EQ(screenManager->getMinScreenId(), 1);
  EXPECT_EQ(screenManager->getMaxScreenId(), 42);

  // Start with first screen
  Screen *currentScreen = screenManager->getFirstScreen();

  // Get previous two screens and validate
  currentScreen = screenManager->getPreviousScreen(currentScreen);
  EXPECT_EQ(currentScreen->getId(), 42);
  currentScreen = screenManager->getPreviousScreen(currentScreen);
  EXPECT_EQ(currentScreen->getId(), 35);

  // Make sure lowest screen returns highest as previous
  Screen *lowestScreen = screenManager->getScreenById(screenManager->getMinScreenId());
  EXPECT_EQ(screenManager->getPreviousScreen(lowestScreen)->getId(), 42);

  // Repeat for next instead of previous
  currentScreen = screenManager->getFirstScreen();

  currentScreen = screenManager->getNextScreen(currentScreen);
  EXPECT_EQ(currentScreen->getId(), 2);
  currentScreen = screenManager->getNextScreen(currentScreen);
  EXPECT_EQ(currentScreen->getId(), 3);

  // Make sure highest screen returns lowest as next
  Screen *highestScreen = screenManager->getScreenById(screenManager->getMaxScreenId());
  EXPECT_EQ(screenManager->getNextScreen(highestScreen)->getId(), 1);

  // Clean up
  delete screenManager;
}
