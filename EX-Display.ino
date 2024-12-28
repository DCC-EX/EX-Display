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

/**
 * @mainpage EX-Display - a project for multiple displays connected to EX-CommandStation
 *
 * @section intro_sec Introduction
 * EX-Display enables one or more displays to be connected to EX-CommandStation via a serial connection, and emulating 
 * JMRI's virtual screen capability.
 * 
 * @section Details
 */

#ifndef PIO_UNIT_TESTING

#include "Configurator.h"

/// @brief Create the Configurator instance to configure EX-Display
/// @param console Pointer to the console stream - defaults to Serial, customise in myConfig.h
/// @param commandStation Pointer to the CommandStation connection stream - default depends on platform, customise in
/// myConfig.h
/// @param logLevel Sets the log level for the application - defaults to WARN, customise in myConfig.h
Configurator *configurator = new Configurator(&CONSOLE_STREAM, &COMMANDSTATION_STREAM, LOG_LEVEL);

/// @brief Main setup method, initialise Configurator here
void setup() {
  CONSOLE_STREAM.begin(115200);
  COMMANDSTATION_STREAM.begin(115200);
  configurator->initialise();
  Controller *controller = configurator->getController();
  controller->begin();
}

/// @brief Main loop, simply calls controller->update() to manage all interactions
void loop() {
  Controller *controller = configurator->getController();
  controller->update();
}

#endif // PIO_UNIT_TEST
