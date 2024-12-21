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

#include "Screen.h"
#include <gtest/gtest.h>

using namespace testing;

class ScreenTests : public Test {
protected:
  void SetUp() override {}

  void TearDown() override {}
};

/// @brief Create a ScreenRow and check all attributes are valid
TEST_F(ScreenTests, CreateScreenRow) {
  // Set row parameters
  uint8_t rowId = 3;
  const char *rowText = "This is row 3";

  // Create and validate
  ScreenRow *row = new ScreenRow(rowId);
  EXPECT_EQ(row->getId(), rowId);

  // Set text and validate
  row->setText(rowText);
  EXPECT_STREQ(row->getText(), rowText);

  // Validate next one doesn't exist
  EXPECT_EQ(row->getNext(), nullptr);

  // Clean up
  delete row;
}

/// @brief Create a Screen and check all attributes are valid
TEST_F(ScreenTests, CreateScreen) {
  // Set screen parameters
  uint8_t screenId = 0;

  // Create and validate
  Screen *screen = new Screen(screenId);
  EXPECT_EQ(screen->getId(), screenId);

  // Validate next screen and first row don't exist
  EXPECT_EQ(screen->getNext(), nullptr);
  EXPECT_EQ(screen->getFirstScreenRow(), nullptr);

  // Clean up
  delete screen;
}

/// @brief Create a screen with associated row list and ensure rows are accessible by ID
TEST_F(ScreenTests, RowAccessibleById) {
  // Create screen and add rows
  Screen *screen = new Screen(0);
  screen->updateScreenRow(0, "Row 0");
  screen->updateScreenRow(2, "Row 2");
  screen->updateScreenRow(40, "Row 40");

  // Validate all are accessible by ID
  EXPECT_EQ(screen->getScreenRowById(0)->getId(), 0);
  EXPECT_STREQ(screen->getScreenRowById(2)->getText(), "Row 2");
  EXPECT_EQ(screen->getScreenRowById(40)->getNext(), nullptr);

  // Validate an unknown ID is a nullptr
  EXPECT_EQ(screen->getScreenRowById(1), nullptr);

  // Clean up
  delete screen;
}

/// @brief Create a screen with associated row list and check all attributes are valid
TEST_F(ScreenTests, CreateScreenRowList) {
  // Create a screen and add some rows
  Screen *screen = new Screen(0);
  screen->updateScreenRow(0, "Row 0");
  screen->updateScreenRow(3, "Row 3");
  screen->updateScreenRow(8, "Row 8");
  screen->updateScreenRow(2, "Row 2");

  // Validate the first row is set
  EXPECT_EQ(screen->getFirstScreenRow()->getId(), 0);
  EXPECT_STREQ(screen->getFirstScreenRow()->getText(), "Row 0");

  // Validate the list
  ScreenRow *row = screen->getFirstScreenRow();
  EXPECT_EQ(row->getId(), 0);
  EXPECT_EQ(row->getNext()->getId(), 3);
  row = row->getNext();
  EXPECT_EQ(row->getNext()->getId(), 8);
  row = row->getNext();
  EXPECT_EQ(row->getNext()->getId(), 2);
  row = row->getNext();
  EXPECT_EQ(row->getNext(), nullptr);

  // Clean up
  delete screen;
}

/// @brief Validate rows are deleted when setting text to ""
TEST_F(ScreenTests, DeleteScreenRow) {
  // Create a screen and add some rows
  Screen *screen = new Screen(0);
  screen->updateScreenRow(0, "Row 0");
  screen->updateScreenRow(3, "Row 3");
  screen->updateScreenRow(8, "Row 8");
  screen->updateScreenRow(2, "Row 2");
  screen->updateScreenRow(21, "Row 21");

  // Delete a row and make sure it's gone
  screen->updateScreenRow(8, "");
  EXPECT_EQ(screen->getScreenRowById(8), nullptr);

  // Ensure the list of rows is updated
  ScreenRow *row = screen->getFirstScreenRow();
  EXPECT_EQ(row->getId(), 0);
  EXPECT_EQ(row->getNext()->getId(), 3);
  row = row->getNext();
  EXPECT_EQ(row->getNext()->getId(), 2);
  row = row->getNext();
  EXPECT_EQ(row->getNext()->getId(), 21);
  row = row->getNext();
  EXPECT_EQ(row->getNext(), nullptr);

  // Ensure deleting the last in the list works
  screen->updateScreenRow(21, "");
  EXPECT_EQ(screen->getScreenRowById(21), nullptr);
  EXPECT_EQ(screen->getScreenRowById(2)->getNext(), nullptr);

  // Ensure deleting the first in list works
  screen->updateScreenRow(0, "");
  EXPECT_EQ(screen->getScreenRowById(0), nullptr);
  EXPECT_EQ(screen->getFirstScreenRow()->getId(), 3);
  EXPECT_EQ(screen->getFirstScreenRow()->getNext()->getId(), 2);

  // Clean up
  delete screen;
}
