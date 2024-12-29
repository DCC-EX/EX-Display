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

#include "DisplayManager.h"
#ifndef PIO_UNIT_TESTING // Cannot create physical displays with Platform IO testing
#include "TFT_eSPIDisplay.h"
#endif // PIO_UNIT_TESTING

DisplayManager::DisplayManager() : _firstDisplay(nullptr), _logger(nullptr), _nextDisplayId(0) {}

void DisplayManager::addDisplay(DisplayInterface *display) {
  LOG(LogLevel::DEBUG, "DisplayManager::addDisplay()");
  if (display == nullptr) {
    return;
  }
  display->setId(_nextDisplayId++);
  if (_logger != nullptr) {
    display->setLogger(_logger);
  }
  if (_firstDisplay == nullptr) {
    _firstDisplay = display;
    return;
  }
  DisplayInterface *current = _firstDisplay;
  while (current->getNext() != nullptr) {
    current = current->getNext();
  }
  current->setNext(display);
}

void DisplayManager::createDisplays() {
#ifndef PIO_UNIT_TESTING // Cannot create physical displays with Platform IO testing
  TFT_eSPIDisplay *tft = new TFT_eSPIDisplay(1, 1, TFT_WHITE, TFT_BLACK);
  addDisplay(tft);
#endif // PIO_UNIT_TESTING
}

void DisplayManager::startDisplays() {
  LOG(LogLevel::DEBUG, "DisplayManager::startDisplays()");
  if (_firstDisplay == nullptr) {
    return;
  }
  for (auto *display = _firstDisplay; display; display = display->getNext()) {
    display->begin();
  }
}

void DisplayManager::displayStartupInfo(const char *version) {
  LOG(LogLevel::DEBUG, "DisplayManager::displayStartupInfo(%s)", version);
  // Do nothing if we don't have a DisplayManager or any displays
  if (_firstDisplay == nullptr) {
    return;
  }
  for (auto *display = _firstDisplay; display; display = display->getNext()) {
    // Select this SPI display if necessary
    _selectSPIDisplay(display);
    display->displayStartupInfo(version);
    // Deselect this SPI display if necessary
    _deselectSPIDisplay(display);
  }
}

void DisplayManager::update(ScreenManager *screenManager) {
  // Do nothing if there is no ScreenManager with Screen info
  if (screenManager == nullptr) {
    return;
  }
  // Iterate through each display
  for (auto *display = _firstDisplay; display; display = display->getNext()) {
    // Select this SPI display if necessary
    _selectSPIDisplay(display);
    // If the screen ID for this display is invalid, default to the same ID
    int screenId = display->getScreenId();
    if (screenId == -1) {
      screenId = display->getId();
      display->setScreenId(screenId);
    }
    // Get the current screen for this display
    Screen *screen = screenManager->getScreenById(screenId);
    // If there is one, display the rows
    if (screen) {
      // If this display needs redrawing, clear first then process rows
      // Must set a local redraw flag here so we can clear the instance for next time
      bool redraw = display->needsRedraw();
      if (redraw) {
        display->clearScreen();
      }
      for (ScreenRow *row = screen->getFirstScreenRow(); row; row = row->getNext()) {
        if (row->needsRedraw() || redraw) {
          display->displayRow(row->getId(), row->getText(), false, 0);
        }
      }
      // Now we've redrawn, clear the flag
      display->setNeedsRedraw(false);
    }
    // Deselect this SPI display if necessary
    _deselectSPIDisplay(display);
  }
}

DisplayInterface *DisplayManager::getFirstDisplay() { return _firstDisplay; }

DisplayInterface *DisplayManager::getDisplayById(uint8_t displayId) {
  for (DisplayInterface *display = _firstDisplay; display; display = display->getNext()) {
    if (display->getId() == displayId) {
      return display;
    }
  }
  return nullptr;
}

void DisplayManager::setLogger(Logger *logger) { _logger = logger; }

DisplayManager::~DisplayManager() {
  if (_firstDisplay != nullptr) {
    DisplayInterface *display = _firstDisplay;
    DisplayInterface *next = nullptr;
    while (display) {
      next = display->getNext();
      delete display;
      display = next;
    }
    _firstDisplay = nullptr;
  }
  _logger = nullptr;
}

void DisplayManager::_selectSPIDisplay(DisplayInterface *display) {
  // If not set, don't do anything
  if (display->getCSPin() == -1) {
    return;
  }
  // Otherwise set CS pin low to select this screen
  digitalWrite(display->getCSPin(), LOW);
}

void DisplayManager::_deselectSPIDisplay(DisplayInterface *display) {
  // If not set, don't do anything
  if (display->getCSPin() == -1) {
    return;
  }
  // Otherwise set CS pin high to deselect this screen
  digitalWrite(display->getCSPin(), HIGH);
}
