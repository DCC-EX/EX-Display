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
#include "test/mocks/MockCallback.h"
#include <gtest/gtest.h>

using namespace testing;

class AtFinderTests : public Test {
protected:
  MockCallback callback;

  void SetUp() override {}

  void TearDown() override {}
};

TEST_F(AtFinderTests, TestCallback) {
  // We shouldn't receive any callbacks when setting up AtFinder
  EXPECT_CALL(callback, updateScreen(testing::_, testing::_, testing::_)).Times(0);
  AtFinder::setup(100, &callback);

  // Setup parameters to expect from the callback
  uint8_t expectScreenId = 0;
  uint8_t expectScreenRow = 3;
  const char *expectText = "Screen 0, row 3 text";
  EXPECT_CALL(callback, updateScreen(Truly([=](uint8_t screenId) { return screenId == expectScreenId; }),
                                     Truly([=](uint8_t row) { return row == expectScreenRow; }), StrEq(expectText)))
      .Times(1);
  const char *inputText = R"(<@ 0 3 "Screen 0, row 3 text")";
  for (size_t i = 0; i < strlen(inputText); i++) {
    AtFinder::processInputChar(inputText[i]);
  }

  // Verify all expectations were made
  testing::Mock::VerifyAndClearExpectations(&callback);

  // Clean up
  AtFinder::cleanUp();
}

TEST_F(AtFinderTests, TestInvalidCommands) {
  // We shouldn't recieve any callbacks when setting up AtFinder
  EXPECT_CALL(callback, updateScreen(testing::_, testing::_, testing::_)).Times(0);
  AtFinder::setup(100, &callback);

  // When sending a command without <@ at the front, we shouldn't callback
  EXPECT_CALL(callback, updateScreen(testing::_, testing::_, testing::_)).Times(0);
  const char *invalidInput1 = R"(<0 3 "Screen 0, row 3 text")";
  for (size_t i = 0; i < strlen(invalidInput1); i++) {
    AtFinder::processInputChar(invalidInput1[i]);
  }

  // When sending a command with an extra parameter, we shouldn't callback
  EXPECT_CALL(callback, updateScreen(testing::_, testing::_, testing::_)).Times(0);
  const char *invalidInput2 = R"(<@ 0 3 77 "Screen 0, row 3 text")";
  for (size_t i = 0; i < strlen(invalidInput2); i++) {
    AtFinder::processInputChar(invalidInput2[i]);
  }

  // When sending a command without < at the front, we shouldn't callback
  EXPECT_CALL(callback, updateScreen(testing::_, testing::_, testing::_)).Times(0);
  const char *invalidInput3 = R"(@ 0 3 "Screen 0, row 3 text")";
  for (size_t i = 0; i < strlen(invalidInput3); i++) {
    AtFinder::processInputChar(invalidInput3[i]);
  }

  // Verify all expectations were made
  testing::Mock::VerifyAndClearExpectations(&callback);

  // Clean up
  AtFinder::cleanUp();
}
