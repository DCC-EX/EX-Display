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

#include "AtFinder.h"
#include <Arduino.h>

/* This is a finite state automation (FSA) to recognize a dccex output message
in the format <@ screenid screenrow "text">.

It is fed one character at a time and will rapidly ignore other inputs.
If the <@ operation is found, it will collect the id,row,text and
make a call to callback(id,row, text);


At any given time, the state is one of the enum values.
Within each state, the parsed character is either used as appropriate or ignored
and the state may or may not change to a different state.  */

uint8_t AtFinder::_maxTextLength = 0;
char *AtFinder::_text = nullptr;
CallbackInterface *AtFinder::_callback = nullptr;
Logger *AtFinder::_logger = nullptr;

// Set maximum accepted length of "text". Longer texts will be trimmed.
// Set callback function that will be called when message detected.

// Note: the code is safe if setup is not called before use because the
// code can not reach the text handling or callback states.
// If the sketch has no reference to the setup function at all,
// then compiler constant propagation is smart enough to realise
// that it can never reach the text handling states, and thus
// the entire function has no effect and is eliminated from the link.

void AtFinder::setup(uint8_t maxTextLength, CallbackInterface *callback) {
  _maxTextLength = maxTextLength;
  _text = (char *)malloc(_maxTextLength + 1);
  _callback = callback;
  LOG(LogLevel::DEBUG, "AtFinder::setup with _maxTextLength %d", _maxTextLength);
}

void AtFinder::processInputChar(char hot) {
  enum stateMachine : byte {
    FIND_START,     // looking for < character
    SET_OPCODE,     // waiting for opcode
    SKIP_SPACES1,   // skip spaces to screen id
    BUILD_SCREENID, // building screen Id
    SKIP_SPACES2,   // skip spaces to row
    BUILD_ROW,      // building screen row
    SKIP_SPACES3,   // skip spaces to "text"
    COPY_TEXT       // copying text to buffer
  };
  static stateMachine state = FIND_START;
  static uint8_t screenId;
  static uint8_t screenRow;
  static uint8_t textLength;

  switch (state) {
  case FIND_START: // looking for < character
    if (hot == '<')
      state = SET_OPCODE;
    return;
  case SET_OPCODE: // waiting for opcode
    state = (hot == '@' && _callback) ? SKIP_SPACES1 : FIND_START;
    return;
  case SKIP_SPACES1: // skip spaces to screen id
    if (hot == ' ')
      return;
    screenId = 0;
    state = BUILD_SCREENID;
    [[fallthrough]];   // character will be reinterpreted
  case BUILD_SCREENID: // building screen Id
    if (hot == ' ') {
      state = SKIP_SPACES2;
      return;
    }
    if (hot < '0' || hot > '9') {
      state = FIND_START; // malformed number, start again.
      return;
    }
    screenId = 10 * screenId + (hot - '0');
    return;
  case SKIP_SPACES2: // skip spaces to row
    if (hot == ' ')
      return;
    screenRow = 0;
    state = BUILD_ROW;
    [[fallthrough]]; // character will be reinterpreted
  case BUILD_ROW:    // building screen row
    if (hot == ' ') {
      state = SKIP_SPACES3;
      return;
    }
    if (hot < '0' || hot > '9') {
      state = FIND_START; // malformed number, start again.
      return;
    }
    screenRow = 10 * screenRow + (hot - '0');
    return;
  case SKIP_SPACES3: // skip spaces to "text"
    if (hot == ' ')
      return;
    if (hot == '"') {
      textLength = 0;
      state = COPY_TEXT;
    } else
      state = FIND_START; // missing "text", start again
    return;
  case COPY_TEXT: // copying text to buffer
    if (hot == '"') {
      // end of text found
      _text[textLength] = 0;
      if (_callback) {
        _callback->updateScreen(screenId, screenRow, _text);
      }
      state = FIND_START;
      return;
    }
    if (textLength < _maxTextLength)
      _text[textLength++] = hot;
    return;
  }
}

void AtFinder::cleanUp() {
  free(AtFinder::_text);
  AtFinder::_text = nullptr;
  AtFinder::_callback = nullptr;
  AtFinder::_logger = nullptr;
}

void AtFinder::setLogger(Logger *logger) { _logger = logger; }
