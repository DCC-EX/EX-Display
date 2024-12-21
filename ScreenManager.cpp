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

#include "ScreenManager.h"

ScreenManager::ScreenManager() : _firstScreen(nullptr), _logger(nullptr) {}

Screen *ScreenManager::addScreen(uint8_t screenId) {
  // If the screen doesn't exist, create and add to list
  LOG(LogLevel::DEBUG, "ScreenManager::addScreen(%d)", screenId);
  if (getScreenById(screenId) == nullptr) {
    Screen *newScreen = new Screen(screenId);
    if (_logger != nullptr) {
      newScreen->setLogger(_logger);
    }
    // Make it the first one if we don't already have a first
    if (_firstScreen == nullptr) {
      _firstScreen = newScreen;
      return newScreen;
    }
    Screen *screen = _firstScreen;
    while (screen->getNext() != nullptr) {
      screen = screen->getNext();
    }
    screen->setNext(newScreen);
    return newScreen;
  } else {
    return getScreenById(screenId);
  }
}

Screen *ScreenManager::getFirstScreen() { return _firstScreen; }

Screen *ScreenManager::getScreenById(uint8_t screenId) {
  if (_firstScreen == nullptr) {
    return nullptr;
  }
  for (Screen *screen = _firstScreen; screen; screen = screen->getNext()) {
    if (screen->getId() == screenId) {
      return screen;
    }
  }
  return nullptr;
}

void ScreenManager::setLogger(Logger *logger) { _logger = logger; }

ScreenManager::~ScreenManager() {
  if (_firstScreen != nullptr) {
    Screen *screen = _firstScreen;
    Screen *next = nullptr;
    while (screen) {
      next = screen->getNext();
      delete screen;
      screen = next;
    }
    _firstScreen = nullptr;
  }
}
