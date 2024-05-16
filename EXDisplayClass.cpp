#include "EXDisplayClass.h"

/// @brief Define the first EXDisplay object as a nullptr
EXDisplay *EXDisplay::_first = nullptr;

/// @brief Define the active display as nullptr also
EXDisplay *EXDisplay::_activeDisplay = nullptr;

/// @brief Define initial last switch time as 0
unsigned long EXDisplay::_lastSwitchTime = 0;

/// @brief Count of displays
uint8_t EXDisplay::_displayCount = 0;

/*
 * EXDisplay class implementation
 */
EXDisplay::EXDisplay(uint8_t displayNumber, EXScreen *exScreen, uint8_t maxScreenWidth)
    : _displayNumber(displayNumber), _exScreen(exScreen), _maxScreenWidth(maxScreenWidth) {
  _firstRow = nullptr;
  _next = _first;
  _first = this;
  _maxRowNumber = 0;
  _numberOfRows = 0;
  _scrollPosition = 0;
  _lastScrollTime = 0;
  _needsRedraw = false;
  if (!_activeDisplay) {
    _activeDisplay = _first;
  }
  _displayCount++;
}

EXDisplay *EXDisplay::getFirst() { return _first; }

EXDisplay *EXDisplay::getNext() { return _next; }

EXDisplayRow *EXDisplay::getFirstRow() { return _firstRow; }

uint8_t EXDisplay::getDisplayNumber() { return _displayNumber; }

EXDisplayRow *EXDisplay::getRowByNumber(uint8_t rowNumber) {
  for (auto *row = _firstRow; row; row = row->getNext()) {
    if (row->getRowNumber() == rowNumber) {
      return row;
    }
  }
  return nullptr;
}

void EXDisplay::updateRow(uint8_t rowNumber, char *rowText) {
  auto *row = getRowByNumber(rowNumber);
  if (row && strlen(rowText) == 0) {
    _deleteRow(row);
  } else if (!row && strlen(rowText) == 0) {
    return;
  } else if (!row) {
    row = _addRow(rowNumber, rowText);
  } else {
    row->setRowText(rowText);
  }
}

void EXDisplay::scrollUp() {
  // Scroll up logic:
  // _scrollPosition needs to decrement to bring lower rows up the screen
  // If _scrollPosition ends at 0, it should become the highest possible row
  uint8_t lastRow = _exScreen->maxRows - 1; // Highest possible row number on screen
  if (_maxRowNumber <= lastRow) {           // If our max row number is on screen, no scroll required
    return;
  }
  if (_scrollPosition == 0) { // If row 0 is top of screen, need to move to the highest row number
    _scrollPosition = _maxRowNumber;
  } else { //
    _scrollPosition--;
  }
  for (EXDisplayRow *row = _firstRow; row; row = row->getNext()) {
    uint8_t newRow = row->getDisplayRow();
    if (newRow == _maxRowNumber) { // If row at bottom, it becomes first row
      newRow = 0;
    } else { // Otherwise move down one row
      newRow++;
    }
    row->setDisplayRow(newRow, _exScreen->maxRows);
  }
  _needsRedraw = true; // Need to redraw after each scroll
}

void EXDisplay::scrollDown() {
  uint8_t lastRow = _exScreen->maxRows - 1; // Highest possible row number on screen
  if (_maxRowNumber <= lastRow) {           // If our max row number is on screen, no scroll required
    return;
  }
  if (_scrollPosition >= lastRow) { // If last row is top of screen, goes to bottom
    _scrollPosition = 0;
  } else { // Otherwise next row is top of screen
    _scrollPosition++;
  }
  for (EXDisplayRow *row = _firstRow; row; row = row->getNext()) {
    uint8_t newRow = row->getDisplayRow();
    if (newRow == 0) { // If row at top of screen, it becomes last row
      newRow = _maxRowNumber;
    } else { // Otherwise move up one row
      newRow--;
    }
    row->setDisplayRow(newRow, _exScreen->maxRows);
  }
  _needsRedraw = true; // Need to redraw after each scroll
}

void EXDisplay::autoScroll(unsigned long scrollDelay) {
  if (millis() - _lastScrollTime > scrollDelay) {
    _lastScrollTime = millis();
    scrollDown();
  }
}

EXScreen *EXDisplay::getEXScreen() { return _exScreen; }

uint8_t EXDisplay::getScreenMaxRows() { return _exScreen->maxRows; }

uint8_t EXDisplay::getScreenMaxColumns() { return _exScreen->maxColumns; }

bool EXDisplay::needsRedraw() { return _needsRedraw; }

void EXDisplay::resetRedraw() { _needsRedraw = false; }

bool EXDisplay::displayNumberExists(uint8_t displayNumber) { return getDisplayByNumber(displayNumber) != nullptr; }

EXDisplay *EXDisplay::getDisplayByNumber(uint8_t displayNumber) {
  for (auto *display = _first; display; display = display->_next) {
    if (display->_displayNumber == displayNumber) {
      return display;
    }
  }
  return nullptr;
}

EXDisplay *EXDisplay::getActiveDisplay() { return _activeDisplay; }

void EXDisplay::setNextDisplay() {
  if (!_activeDisplay) {
    _activeDisplay = _first;
    _activeDisplay->_needsRedraw = true;
    return;
  }
  if (_displayCount == 1) {
    return;
  }
  if (_activeDisplay->_next) {
    _activeDisplay = _activeDisplay->_next;
  } else {
    _activeDisplay = _first;
  }
  _activeDisplay->_needsRedraw = true;
}

void EXDisplay::setPreviousDisplay() {
  if (!_activeDisplay) {
    _activeDisplay = _first;
    _activeDisplay->_needsRedraw = true;
    return;
  }
  if (_displayCount == 1) {
    return;
  }
  for (EXDisplay *display = _activeDisplay; display; display = display->getNext()) {
    if (display->getNext() == _activeDisplay) {
      _activeDisplay = display;
      _activeDisplay->_needsRedraw = true;
      return;
    }
  }
}

void EXDisplay::autoSwitch(unsigned long switchDelay) {
  if (millis() - EXDisplay::_lastSwitchTime > switchDelay) {
    EXDisplay::_lastSwitchTime = millis();
    setNextDisplay();
  }
}

void EXDisplay::processDisplay() {
  if (_needsRedraw) {
    _exScreen->clearScreen(BACKGROUND_COLOUR);
  }
  for (EXDisplayRow *row = _firstRow; row; row = row->getNext()) {
    if (row->needsRender() && (row->isChanged() || _needsRedraw)) {
      if (row->isLine()) {
        _exScreen->writeLine(row->getDisplayRow(), 0, _exScreen->maxColumns, row->getTextColour(),
                             row->getBackgroundColour());
      } else {
        _exScreen->writeRow(row->getDisplayRow(), 0, row->getTextColour(), row->getBackgroundColour(),
                            _exScreen->maxColumns, row->getRowText(), row->isUnderlined());
      }
    }
  }
  _needsRedraw = false;
}

EXDisplayRow *EXDisplay::_addRow(uint8_t rowNumber, char *rowText) {
  // create a new row and chain it in
  EXDisplayRow *row = new EXDisplayRow(rowNumber);
  _numberOfRows++;

  // find the row prior to the one we want to add
  EXDisplayRow *previous = nullptr;
  for (auto peek = _firstRow; peek; peek = peek->getNext()) {
    if (peek->getRowNumber() > rowNumber)
      break;
    previous = peek;
  }
  if (previous) {
    // chain after previous
    row->setNext(previous->getNext());
    previous->setNext(row);
  } else {
    // chain at start of list
    row->setNext(_firstRow);
    _firstRow = row;
  }
  if (rowNumber > _maxRowNumber) {
    _maxRowNumber = rowNumber;
  }
  row->setColours(TEXT_COLOUR, BACKGROUND_COLOUR);
  row->setRowText(rowText);
  row->setDisplayRow(rowNumber, _exScreen->maxRows);
  return row;
}

void EXDisplay::_deleteRow(EXDisplayRow *row) {
  CONSOLE.print(F("Need to implement deleting row "));
  CONSOLE.println(row->getRowNumber());
  // EXDisplayRow *currentRow = _firstRow;
  // while (currentRow != nullptr && currentRow->getNext() != nullptr) {
  //   if (currentRow->getNext()->getRowNumber() == rowNumber) {
  //     EXDisplayRow *temp = currentRow->getNext();
  //     currentRow->setNext(temp->getNext());
  //     delete temp; // CAUTION DESTRUCTOR MUST DELETE TEXT TOO
  //     return;
  //   }
  //   currentRow = currentRow->getNext();
}
