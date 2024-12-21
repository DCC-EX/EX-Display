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

Screen *ScreenManager::updateScreen(uint8_t screenId) {
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

Screen *ScreenManager::getPreviousScreen(Screen *screen) {
  // If there is no screen, nullptr
  if (_firstScreen == nullptr) {
    return nullptr;
  }
  // If there's only one screen, that's the one
  if (_firstScreen->getNext() == nullptr) {
    return _firstScreen;
  }
  // If this is the lowest numbered screen, wrap to highest as previous
  if (screen->getId() == getMinScreenId()) {
    return getScreenById(getMaxScreenId());
  }
  // Otherwise we need to find it
  // Iterate descending through all screens by ID, starting from provided screen -1
  uint8_t minId = getMinScreenId();
  uint8_t maxId = screen->getId() - 1;
  for (uint8_t i = maxId; i >= minId; i--) {
    Screen *testScreen = getScreenById(i);
    // If there's a screen at this ID, it must be the previous, return it
    if (testScreen != nullptr) {
      return testScreen;
    }
  }
  return nullptr;
}

Screen *ScreenManager::getNextScreen(Screen *screen) {
  // If there is no screen, nullptr
  if (_firstScreen == nullptr) {
    return nullptr;
  }
  // If there's only one screen, that's the one
  if (_firstScreen->getNext() == nullptr) {
    return _firstScreen;
  }
  // If this is the highest numbered screen, wrap to lowest as next
  if (screen->getId() == getMaxScreenId()) {
    return getScreenById(getMinScreenId());
  }
  // Otherwise we need to find it
  // Iterate through all screens by ID, starting from provided screen +1
  uint8_t minId = screen->getId() + 1;
  uint8_t maxId = getMaxScreenId();
  for (uint8_t i = minId; i <= maxId; i++) {
    Screen *testScreen = getScreenById(i);
    // If there's a screen at this ID, it must be the next, return it
    if (testScreen != nullptr) {
      return testScreen;
    }
  }
  return nullptr;
}

uint8_t ScreenManager::getMinScreenId() {
  if (_firstScreen == nullptr) {
    return 0;
  }
  uint8_t screenId = _firstScreen->getId();
  for (Screen *screen = _firstScreen; screen; screen = screen->getNext()) {
    if (screen->getId() < screenId) {
      screenId = screen->getId();
    }
  }
  return screenId;
}

uint8_t ScreenManager::getMaxScreenId() {
  if (_firstScreen == nullptr) {
    return 0;
  }
  uint8_t screenId = _firstScreen->getId();
  for (Screen *screen = _firstScreen; screen; screen = screen->getNext()) {
    if (screen->getId() > screenId) {
      screenId = screen->getId();
    }
  }
  return screenId;
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
