/*
 *  © 2024 Peter Cole
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

#include "Screen.h"

Screen::Screen(uint8_t screenId) : _screenId(screenId), _next(nullptr), _firstScreenRow(nullptr), _logger(nullptr) {}

uint8_t Screen::getId() { return _screenId; }

void Screen::setNext(Screen *screen) { _next = screen; }

Screen *Screen::getNext() { return _next; }

void Screen::updateScreenRow(uint8_t screenRowId, const char *text) {
  // Check if it exists already
  ScreenRow *updateRow = getScreenRowById(screenRowId);
  // If not, create and add to the list unless this is supposed to delete it with ""
  if (updateRow == nullptr && strcmp(text, "") != 0) {
    _addScreenRow(screenRowId, text);
  } else {
    // If "" this row is to be deleted
    if (strcmp(text, "") == 0) {
      _deleteScreenRow(updateRow);
    } else {
      // Otherwise update the text
      updateRow->setText(text);
    }
  }
}

ScreenRow *Screen::getFirstScreenRow() { return _firstScreenRow; }

ScreenRow *Screen::getScreenRowById(uint8_t screenRowId) {
  if (_firstScreenRow == nullptr) {
    return nullptr;
  }
  for (ScreenRow *row = _firstScreenRow; row; row = row->getNext()) {
    if (row->getId() == screenRowId) {
      return row;
    }
  }
  return nullptr;
}

void Screen::setLogger(Logger *logger) { _logger = logger; }

Screen::~Screen() {
  if (_firstScreenRow != nullptr) {
    ScreenRow *row = _firstScreenRow;
    ScreenRow *next = nullptr;
    while (row) {
      next = row->getNext();
      delete row;
      row = next;
    }
    _firstScreenRow = nullptr;
  }

  _next = nullptr;
}

void Screen::_addScreenRow(uint8_t screenRowId, const char *text) {
  LOG(LogLevel::DEBUG, "Screen::_addScreenRow(%d, %s)", screenRowId, text);
  ScreenRow *newRow = new ScreenRow(screenRowId);
  newRow->setText(text);
  // If we don't have a first, this is it
  if (_firstScreenRow == nullptr) {
    _firstScreenRow = newRow;
  } else {
    // Otherwise, iterate through the list and add to the end
    ScreenRow *row = _firstScreenRow;
    while (row->getNext() != nullptr) {
      row = row->getNext();
    }
    row->setNext(newRow);
  }
}

void Screen::_deleteScreenRow(ScreenRow *screenRow) {
  if (screenRow == nullptr) {
    return;
  }
  LOG(LogLevel::DEBUG, "Screen::_deleteScreenRow() - ID: %d", screenRow->getId());
  // If it's the first in the list, shuffle to next, delete, and done
  if (_firstScreenRow == screenRow) {
    ScreenRow *deleteRow = _firstScreenRow;
    _firstScreenRow = deleteRow->getNext();
    delete deleteRow;
    return;
  }
  // Otherwise iterate through, shuffle, delete, and done
  ScreenRow *currentRow = _firstScreenRow;
  ScreenRow *previousRow = nullptr;

  while (currentRow != nullptr) {
    if (currentRow == screenRow) {
      previousRow->setNext(currentRow->getNext());
      delete currentRow;
      return;
    }
    previousRow = currentRow;
    currentRow = currentRow->getNext();
  }
}
