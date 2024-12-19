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
#include "CallbackInterface.h"
#include "Logger.h"
#include <Arduino.h>

/// @brief Class to monitor input stream for EXRAIL SCREEN commands
/// Format: <@ screen row "Text">
class AtFinder {
public:
  /// @brief Setup the AtFinder parser
  /// @param _maxTextLength Maximum length of text the parser will accept
  /// @param _callback Parser will call this function and provide display ID, row number, and a char array of text
  static void setup(uint8_t maxTextLength, CallbackInterface *callback);

  /// @brief Call this as often as possible with a streaming input (eg. Serial.read())
  /// @param hot The next character to process in the stream
  static void processInputChar(char hot);

  /// @brief Clean up memory allocations used by AtFinder
  static void cleanUp();

  /// @brief Set the logger instance to use for diagnostic logging
  /// @param logger Pointer to the Logger instance to use
  static void setLogger(Logger *logger);

private:
  static uint8_t _maxTextLength;
  static char *_text;
  static CallbackInterface *_callback;
  static Logger *_logger;
};
#endif