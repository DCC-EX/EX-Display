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

#include "AtFinder.h"
#include "Controller.h"

Controller::Controller(Stream *consoleStream, Stream *commandStationStream, DisplayManager *displayManager,
                       ScreenManager *screenManager, Logger *logger)
    : _consoleStream(consoleStream), _commandStationStream(commandStationStream), _displayManager(displayManager),
      _screenManager(screenManager) {
  _logger = logger;
}

void Controller::update() {
  if (_commandStationStream != nullptr && _commandStationStream->available()) {
    char csChar = _commandStationStream->read();
    AtFinder::processInputChar(csChar);
  }
  if (_consoleStream != nullptr && _consoleStream->available()) {
    char consoleChar = _consoleStream->read();
    AtFinder::processInputChar(consoleChar);
  }
  if (_displayManager != nullptr && _screenManager != nullptr) {
    for (auto *display = _displayManager->getFirstDisplay(); display; display = display->getNext()) {
      Screen *screen = _screenManager->getScreenById(display->getScreenId());
      for (ScreenRow *row = screen->getFirstScreenRow(); row; row = row->getNext()) {
        if (row->needsRedraw()) {
          display->displayRow(row->getId(), row->getText());
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

void Controller::onInputAction(InputAction action) { LOG(LogLevel::DEBUG, "Controller::onInputAction(%d)", action); }

Controller::~Controller() {
  _displayManager = nullptr;
  _screenManager = nullptr;
  _consoleStream = nullptr;
  _commandStationStream = nullptr;
  _logger = nullptr;
}
