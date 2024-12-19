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

#ifndef CONSOLEINPUT_H
#define CONSOLEINPUT_H

#include "src/infrastructure/Logger/Logger.h"
#include <Arduino.h>

class ConsoleInput {
public:
  /// @brief Constructor for a ConsoleInput instance
  /// @param stream Pointer to a stream to accept input from (eg. ConsoleInput(&Serial))
  /// @param maxInputLength Maximum number of characters accepted for input (default 100)
  ConsoleInput(Stream *stream, uint8_t maxInputLength = 100);

  /// @brief Process Stream for user input
  void check();

  /// @brief Set the logger instance to use for diagnostic logging
  /// @param logger Pointer to the Logger instance to use
  void setLogger(Logger *logger);

  /// @brief Destructor for a ConsoleInput instance
  ~ConsoleInput();

private:
  Stream *_stream;
  uint8_t _maxInputLength;
  Logger *_logger;
  char *_inputBuffer;
  uint8_t _inputIndex;

  /// @brief Process the command currently in _inputBuffer
  /// @param command Char array containing the command to process
  void _processCommand(const char *command);
};

#endif // CONSOLEINPUT_H
