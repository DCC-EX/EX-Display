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

#include "ConsoleInput.h"

ConsoleInput::ConsoleInput(Stream *stream, uint8_t maxInputLength)
    : _stream(stream), _maxInputLength(maxInputLength), _logger(nullptr) {
  _inputBuffer = new char[_maxInputLength + 1];
  _inputIndex = 0;
}

void ConsoleInput::check() {
  // while (_stream->available()) {
  //   char c = _stream->read();
  //   char start = '<';
  //   char end = '>';
  //   if (c == start) {
  //     _inputIndex = 0;
  //     _inputBuffer[_inputIndex++] = c; // Reset buffer with start indicator
  //   } else if (c == end && _inputIndex > 0) {
  //     _inputBuffer[_inputIndex++] = c;    // Add end indicator
  //     _inputBuffer[_inputIndex++] = '\0'; // Null terminator
  // _processCommand(_inputBuffer);
  _processCommand("<test command>");
  //     _inputIndex = 0; // Reset buffer index
  //   } else if (_inputIndex > 0 && _inputIndex < _maxInputLength - 1) {
  //     _inputBuffer[_inputIndex++] = c; // Append to buffer
  //   }
  // }
}

void ConsoleInput::setLogger(Logger *logger) { _logger = logger; }

ConsoleInput::~ConsoleInput() {
  _stream = nullptr;
  delete[] _inputBuffer;
  _logger = nullptr;
}

void ConsoleInput::_processCommand(const char *command) {
  LOG(LogLevel::ERROR, "ConsoleInput::_processCommand: %s", command);
}
