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

#ifndef DEFINES_H
#define DEFINES_H

// Give log defines their values before user config
#include "Logger.h"
#define LOG_NONE LOG_NONE
#define LOG_ERROR LOG_ERROR
#define LOG_WARN LOG_WARN
#define LOG_INFO LOG_INFO
#define LOG_DEBUG LOG_DEBUG

#ifndef PIO_UNIT_TESTING // Don't warn or use user config when testing
// Incude user's myConfig.h if it exists.
#if __has_include("myConfig.h")
#include "myConfig.h"
#else
#warning myConfig.h not found, using defaults
#endif // myConfig

// Default settings for streams
#ifndef CONSOLE_STREAM
#define CONSOLE_STREAM Serial
#endif // CONSOLE_STREAM
#ifndef COMMANDSTATION_STREAM
#if defined(ARDUINO_ARCH_ESP32)
#define COMMANDSTATION_STREAM Serial2
#else
#define COMMANDSTATION_STREAM Serial
#endif // PLATFORM TYPE
#endif // COMMANDSTATION_STREAM
#endif // PIO_UNIT_TESTING

// Default log level WARN unless overridden
#ifndef LOG_LEVEL
#define LOG_LEVEL LOG_WARN
#endif // LOG_LEVEL

// Default to showing the EX-Display version for 2 seconds unless overridden
#ifndef STARTUP_INFO_DELAY
#define STARTUP_INFO_DELAY 3000
#endif // STARTUP_INFO_DELAY

#endif // DEFINES_H
