#include "Defines.h"
#include "PhysicalScreen.h"
#include <Arduino.h>

PhysicalScreen *PhysicalScreen::_first = nullptr;
uint8_t PhysicalScreen::_screenCount = 0;

PhysicalScreen::PhysicalScreen() {
  _firstDisplay = nullptr;
  _activeDisplay = nullptr;
  _displayCount = 0;
  _lastSwitchTime = 0;
  _maxRows = 0;
  _maxRowLength = 0;
  _fontHeight = 0;
  _fontWidth = 0;
  _screenNumber = _screenCount++;
  if (!_first) {
    _first = this;
    _next = nullptr;
  } else {
    for (PhysicalScreen *screen = PhysicalScreen::getFirst(); screen; screen = screen->_next) {
      if (!screen->_next) {
        screen->_next = this;
      }
    }
  }
}

PhysicalScreen *PhysicalScreen::getFirst() { return _first; }

PhysicalScreen *PhysicalScreen::getNext() { return _next; }

LogicalDisplay *PhysicalScreen::addDisplay(uint8_t displayNumber, uint16_t defaultTextColour, uint16_t defaultBackgroundColour) {
  // Create a new display
  LogicalDisplay *display =
      new LogicalDisplay(displayNumber, _maxRowLength, _maxRows, defaultTextColour, defaultBackgroundColour);

  // Find previous display
  LogicalDisplay *previous = nullptr;
  for (auto peek = _firstDisplay; peek; peek = peek->getNext()) {
    if (peek->getDisplayNumber() > displayNumber) {
      break;
    }
    previous = peek;
  }
  if (previous) {
    // If there's a previous display, chain after it
    display->setNext(previous->getNext());
    previous->setNext(display);
  } else {
    // Put at start of list
    display->setNext(_firstDisplay);
    _firstDisplay = display;
  }
  if (!_activeDisplay) {
    _activeDisplay = display;
  }
  _displayCount++;
  return display;
}

LogicalDisplay *PhysicalScreen::getFirstDisplay() { return _firstDisplay; }

void PhysicalScreen::setActiveDisplay(LogicalDisplay *activeDisplay) { _activeDisplay = activeDisplay; }

LogicalDisplay *PhysicalScreen::getActiveDisplay() { return _activeDisplay; }

bool PhysicalScreen::displayNumberExists(uint8_t displayNumber) { return getDisplayByNumber(displayNumber) != nullptr; }

LogicalDisplay *PhysicalScreen::getDisplayByNumber(uint8_t displayNumber) {
  for (auto *display = _firstDisplay; display; display = display->getNext()) {
    if (display->getDisplayNumber() == displayNumber) {
      return display;
    }
  }
  return nullptr;
}

void PhysicalScreen::switchToNextDisplay() {
  if (!_activeDisplay) {
    _activeDisplay = _firstDisplay;
    _activeDisplay->setRedraw(true);
    return;
  }
  if (_displayCount == 1) {
    return;
  }
  if (_activeDisplay->getNext()) {
    _activeDisplay = _activeDisplay->getNext();
  } else {
    _activeDisplay = _firstDisplay;
  }
  _activeDisplay->setRedraw(true);
}

void PhysicalScreen::switchToPreviousDisplay() {
  if (!_activeDisplay) {
    _activeDisplay = _firstDisplay;
    _activeDisplay->setRedraw(true);
    return;
  }
  if (_displayCount == 1) {
    return;
  }
  LogicalDisplay *last = nullptr;
  for (LogicalDisplay *display = _firstDisplay; display; display = display->getNext()) {
    if (!display->getNext()) {
      last = display;
      break;
    }
  }
  if (_activeDisplay == _firstDisplay) {
    _activeDisplay = last;
    _activeDisplay->setRedraw(true);
    return;
  }
  for (LogicalDisplay *display = _firstDisplay; display; display = display->getNext()) {
    if (display->getNext() == _activeDisplay) {
      _activeDisplay = display;
      _activeDisplay->setRedraw(true);
      return;
    }
  }
}

void PhysicalScreen::autoSwitch(unsigned long switchDelay) {
  if (millis() - _lastSwitchTime > switchDelay) {
    _lastSwitchTime = millis();
    switchToNextDisplay();
  }
}

void PhysicalScreen::processActiveDisplay() {
  if (!_activeDisplay)
    return;
  if (_activeDisplay->needsRedraw()) {
    clearScreen(_activeDisplay->getDefaultBackgroundColour());
  }
  for (LogicalDisplayRow *row = _activeDisplay->getFirstRow(); row; row = row->getNext()) {
    if (row->needsRender() && (row->isChanged() || _activeDisplay->needsRedraw())) {
      if (row->isLine()) {
        writeLine(row->getDisplayRow(), 0, _activeDisplay->getMaxRowLength(), row->getTextColour(),
                  row->getBackgroundColour());
      } else {
        writeRow(row->getDisplayRow(), 0, row->getTextColour(), row->getBackgroundColour(),
                 _activeDisplay->getMaxRowLength(), row->getRowText(), row->isUnderlined());
      }
    }
  }
  _activeDisplay->setRedraw(false);
}

uint8_t PhysicalScreen::getScreenNumber() { return _screenNumber; }

uint8_t PhysicalScreen::getMaxRows() { return _maxRows; }

uint8_t PhysicalScreen::getMaxRowLength() { return _maxRowLength; }
