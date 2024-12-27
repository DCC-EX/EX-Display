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

#include "Controller.h"
#include "AtFinder.h"
#include "Version.h"

Controller::Controller(Stream *consoleStream, Stream *commandStationStream, DisplayManager *displayManager,
                       InputManager *inputManager, ScreenManager *screenManager, Logger *logger,
                       unsigned long pauseDisplayUpdatesUntil)
    : _consoleStream(consoleStream), _commandStationStream(commandStationStream), _displayManager(displayManager),
      _inputManager(inputManager), _screenManager(screenManager), _pauseDisplayUpdatesUntil(pauseDisplayUpdatesUntil) {
  _logger = logger;
  if (_pauseDisplayUpdatesUntil > 0) {
    _pauseDisplayUpdates = true;
  } else {
    _pauseDisplayUpdates = false;
  }
}

void Controller::begin() {
  _displayManager->startDisplays(); // Start displays
  _inputManager->startInput();      // Start input
  LOG(LogLevel::MESSAGE, "EX-Display version %s", VERSION);
  _displayManager->displayStartupInfo(VERSION); // Display version info
}

void Controller::update() {
  // If the stream from the CommandStation is valid and has data, send it through AtFinder
  if (_commandStationStream != nullptr && _commandStationStream->available()) {
    char csChar = _commandStationStream->read();
    AtFinder::processInputChar(csChar);
  }
  // If the stream from the console is valid and has data, send it through AtFinder
  if (_consoleStream != nullptr && _consoleStream->available()) {
    char consoleChar = _consoleStream->read();
    AtFinder::processInputChar(consoleChar);
  }
  // On startup, EX-Display version is displayed, this ensures it remains on screen until the elapsed time set by the
  // Configurator
  // When the time has passed, turn the pause of and clear each display to enable normal display operation
  if (_pauseDisplayUpdates && millis() > _pauseDisplayUpdatesUntil) {
    LOG(LogLevel::DEBUG, "_pauseDisplayUpdatesUntil time exceeded, resume display updates");
    _pauseDisplayUpdatesUntil = 0;
    _pauseDisplayUpdates = false;
    for (auto *display = _displayManager->getFirstDisplay(); display; display = display->getNext()) {
      display->clearScreen();
    }
  }

  // Process user input provided there is a valid InputManager and InputInterface
  bool isCalibrating = false; // Set up the calibrating flag to avoid display updates if in progress
  if (_inputManager != nullptr) {
    auto *input = _inputManager->getInput();
    if (input) {
      // Poll the InputInterface's check method for user input actions
      isCalibrating = input->isCalibrating();
      input->check();
    }
  }

  // Only process displays if there is a valid DisplayManager and ScreenManager, and any input is not calibrating
  if (_displayManager != nullptr && _screenManager != nullptr && !_pauseDisplayUpdates && !isCalibrating) {
    // Iterate through each physical display, auto means we don't care about the type as we're using the interface
    for (auto *display = _displayManager->getFirstDisplay(); display; display = display->getNext()) {
      // If the screen ID is invalid, set it to the first screen ID if there is one, otherwise continue to next display
      if (display->getScreenId() == -1) {
        if (_screenManager->getFirstScreen() == nullptr) {
          continue;
        }
        display->setScreenId(_screenManager->getFirstScreen()->getId());
      }
      // Get the screen for this display if it exists, otherwise continue to next display
      Screen *screen = _screenManager->getScreenById(display->getScreenId());
      if (screen == nullptr) {
        continue;
      }
      // Display the rows needing to be updated
      for (ScreenRow *row = screen->getFirstScreenRow(); row; row = row->getNext()) {
        if (row->needsRedraw()) {
          display->displayRow(row->getId(), row->getText(), false, 0);
        }
      }
    }
  }
}

void Controller::updateScreen(uint8_t screenId, uint8_t row, const char *text) {
  LOG(LogLevel::DEBUG, "Controller::updateScreen(%d, %d, %s)", screenId, row, text);
  if (_screenManager == nullptr) {
    LOG(LogLevel::DEBUG, "Controller::_screenManager == nullptr");
    return;
  }
  Screen *screen = _screenManager->updateScreen(screenId);
  if (screen != nullptr) {
    screen->updateScreenRow(row, text);
  }
}

void Controller::onInputAction(InputAction action) {
  // No inputs are valid if there are no displays or screens, so just bail out
  if (_displayManager == nullptr || _screenManager == nullptr || _displayManager->getFirstDisplay() == nullptr ||
      _screenManager->getFirstScreen() == nullptr) {
    return;
  }
  auto *display = _displayManager->getFirstDisplay();
  switch (action) {
  // Left press selects the previous screen for display
  case InputAction::PRESS_LEFT: {
    LOG(LogLevel::DEBUG, "Controller::onInputAction(InputAction::PRESS_LEFT)");
    _selectPreviousScreen(display);
    break;
  }
  // Right press selects the next screen for display
  case InputAction::PRESS_RIGHT: {
    LOG(LogLevel::DEBUG, "Controller::onInputAction(InputAction::PRESS_RIGHT)");
    _selectNextScreen(display);
    break;
  }
  // Up scrolls the screen up one row
  case InputAction::PRESS_UP: {
    LOG(LogLevel::DEBUG, "Controller::onInputAction(InputAction::PRESS_UP)");
    break;
  }
  // Down scrolls the screen down one row
  case InputAction::PRESS_DOWN: {
    LOG(LogLevel::DEBUG, "Controller::onInputAction(InputAction::PRESS_DOWN)");
    break;
  }
  // Centre moves input control to the next display - does nothing until multiple displays are supported
  case InputAction::PRESS_CENTRE: {
    LOG(LogLevel::DEBUG, "Controller::onInputAction(InputAction::PRESS_CENTRE)");
    break;
  }
  default: {
    LOG(LogLevel::DEBUG, "Controller::onInputAction(Unknown)");
    break;
  }
  }
}

Controller::~Controller() {
  _displayManager = nullptr;
  _screenManager = nullptr;
  _consoleStream = nullptr;
  _commandStationStream = nullptr;
  _logger = nullptr;
}

void Controller::_selectPreviousScreen(DisplayInterface *display) {
  // If screen ID is invalid, select the first screen
  int screenId = display->getScreenId();
  int previousId = -1;
  if (screenId == -1) {
    previousId = _screenManager->getFirstScreen()->getId();
  } else {
    // Otherwise get the ID of the previous screen and update it
    Screen *screen = _screenManager->getScreenById(screenId);
    previousId = _screenManager->getPreviousScreen(screen)->getId();
  }
  display->setScreenId(previousId);
  LOG(LogLevel::DEBUG, "Controller::_selectPreviousScreen: _displayId=%d|screenId=%d|previousId=%d", display->getId(),
      screenId, previousId);
}

void Controller::_selectNextScreen(DisplayInterface *display) {
  // If screen ID is invalid, select the first screen
  int screenId = display->getScreenId();
  int nextId = -1;
  if (screenId == -1) {
    nextId = _screenManager->getFirstScreen()->getId();
  } else {
    // Otherwise get the ID of the next screen and update it
    Screen *screen = _screenManager->getScreenById(screenId);
    nextId = _screenManager->getNextScreen(screen)->getId();
  }
  display->setScreenId(nextId);
  LOG(LogLevel::DEBUG, "Controller::_selectPreviousScreen: _displayId=%d|screenId=%d|nextId=%d", display->getId(),
      screenId, nextId);
}
