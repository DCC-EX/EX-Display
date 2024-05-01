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

DISPLAY_CALLBACK AtFinder::callback = nullptr;
uint8_t AtFinder::maxTextLength = 0;
char *AtFinder::text = nullptr;

// Set maximum accepted length of "text". Longer texts will be trimmed.
// Set callback function that will be called when message detected.

// Note: the code is safe if setup is not called before use because the
// code can not reach the text handling or callback states. 
// If the sketch has no reference to the setup function at all,
// then compiler constant propagation is smart enough to realise
// that it can never reach the text handling states, and thus
// the entire function has no effect and is eliminated from the link.


void AtFinder::setup(uint8_t _maxTextLength, DISPLAY_CALLBACK _callback) {
  maxTextLength = _maxTextLength;
  text = (char *)malloc(maxTextLength + 1);
  callback = _callback;
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
    state = (hot == '@' && callback) ? SKIP_SPACES1 : FIND_START;
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
  case BUILD_ROW:   // building screen row
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
      text[textLength] = 0;
      if (callback)
        callback(screenId, screenRow, text); // ET PHONE HOME!
      state = FIND_START;
      return;
    }
    if (textLength < maxTextLength)
      text[textLength++] = hot;
    return;
  }
}
