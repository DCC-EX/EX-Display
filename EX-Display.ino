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

#ifndef PIO_UNIT_TESTING

#include "Configurator.h"

Configurator configurator(&CONSOLE_STREAM, &COMMANDSTATION_STREAM, LOG_LEVEL);

void setup() {
  CONSOLE_STREAM.begin(115200);
  COMMANDSTATION_STREAM.begin(115200);
  configurator.initialise();
}

void loop() {
  Controller *controller = configurator.getController();
  controller->update();
}

#endif // PIO_UNIT_TEST
