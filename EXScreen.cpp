#include "EXScreen.h"

/// @brief Define the first screen as a nullptr to start
EXScreen *EXScreen::_first = nullptr;

EXScreen::EXScreen(uint8_t screenId, uint8_t rows, uint8_t columns) : _id(screenId), _rows(rows), _columns(columns) {
  _next = _first;
  _first = this;
}

uint8_t EXScreen::getId() { return _id; }

uint8_t EXScreen::getRows() { return _rows; }

uint8_t EXScreen::getColumns() { return _columns; }

EXScreen *EXScreen::getFirst() { return _first; }

EXScreen *EXScreen::getNext() { return _next; }
