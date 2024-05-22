#include "Defines.h"
#include "LogicalDisplay.h"

/*
 * LogicalDisplay class implementation
 */
LogicalDisplay::LogicalDisplay(uint8_t displayNumber, uint8_t maxRowLength, uint8_t maxRowNumber, uint16_t textColour,
                               uint16_t backgroundColour)
    : _displayNumber(displayNumber), _maxRowLength(maxRowLength), _maxRowNumber(maxRowNumber),
      _defaultTextColour(textColour), _defaultBackgroundColour(backgroundColour) {
  _firstRow = nullptr;
  _next = nullptr;
  _highestRowNumber = 0;
  _numberOfRows = 0;
  _scrollPosition = 0;
  _lastScrollTime = 0;
  _needsRedraw = false;
}

void LogicalDisplay::setNext(LogicalDisplay *display) { _next = display; }

LogicalDisplay *LogicalDisplay::getNext() { return _next; }

LogicalDisplayRow *LogicalDisplay::getFirstRow() { return _firstRow; }

uint8_t LogicalDisplay::getDisplayNumber() { return _displayNumber; }

LogicalDisplayRow *LogicalDisplay::getRowByNumber(uint8_t rowNumber) {
  for (auto *row = _firstRow; row; row = row->getNext()) {
    if (row->getRowNumber() == rowNumber) {
      return row;
    }
  }
  return nullptr;
}

void LogicalDisplay::updateRow(uint8_t rowNumber, char *rowText) {
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

void LogicalDisplay::scrollUp() {
  // Scroll up logic:
  // _scrollPosition needs to decrement to bring lower rows up the screen
  // If _scrollPosition ends at 0, it should become the highest possible row
  uint8_t lastRow = _maxRowNumber - 1; // Highest possible row number on screen
  if (_highestRowNumber <= lastRow) {  // If our max row number is on screen, no scroll required
    return;
  }
  if (_scrollPosition == 0) { // If row 0 is top of screen, need to move to the highest row number
    _scrollPosition = _highestRowNumber;
  } else { //
    _scrollPosition--;
  }
  for (LogicalDisplayRow *row = _firstRow; row; row = row->getNext()) {
    uint8_t newRow = row->getDisplayRow();
    if (newRow == _highestRowNumber) { // If row at bottom, it becomes first row
      newRow = 0;
    } else { // Otherwise move down one row
      newRow++;
    }
    row->setDisplayRow(_scrollPosition, _maxRowNumber, _highestRowNumber);
  }
  _needsRedraw = true; // Need to redraw after each scroll
}

void LogicalDisplay::scrollDown() {
  uint8_t lastRow = _maxRowNumber - 1; // Highest possible row number on screen
  if (_highestRowNumber <= lastRow) {  // If our max row number is on screen, no scroll required
    return;
  }
  if (_scrollPosition >= lastRow) { // If last row is top of screen, goes to bottom
    _scrollPosition = 0;
  } else { // Otherwise next row is top of screen
    _scrollPosition++;
  }
  for (LogicalDisplayRow *row = _firstRow; row; row = row->getNext()) {
    uint8_t newRow = row->getDisplayRow();
    if (newRow == 0) { // If row at top of screen, it becomes last row
      newRow = _highestRowNumber;
    } else { // Otherwise move up one row
      newRow--;
    }
    row->setDisplayRow(_scrollPosition, _maxRowNumber, _highestRowNumber);
  }
  _needsRedraw = true; // Need to redraw after each scroll
}

void LogicalDisplay::autoScroll(unsigned long scrollDelay) {
  if (millis() - _lastScrollTime > scrollDelay) {
    _lastScrollTime = millis();
    scrollDown();
  }
}

bool LogicalDisplay::needsRedraw() { return _needsRedraw; }

void LogicalDisplay::setRedraw(bool redraw) { _needsRedraw = redraw; }

uint16_t LogicalDisplay::getDefaultTextColour() { return _defaultTextColour; }

uint16_t LogicalDisplay::getDefaultBackgroundColour() { return _defaultBackgroundColour; }

uint8_t LogicalDisplay::getMaxRowLength() { return _maxRowLength; }

LogicalDisplayRow *LogicalDisplay::_addRow(uint8_t rowNumber, char *rowText) {
  // create a new row and chain it in
  LogicalDisplayRow *row = new LogicalDisplayRow(rowNumber);
  _numberOfRows++;

  // find the row prior to the one we want to add
  LogicalDisplayRow *previous = nullptr;
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
  if (rowNumber > _highestRowNumber) {
    _highestRowNumber = rowNumber;
  }
  row->setColours(TEXT_COLOUR, BACKGROUND_COLOUR);
  row->setRowText(rowText);
  row->setDisplayRow(_scrollPosition, _maxRowNumber, _highestRowNumber);
  return row;
}

void LogicalDisplay::_deleteRow(LogicalDisplayRow *row) {
  if (!row) {
    return; // Return if the row is nullptr
  }

  // Find the previous node in the linked list
  LogicalDisplayRow *previous = nullptr;
  LogicalDisplayRow *current = _firstRow;
  while (current != row) {
    previous = current;
    current = current->getNext();
  }

  // Remove the node from the linked list
  if (previous) {
    previous->setNext(row->getNext());
  } else {
    _firstRow = row->getNext();
  }

  // Decrement the number of rows
  _numberOfRows--;

  // Update the maximum row number if necessary
  if (row->getRowNumber() == _highestRowNumber) {
    _highestRowNumber = 0;
    for (LogicalDisplayRow *temp = _firstRow; temp; temp = temp->getNext()) {
      if (temp->getRowNumber() > _highestRowNumber) {
        _highestRowNumber = temp->getRowNumber();
      }
    }
  }

  // If we're now within the confines of the screen, need to reset display rows and redraw
  if (_highestRowNumber <= _maxRowNumber) {
    _scrollPosition = 0;
    for (LogicalDisplayRow *temp = _firstRow; temp; temp = temp->getNext()) {
      temp->setDisplayRow(_scrollPosition, _maxRowNumber, _highestRowNumber);
    }
    _needsRedraw = true;
  }

  // Delete the row object
  delete row;
}
