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

#include "DisplayInterface.h"

void DisplayInterface::setNext(DisplayInterface *display) { _next = display; }

DisplayInterface *DisplayInterface::getNext() { return _next; }

void DisplayInterface::setLogger(Logger *logger) { _logger = logger; }

void DisplayInterface::setId(uint8_t displayId) { _displayId = displayId; }

uint8_t DisplayInterface::getId() { return _displayId; }

void DisplayInterface::setScreenId(int screenId) {
  _needsRedraw = true;
  _screenId = screenId;
}

int DisplayInterface::getScreenId() { return _screenId; }

int DisplayInterface::getCSPin() { return _csPin; }

void DisplayInterface::setNeedsRedraw(bool redraw) { _needsRedraw = redraw; }

bool DisplayInterface::needsRedraw() { return _needsRedraw; }

/**
 * @brief Static method to enable calling back to a derived class with a formatted row
 * @details Valid uses of modifiers:
 * "`_`This is an underlined row"
 * "`-`This is a horizontal line, text will be ignored"
 * "`~`This row will always ticker when implemented"
 * "`!`This row will never ticker when implemented"
 * "`#FF0000`This row has red text"
 * "`_``~`This row  is underlined, will always ticker, and `#FF0000`this bit of text is red"
 * "`!``_`This row is underlined, and will never ticker"
 * "`#FF0000`This row starts red, then goes `#FFFFFF`white"
 * @param display Derived instance containing the displayFormattedRow() method
 * @param row Row to display
 * @param text Text containing formatting
 */
void DisplayInterface::formatRow(DisplayInterface *display, int rowId, const char *text) {
  /**
   * @brief stateMachine enum allows us to iterate through each char of text and examine it byte by byte for modifiers.
   */
  enum stateMachine : byte {
    FIND_MODSTART,
    FIND_MODIFIER,
  };

  int textLength = strlen(text) + 1;  /** Length of the provided text, we can't return anything longer than this */
  int textStart = 0;                  /** Starting index of text we need to return, enables subtracting modifiers */
  char *returnedText;                 /** Text to return, will be sized with modifiers removed */
  char check;                         /** Holds each char for checking */
  stateMachine state = FIND_MODSTART; /** Start by looking for the first backtick */
  RowAttributes attributes = {false, false, false,
                              false, false, 0xFFFF}; /** Set all attributes false to start with, and white text */

  /** If our very first char is not a backtick, then we have no leading modifiers but may have embedded colours */
  check = text[0];
  if (check != '`') {
    // state = FIND_COLOURSTART; /** Start by looking for a backtick ahead of # for colour */
    display->displayFormattedRow(rowId, 0, attributes, text, false); /** For now we're not finding colours */
  }

  // Now iterate through the provided text to look for modifiers
  for (int i = 0; i < textLength; i++) {
    check = text[i];
    switch (state) {
    case FIND_MODSTART: { // If first backtick, look for a modifier next
      if (check == '`') {
        state = FIND_MODIFIER;
        continue;
      }
    }
    case FIND_MODIFIER: {
      if (_isModifier(check) && text[i + 1] == '`') { // If modifier is valid and next char is backtick, set it
        attributes = _setAttribute(attributes, check);
        i++;
        state = FIND_MODSTART; // There may be more modifiers so look again
        continue;
      }
    }
    }
  }
  attributes = DisplayInterface::_sanitiseAttributes(attributes);
  display->displayFormattedRow(rowId, 0, attributes, text, false);
}

RowAttributes DisplayInterface::_sanitiseAttributes(RowAttributes attributes) {
  if (attributes.isLine) {
    attributes.isUnderlined = false;
    attributes.alwaysTicker = false;
    attributes.neverTicker = false;
  }
  if (attributes.alwaysTicker && attributes.neverTicker) {
    attributes.alwaysTicker = false;
    attributes.neverTicker = false;
  }
  return attributes;
}

bool DisplayInterface::_isModifier(char check) {
  if (check == '_' || check == '-' || check == '~' || check == '!') {
    return true;
  } else {
    return false;
  }
}

RowAttributes DisplayInterface::_setAttribute(RowAttributes attributes, char modifier) {
  switch (modifier) {
  case '#':
    attributes.colourSet = true;
    break;
  case '_':
    attributes.isUnderlined = true;
    break;
  case '-':
    attributes.isLine = true;
    break;
  case '~':
    attributes.alwaysTicker = true;
    break;
  case '!':
    attributes.neverTicker = true;
    break;
  default:
    break;
  }
  return attributes;
}
