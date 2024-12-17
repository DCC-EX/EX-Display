#include "Defines.h"
#include "LogicalDisplayRow.h"

/*
 * LogicalDisplayRow class implementation
 */
LogicalDisplayRow::LogicalDisplayRow(uint8_t rowNumber) {
  _rowNumber = rowNumber;
  _maxMalloc = 0;
  _rowText = nullptr;
  _changed = true;
  _needsRender = false;
  _rowAttributes = {false, false, false, false};
}

uint8_t LogicalDisplayRow::getRowNumber() { return _rowNumber; }

uint8_t LogicalDisplayRow::getMaxRowLength() { return _maxMalloc; }

void LogicalDisplayRow::setRowText(char *rowText) {
  // Note size limit is 254 chars but that is beyond
  // the capability of the caller anyway.

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

  // Now we have our new text, check for formatters
  _rowFormatter();

  _changed = true;
}

char *LogicalDisplayRow::getRowText() {
  _changed = false;
  return _rowText;
}

bool LogicalDisplayRow::isChanged() { return _changed; }

void LogicalDisplayRow::setDisplayRow(uint8_t scrollPosition, uint8_t maxScreenRows, uint8_t maxRowNumber) {
  if (_rowNumber >= scrollPosition) {
    _displayRow = _rowNumber - scrollPosition;
  } else {
    _displayRow = maxRowNumber - (scrollPosition - _rowNumber - 1);
  }
  if (_displayRow >= maxScreenRows) {
    _needsRender = false;
  } else {
    _needsRender = true;
  }
}

uint8_t LogicalDisplayRow::getDisplayRow() { return _displayRow; }

bool LogicalDisplayRow::needsRender() { return _needsRender; }

LogicalDisplayRow *LogicalDisplayRow::getNext() { return _next; }

void LogicalDisplayRow::setNext(LogicalDisplayRow *next) { _next = next; }

void LogicalDisplayRow::setColours(uint16_t textColour, uint16_t backgroundColour) {
  _textColour = textColour;
  _backgroundColour = backgroundColour;
  _changed = true;
}

uint16_t LogicalDisplayRow::getTextColour() { return _textColour; }

uint16_t LogicalDisplayRow::getBackgroundColour() { return _backgroundColour; }

bool LogicalDisplayRow::isLine() {
  _changed = false;
  return _rowAttributes.line;
}

bool LogicalDisplayRow::isUnderlined() { return _rowAttributes.underline; }

LogicalDisplayRow::~LogicalDisplayRow() { free(_rowText); }

void LogicalDisplayRow::_rowFormatter() {
  /*
  Need to check for all possible formatting codes here
  When formatting codes discovered:
  - Apply attributes to _rowAttributes as required
    - Embedded colours: "#0xdddd#0xdddd#Coloured text"
    - Row underlined: "_This text is underlined_"
    - Row is a horizontal line: "--"
    - Row always tickers: "~~Text to ticker"
    - Row never tickers: "!~Never ticker text"
  */
  _setColours();
  _setLine();
  _setUnderline();
  _alwaysTicker();
  _neverTicker();
}

void LogicalDisplayRow::_setColours() {
  // Check for format #0xdddd#0xdddd#
  if (_rowText[0] != '#' || _rowText[7] != '#' || _rowText[14] != '#') {
    return;
  }
  // Find the positions of the three '#' characters
  char *start = strchr(_rowText, '#');
  if (start == NULL) {
    return;
  }
  char *middle = strchr(start + 1, '#');
  if (middle == NULL) {
    return;
  }
  char *end = strchr(middle + 1, '#');
  if (end == NULL) {
    return;
  }
  // Check if the hexadecimal values are of the correct length (4 characters)
  if (end - middle - 1 != 6 || middle - start - 1 != 6) {
    return;
  }
  // Check if the characters between the '#' are valid hexadecimal digits
  if (_rowText[1] != '0' || _rowText[2] != 'x' || middle[1] != '0' || middle[2] != 'x') {
    return;
  }
  for (const char *p = _rowText + 3; p < middle; p++) {
    if (!((p[0] >= '0' && p[0] <= '9') || (p[0] >= 'A' && p[0] <= 'F'))) {
      return;
    }
  }
  for (const char *p = middle + 3; p < end; p++) {
    if (!((p[0] >= '0' && p[0] <= '9') || (p[0] >= 'A' && p[0] <= 'F'))) {
      return;
    }
  }
  // Find first #
  start = strchr(_rowText, '#');
  // Convert text colour
  char *endPointer;
  _textColour = (uint16_t)strtol(start + 1, &endPointer, 16);
  // Find next #
  start = strchr(start + 1, '#');
  // Convert background colour
  _backgroundColour = (uint16_t)strtol(start + 1, &endPointer, 16);
  _removeFormatters(15);
}

void LogicalDisplayRow::_setLine() {
  if (strlen(_rowText) != 2 || _rowText[0] != '-' || _rowText[strlen(_rowText) - 1] != '-') {
    _rowAttributes.line = false;
    return;
  }
  _rowAttributes.line = true;
  _removeFormatters(2);
}

void LogicalDisplayRow::_setUnderline() {
  if (_rowText[0] != '_' || _rowText[1] != '_') {
    if (_rowAttributes.underline) {
      _rowAttributes.underline = false;
    }
    return;
  }
  _rowAttributes.underline = true;
  _removeFormatters(2);
}

void LogicalDisplayRow::_alwaysTicker() {
  // Check for leading "~~"
  if (_rowText[0] != '~' || _rowText[1] != '~') {
    _rowAttributes.alwaysTicker = false;
    return;
  }
  _rowAttributes.alwaysTicker = true;
  return;
}

void LogicalDisplayRow::_neverTicker() {
  // Check for leading "!~"
  if (_rowText[0] != '!' || _rowText[1] != '~') {
    _rowAttributes.neverTicker = false;
    return;
  }
  _rowAttributes.neverTicker = true;
  return;
}

void LogicalDisplayRow::_removeFormatters(uint8_t size) {
  // New length for "text" needs to be length - formatters (size) + null pointer (1)
  uint8_t textLength = strlen(_rowText) - size + 1;
  // Set our temp char array to what we already have defined as our max size
  char *temp = (char *)malloc(_maxMalloc);
  // Copy the text minus formatters to temp and null terminate
  strncpy(temp, _rowText + size, textLength);
  temp[textLength] = '\0';
  // Free the no longer required _rowText memory
  free(_rowText);
  // Temp is now _rowText
  _rowText = temp;
}
