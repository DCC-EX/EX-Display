/*
 *  © 2025 Peter Cole
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

#include "test/mocks/MockColourDisplay.h"
#include <gtest/gtest.h>

using namespace testing;

/**
 * @brief
 * @details
 * Attributes are enclosed in backticks and must be before any text or colours.
 * Underline is `__`
 * Line is `--`
 * Always ticker is `~~`
 * Never ticker is `!~`
 * Colours are in web format `#FFFFFF` and can be anywhere in the text, must convert to 16bit also
 *
 * The row formatting method must support changing colours inline with text, so there must be a return to indicate if
 * it's end of the text, or if the text should continue with a different colour at the next column position.
 */
class DisplayFormattingTests : public Test {
protected:
  MockColourDisplay *display;

  void SetUp() override { display = new MockColourDisplay(); }

  void TearDown() override { delete display; }
};

/**
 * @brief Define a custom matcher for the RowAttributes struct
 */
MATCHER_P(ExpectedRowAttributes, expected, "") {
  return arg.isUnderlined == expected.isUnderlined && arg.isLine == expected.isLine &&
         arg.alwaysTicker == expected.alwaysTicker && arg.neverTicker == expected.neverTicker &&
         arg.textColour == expected.textColour;
}

/**
 * @brief Test row formatting using modifiers
 */
TEST_F(DisplayFormattingTests, TestRowFormatting) {
  // Set our expected attributes for the first test with no modifiers
  RowAttributes expectedAttributes = {false, false, false, false, 0xFFFF};

  // Test with no formatting
  EXPECT_CALL(*display, displayFormattedRow(Eq(0), Eq(0), ExpectedRowAttributes(expectedAttributes),
                                            StrEq("Row 0, no attributes"), Eq(false)))
      .Times(1);
  const char *row0 = "Row 0, no attributes";
  display->displayRow(0, row0);

  // Test for basic underlined text on row 0
  // Expect that displayFormattedRow is called once with these arguments
  // EXPECT_CALL(*display,
  //             displayFormattedRow(Truly([=](uint8_t row) { return row == 0; }),
  //                                 Truly([=](uint8_t column) { return column == 0; }),
  //                                 Truly([=](RowAttributes attributes) { return attributes.isUnderlined; }),
  //                                 StrEq("Underlined row 0"), Truly([=](bool append) { return append == false; })))
  //     .Times(1);
  // //
  // const char *row0underlined = "`__`Underlined row 0";
  // display->displayRow(0, row0underlined);
}