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

#include "Configurator.h"
#include "AtFinder.h"
#include "Version.h"

Configurator::Configurator(Stream *consoleStream, Stream *commandStationStream, LogLevel logLevel)
    : _consoleStream(consoleStream), _commandStationStream(commandStationStream) {
  _logger = new Logger(_consoleStream);
  _logger->setLogLevel(logLevel);
  _displayManager = new DisplayManager();
  _displayManager->setLogger(_logger);
  _inputManager = new InputManager();
  _screenManager = new ScreenManager();
  _screenManager->setLogger(_logger);
  unsigned long pauseDisplayUpdates = STARTUP_INFO_DELAY + millis();
  _controller = new Controller(_consoleStream, _commandStationStream, _displayManager, _screenManager, _logger,
                               pauseDisplayUpdates);
}

void Configurator::initialise() {
  AtFinder::setup(100, _controller);
  AtFinder::setLogger(_logger);
  _displayManager->createDisplayList();
  _displayManager->startDisplays();
  _inputManager->createInput();
  _inputManager->startInput();
  LOG(LogLevel::MESSAGE, "EX-Display version %s", VERSION);
  _displayManager->displayStartupInfo(VERSION);
}

Stream *Configurator::getConsoleStream() { return _consoleStream; }

Stream *Configurator::getCommandStationStream() { return _commandStationStream; }

Logger *Configurator::getLogger() { return _logger; }

Controller *Configurator::getController() { return _controller; }

DisplayManager *Configurator::getDisplayManager() { return _displayManager; }

InputManager *Configurator::getInputManager() { return _inputManager; }

ScreenManager *Configurator::getScreenManager() { return _screenManager; }

Configurator::~Configurator() {
  AtFinder::cleanUp();
  delete _controller;
  delete _logger;
  delete _displayManager;
  delete _inputManager;
  delete _screenManager;
  _controller = nullptr;
  _logger = nullptr;
  _displayManager = nullptr;
  _screenManager = nullptr;
}
