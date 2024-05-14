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
  if (isLine()) {
    bitClear(_rowAttributes, 0);
  }
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

void EXDisplayRow::setLine(bool line) {
  if (line) {
    bitSet(_rowAttributes, 0);
  } else {
    bitClear(_rowAttributes, 0);
  }
  _changed = true;
}

bool EXDisplayRow::isLine() {
  _changed = false;
  return bitRead(_rowAttributes, 0);
}

void EXDisplayRow::setUnderline(bool underline) {
  if (underline) {
    bitSet(_rowAttributes, 1);
  } else {
    bitClear(_rowAttributes, 1);
  }
  _changed = true;
}

bool EXDisplayRow::isUnderlined() { return bitRead(_rowAttributes, 1); }

uint8_t EXDisplayRow::getAttributes() { return _rowAttributes; }

void EXDisplayRow::_rowFormatter(EXDisplayRow *row) {
  /*
  Need to check for all possible formatting codes here
  When formatting codes discovered:
  - Apply attributes to _rowAttributes as required
  - Copy _rowText to a temp char
  - Use strncpy to copy only the text from temp back to _rowText (drop format codes)
  - Delete temp char
  - Need to add a formatter for DELETING a row, which must delete from linked list + _rowText
  */
}
