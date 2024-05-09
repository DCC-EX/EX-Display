#include "EXDisplayClass.h"

/// @brief Define the first EXDisplay object as a nullptr
EXDisplay *EXDisplay::_first = nullptr;

/// @brief Define the active display as nullptr also
EXDisplay *EXDisplay::_activeDisplay = nullptr;

/// @brief Define initial last switch time as 0
unsigned long EXDisplay::_lastSwitchTime = 0;

/*
 * EXDisplay class implementation
 */
EXDisplay::EXDisplay(uint8_t displayNumber, EXScreen *exScreen, uint8_t maxScreenWidth)
    : _displayNumber(displayNumber), _exScreen(exScreen), _maxScreenWidth(maxScreenWidth) {
  _firstRow = nullptr;
  _next = _first;
  _first = this;
  _numberOfRows = 0;
  _scrollPosition = 0;
  _lastScrollTime = 0;
  _needsRedraw = false;
  if (!_activeDisplay) {
    _activeDisplay = _first;
  }
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
  if (!row) {
    // create a new row and chain it in
    row = new EXDisplayRow(rowNumber);
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
  }
  row->setRowText(rowText);
  row->setDisplayRow(rowNumber, _exScreen->maxRows);
}

void EXDisplay::scrollUp() {
  uint8_t screenRows = _exScreen->maxRows;
  uint8_t newPosition = 0;
  if (_numberOfRows <= screenRows) {
    _scrollPosition = newPosition;
  } else {
    newPosition = _scrollPosition--;
    if (newPosition >= _numberOfRows) {
      newPosition = 0;
    }
  }
  _scrollPosition = newPosition;
}

void EXDisplay::scrollDown() {
  // If the highest row number is more than will fit on the screen we need to scroll
  // If not, do not redraw screen and do not update any displayRow or scroll values
  uint8_t lastRow = _exScreen->maxRows - 1;
  uint8_t newScroll = _scrollPosition;
  if (_scrollPosition == lastRow) {
    newScroll = 0;
  } else {
    for (EXDisplayRow *row = _firstRow; row; row = row->getNext()) {

    }
  }
  _needsRedraw = true;
}

void EXDisplay::autoScroll(unsigned long scrollDelay) {
  if (millis() - _lastScrollTime > scrollDelay) {
    _lastScrollTime = millis();
    CONSOLE.println(F("Time to scroll"));
    scrollDown();
  }
}

EXScreen *EXDisplay::getEXScreen() { return _exScreen; }

uint8_t EXDisplay::getScreenMaxRows() { return _exScreen->maxRows; }

uint8_t EXDisplay::getScreenMaxColumns() { return _exScreen->maxColumns; }

bool EXDisplay::needsRedraw() { return _needsRedraw; }

void EXDisplay::resetRedraw() { _needsRedraw = false; }

/*** probably not needed
 void EXDisplay::deleteRowNumber(uint8_t rowNumber) {
  EXDisplayRow *currentRow = _firstRow;
  while (currentRow != nullptr && currentRow->getNext() != nullptr) {
    if (currentRow->getNext()->getRowNumber() == rowNumber) {
      EXDisplayRow *temp = currentRow->getNext();
      currentRow->setNext(temp->getNext());
      delete temp; // CAUTION DESTRUCTOR MUST DELETE TEXT TOO
      return;
    }
    currentRow = currentRow->getNext();
  }
}
***/

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
    CONSOLE.println(F("Time to switch"));
    setNextDisplay();
  }
}
