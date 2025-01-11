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
 * @param row Row to display
 * @param text Text containing formatting
 */
void DisplayInterface::formatRow(int rowId, const char *text) {
  /**
   * @brief stateMachine enum allows us to iterate through each char of text and examine it byte by byte for modifiers.
   */
  enum stateMachine : byte { FIND_MODSTART, FIND_MODIFIER, FIND_COLOURSTART, FIND_COLOUR, BUILD_TEXT };

  size_t textLength = strlen(text) + 1;  /** Length of the provided text, we can't return anything longer than this */
  size_t textStart = 0;                  /** Starting index of text we need to return, enables subtracting modifiers */
  size_t copyLength = 0;                 /** Size of text to copy into textOnly later */
  int column = 0;                        /** Default start at column 0, update if colours are embedded */
  bool append = false;                   /** Default is a new row, update if colours are embedded */
  char *textOnly = new char[textLength]; /** Text only minus any modifiers, no bigger than provided size */
  char check;                            /** Holds each char for checking */
  stateMachine state = FIND_MODSTART;    /** Start by looking for the first backtick */
  RowAttributes attributes = {false, false, false,
                              false, false, 0xFFFF}; /** Set all attributes false to start with, and white text */

  // Iterate through the provided text to look for leading modifiers
  for (size_t i = 0; i < textLength; i++) {
    check = text[i];
    switch (state) {
    case FIND_MODSTART: { // If first backtick, look for a modifier next, skip if using colour modifier
      if (check == '`' && text[i + 1] != '#') {
        state = FIND_MODIFIER;
        break;
      }
    }
    case FIND_MODIFIER: {
      if (_isModifier(check) && text[i + 1] == '`') { // If modifier is valid and next char is backtick, set it
        attributes = _setAttribute(attributes, check);
        i++;
        state = FIND_MODSTART; // There may be more modifiers so look again
        textStart = i + 1;     // Set the start of our text to the next char after the backtick
      } else {
        state = FIND_COLOURSTART; // Now we've finished with modifiers, need to look for colours
      }
      break;
    }
    case FIND_COLOURSTART: {
      if (check == '`') {
        state = FIND_COLOUR;
        break;
      }
    }
    case FIND_COLOUR: {
      if (check == '#' && text[i + 7] == '`') { // Look for valid colour size of #FFFFFF
        char *rgb = new char[7];
        strncpy(rgb, text + i + 1, 6); // Extract the RGB colour string
        rgb[6] = '\0';
        if (_isRGB(rgb)) { // If colour is valid, we need to convert to RGB565
          uint16_t rgb565 = _convertRGBtoRGB565(rgb);
          // if (i > textStart) { // If the colour is found after the start of our text...
          //   // Calculate text length and copy the subtext so far
          //   // Send that off with:
          //   // display->displayFormattedRow(rowId, column, attributes, textSoFar, append);
          //   // Set append flag because everything after that is appended
          //   copyLength = i - textStart;
          //   strncpy(textOnly, text + textStart, copyLength);
          //   textOnly[copyLength] = '\0';
          //   displayFormattedRow(rowId, column, attributes, textOnly, append);
          //   append = true;
          //   i += 8;
          // }
          textStart = i + 8;
          attributes = _setAttribute(attributes, check, rgb565); // Set the colour and flag it
        }
        delete[] rgb;
      }
    }
    case BUILD_TEXT: {
      // If we're no longer looking for modifiers, continue to build the returned text
      break;
    }
    }
    // If we've flagged we've finished with modifiers, break out of the loop, no more to do
    if (state == BUILD_TEXT) {
      break;
    }
  }
  // Make sure our attributes are sane according to the rules
  attributes = DisplayInterface::_sanitiseAttributes(attributes);
  // If we've set a horizontal line, we don't return text, just null terminator
  if (attributes.isLine) {
    textOnly[0] = '\0';
  } else {
    // Otherwise copy the appropriate chars to returnedText ready to call our method
    copyLength = textLength - textStart - 1;
    strncpy(textOnly, text + textStart, copyLength);
    textOnly[copyLength] = '\0';
  }
  displayFormattedRow(rowId, column, attributes, textOnly, append);
  delete[] textOnly;
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
  // Note while # is the modifier for colour, it is not a single char modifier and is dealt with separately
  if (check == '_' || check == '-' || check == '~' || check == '!') {
    return true;
  } else {
    return false;
  }
}

RowAttributes DisplayInterface::_setAttribute(RowAttributes attributes, char modifier, uint16_t colour) {
  switch (modifier) {
  case '#':
    attributes.colourSet = true;
    attributes.textColour = colour;
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

bool DisplayInterface::_isRGB(const char *colour) {
  bool isRGB = true;
  for (size_t i = 0; i < 6; i++) {
    // Iterate through the char array, valid chars are 0-9 and A-f
    if ((colour[i] < '0' || colour[i] > '9') && (colour[i] < 'A' && colour[i] > 'F')) {
      isRGB = false;
    }
  }
  return isRGB;
}

uint16_t DisplayInterface::_convertRGBtoRGB565(const char *colour) {
  uint16_t rgb565 = 0;
  uint8_t r = strtol(colour, NULL, 16) >> 16;
  uint8_t g = (strtol(colour, NULL, 16) >> 8) & 0xFF;
  uint8_t b = strtol(colour, NULL, 16) & 0xFF;
  rgb565 = ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
  return rgb565;
}
