#include "EXDisplayClass.h"

/// @brief Define the first EXDisplay object as a nullptr
EXDisplay *EXDisplay::_first = nullptr;

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
}

void EXDisplay::autoScroll(unsigned long scrollDelay) {
  uint8_t screenRows = _exScreen->getMaxRows();
  uint8_t newPosition = 0;
  if (_numberOfRows <= screenRows) {
    _scrollPosition = newPosition;
  } else {
    if (millis() - _lastScrollTime > scrollDelay) {
      newPosition = _scrollPosition++;
      if (newPosition >= _numberOfRows) {
        newPosition = 0;
      }
    }
  }
  _scrollPosition = newPosition;
}

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
