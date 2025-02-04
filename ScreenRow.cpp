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

#include "ScreenRow.h"

ScreenRow::ScreenRow(uint8_t screenRowId)
    : _screenRowId(screenRowId), _text(nullptr), _next(nullptr), _logger(nullptr), _needsRedraw(true) {}

uint8_t ScreenRow::getId() { return _screenRowId; }

void ScreenRow::setNext(ScreenRow *screenRow) { _next = screenRow; }

ScreenRow *ScreenRow::getNext() { return _next; }

void ScreenRow::setText(const char *text) {
  if (text == nullptr) {
    return;
  }
  if (_text) {
    delete[] _text;
    _text = nullptr;
  }
  _text = new char[strlen(text) + 1];
  strcpy(_text, text);
  _needsRedraw = true;
  LOG(LogLevel::LOG_DEBUG, "ScreenRow::setText(%s)", _text);
}

const char *ScreenRow::getText() {
  _needsRedraw = false;
  return _text;
}

void ScreenRow::setLogger(Logger *logger) { _logger = logger; }

bool ScreenRow::needsRedraw() { return _needsRedraw; }

ScreenRow::~ScreenRow() {
  if (_text) {
    delete[] _text;
  }
  _text = nullptr;
  _next = nullptr;
  _logger = nullptr;
}
