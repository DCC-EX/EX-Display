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

#ifndef CONFIGURATOR_H
#define CONFIGURATOR_H

#include "Controller.h"
#include "Defines.h"
#include "Logger.h"
#include "ScreenManager.h"

class Configurator {
public:
  /// @brief Constructor for this Configurator
  /// @param consoleStream Pointer to the Stream for console interaction
  /// @param commandStationStream Pointer to the Stream for the CommandStation connection
  /// @param logLevel LogLevel to set (default WARN)
  Configurator(Stream *consoleStream, Stream *commandStationStream, LogLevel logLevel = LogLevel::WARN);

  /// @brief Call all one-shot initialisation or begin methods on startup
  void initialise();

  /// @brief Get the console Stream instance for this configurator
  /// @return Pointer to the Stream
  Stream *getConsoleStream();

  /// @brief Get the CommandStation connection Stream instance for this configurator
  /// @return Pointer to the Stream
  Stream *getCommandStationStream();

  /// @brief Get the Logger instance for this Configurator
  /// @return Pointer to the Logger
  Logger *getLogger();

  /// @brief Get the Controller instance for this Configurator
  /// @return Pointer to the Controller
  Controller *getController();

  /// @brief Destructor for the Configurator
  ~Configurator();

private:
  Stream *_consoleStream;
  Stream *_commandStationStream;
  Logger *_logger;
  Controller *_controller;
};

#endif // CONFIGURATOR_H
