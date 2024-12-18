/*
 *  © 2024 Chris Harlow
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

#ifndef AtFinder_h
#define AtFinder_h
#include "src/interfaces/CallbackInterface.h"
#include <Arduino.h>

/// @brief
class AtFinder {
public:
  /// @brief Setup the AtFinder parser
  /// @param _maxTextLength Maximum length of text the parser will accept
  /// @param _callback Parser will call this function and provide display ID, row number, and a char array of text
  static void setup(uint8_t maxTextLength, CallbackInterface *callback);

  /// @brief Call this as often as possible with a streaming input (eg. Serial.read())
  /// @param hot The next character to process in the stream
  static void processInputChar(char hot);

private:
  static uint8_t _maxTextLength;
  static char *_text;
  static CallbackInterface *_callback;
};
#endif