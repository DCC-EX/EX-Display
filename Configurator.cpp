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
  _screenManager = new ScreenManager();
  _controller = new Controller(_consoleStream, _commandStationStream, _logger);
}

void Configurator::initialise() {
  AtFinder::setup(100, _controller);
  AtFinder::setLogger(_logger);
  _consoleStream->print("EX-Display version ");
  _consoleStream->println(VERSION);
}

Stream *Configurator::getConsoleStream() { return _consoleStream; }

Stream *Configurator::getCommandStationStream() { return _commandStationStream; }

Logger *Configurator::getLogger() { return _logger; }

ScreenManager *Configurator::getScreenManager() { return _screenManager; }

Controller *Configurator::getController() { return _controller; }

Configurator::~Configurator() {
  delete _controller;
  delete _screenManager;
  delete _logger;
  _controller = nullptr;
  _screenManager = nullptr;
  _logger = nullptr;
}
