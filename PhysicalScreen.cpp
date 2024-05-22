#include "Defines.h"
#include "PhysicalScreen.h"
#include <Arduino.h>

PhysicalScreen::PhysicalScreen() {
  _firstDisplay = nullptr;
  _activeDisplay = nullptr;
  _displayCount = 0;
  _lastSwitchTime = 0;
  _maxRows = 0;
  _maxRowLength = 0;
}

void PhysicalScreen::addDisplay(uint8_t displayNumber, uint16_t defaultTextColour, uint16_t defaultBackgroundColour) {
  
}

LogicalDisplay *PhysicalScreen::getFirstDisplay() { return _firstDisplay; }

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
  for (LogicalDisplay *display = _activeDisplay; display; display = display->getNext()) {
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
