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

#include "ConsoleInput.h"
#include "test/mocks/Stream.h"
#include <gtest/gtest.h>

using namespace testing;

class ConsoleInputTests : public Test {
protected:
  Stream stream;
  ConsoleInput *console;

  void SetUp() override {
    // Initialise test objects
    console = new ConsoleInput(&stream);
    stream.clear();
  }

  void TearDown() override {
    // Cleanup
    delete console;
  }
};

TEST_F(ConsoleInputTests, TestInput) {
  //
}