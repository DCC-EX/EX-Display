#include "Defines.h"
#include "EXDisplayRow.h"

/*
 * EXDisplayRow class implementation
 */
EXDisplayRow::EXDisplayRow(uint8_t rowNumber) {
  _rowNumber = rowNumber;
  _maxMalloc = 0;
  _rowText = nullptr;
  _changed = true;
  _needsRender = false;
  _rowAttributes = 0;
}

uint8_t EXDisplayRow::getRowNumber() { return _rowNumber; }

uint8_t EXDisplayRow::getMaxRowLength() { return _maxMalloc; }

void EXDisplayRow::setRowText(char *rowText) {
  // Note size limit is 254 chars but that is beyond
  // the capability of the caller anyway.

  // First thing is to format this row
  _rowFormatter(this, rowText);

  // Ignore change if text the same...
  if (_rowText && strcmp(_rowText, rowText) == 0)
    return;

  uint8_t bytesNeeded = strlen(rowText) + 1;
  if (bytesNeeded > _maxMalloc || !_rowText) {
    // _rowText is not big enough so realloc() it.
    // Deliberately dont realloc() if its big enough to
    // avolid fragmentation caused by realloc freeing
    // the tail which we will probabaly need later anyway.
    _rowText = (char *)realloc(_rowText, bytesNeeded);
    _maxMalloc = bytesNeeded;
  }
  strcpy(_rowText, rowText);
  _changed = true;
}

char *EXDisplayRow::getRowText() {
  _changed = false;
  return _rowText;
}

bool EXDisplayRow::isChanged() { return _changed; }

void EXDisplayRow::setDisplayRow(uint8_t displayRow, uint8_t maxScreenRows) {
  _displayRow = displayRow;
  if (_displayRow >= maxScreenRows) {
    _needsRender = false;
  } else {
    _needsRender = true;
  }
}

uint8_t EXDisplayRow::getDisplayRow() { return _displayRow; }

bool EXDisplayRow::needsRender() { return _needsRender; }

EXDisplayRow *EXDisplayRow::getNext() { return _next; }

void EXDisplayRow::setNext(EXDisplayRow *next) { _next = next; }

void EXDisplayRow::setColours(uint16_t textColour, uint16_t backgroundColour) {
  _textColour = textColour;
  _backgroundColour = backgroundColour;
  _changed = true;
}

uint16_t EXDisplayRow::getTextColour() { return _textColour; }

uint16_t EXDisplayRow::getBackgroundColour() { return _backgroundColour; }

bool EXDisplayRow::isLine() {
  _changed = false;
  return bitRead(_rowAttributes, 0);
}

bool EXDisplayRow::isUnderlined() { return bitRead(_rowAttributes, 1); }

uint8_t EXDisplayRow::getAttributes() { return _rowAttributes; }

void EXDisplayRow::_rowFormatter(EXDisplayRow *row, char *rowText) {
  /*
  Need to check for all possible formatting codes here
  When formatting codes discovered:
  - Apply attributes to _rowAttributes as required
    - Embedded colours: "#0xdddd#0xdddd#" (no text taken from this)
    - Row underlined: "_This text is underlined_"
    - Row is a horizontal line: "--"
    - Row always tickers: "~~Text to ticker"
    - Row never tickers: "!~Never ticker text"
    - Delete row: ""
  - Copy _rowText to a temp char
  - Use strncpy to copy only the text from temp back to _rowText (drop format codes)
  - Delete temp char
  - Return true if something has changed
  */
  bool changed = true;
  if (_isEmbeddedColours(rowText)) {
    row->_extractColours(rowText);
  } else if (_isLine(rowText)) {
    row->_setLine();
  } else if (_isUnderline(rowText)) {
    row->_setUnderline();
  } else if (_alwaysTicker(rowText)) {
    // always ticker here
  } else if (_neverTicker(rowText)) {
    // never ticker here
  } else {
    changed = false;
  }
  row->_changed = changed;
}

bool EXDisplayRow::_isEmbeddedColours(const char *text) {
  // Check for format #0x0000#0x0000#
  if (text[0] != '#' || text[7] != '#' || text[strlen(text) - 1] != '#') {
    return false;
  }
  // Find the positions of the three '#' characters
  char *start = strchr(text, '#');
  if (start == NULL) {
    return false;
  }
  char *middle = strchr(start + 1, '#');
  if (middle == NULL) {
    return false;
  }
  char *end = strchr(middle + 1, '#');
  if (end == NULL) {
    return false;
  }
  // Check if the hexadecimal values are of the correct length (6 characters)
  if (end - middle - 1 != 6 || middle - start - 1 != 6) {
    return false;
  }
  // Check if the characters between the '#' are valid hexadecimal digits
  if (text[1] != '0' || text[2] != 'x' || middle[1] != '0' || middle[2] != 'x') {
    return false;
  }
  for (const char *p = text + 3; p < middle; p++) {
    if (!((p[0] >= '0' && p[0] <= '9') || (p[0] >= 'A' && p[0] <= 'F'))) {
      return false;
    }
  }
  for (const char *p = middle + 3; p < end; p++) {
    if (!((p[0] >= '0' && p[0] <= '9') || (p[0] >= 'A' && p[0] <= 'F'))) {
      return false;
    }
  }
  return true;
}

void EXDisplayRow::_extractColours(const char *text) {
  // Find first #
  char *start = strchr(text, '#');
  // Convert text colour
  char *endPointer;
  _textColour = (uint16_t)strtol(start + 1, &endPointer, 16);
  // Find next #
  start = strchr(start + 1, '#');
  // Convert background colour
  _backgroundColour = (uint16_t)strtol(start + 1, &endPointer, 16);
  char blank[1] = {'\0'};
  char *temp = _rowText;
  _rowText = blank;
  delete(temp);
}

void EXDisplayRow::_setLine() {
  bitSet(_rowAttributes, 0);
  char blank[1] = {'\0'};
  char *temp = _rowText;
  _rowText = blank;
  delete(temp);
  _changed = true;
}

bool EXDisplayRow::_isLine(const char *text) {
  // Check for exactly "--"
  if (strlen(text) != 2 || text[0] != '-' || text[strlen(text) - 1] != '-') {
    return false;
  }
  return true;
}

void EXDisplayRow::_setUnderline() {
  bitSet(_rowAttributes, 1);
  _changed = true;
}

bool EXDisplayRow::_isUnderline(const char *text) {
  // Check for leading and trailing "_"
  if (text[0] != '_' || text[strlen(text) - 1] != '_') {
    return false;
  }
  return true;
}

bool EXDisplayRow::_alwaysTicker(const char *text) {
  // Check for leading "~~"
  if (text[0] != '~' || text[1] != '~') {
    return false;
  }
  return true;
}

bool EXDisplayRow::_neverTicker(const char *text) {
  // Check for leading "!~"
  if (text[0] != '!' || text[1] != '~') {
    return false;
  }
  return true;
}
