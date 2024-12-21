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
#define LOG_NONE LogLevel::NONE
#define LOG_ERROR LogLevel::ERROR
#define LOG_WARN LogLevel::WARN
#define LOG_INFO LogLevel::INFO
#define LOG_DEBUG LogLevel::DEBUG

#ifndef PIO_UNIT_TESTING // Don't warn or use user config when testing
// Incude user's myConfig.h if it exists.
#if __has_include("myConfig.h")
#include "myConfig.h"
#else
#warning myConfig.h not found, using defaults
#endif // myConfig
#endif // PIO_UNIT_TESTING

// Default log level WARN
#ifndef LOG_LEVEL
#define LOG_LEVEL LOG_WARN
#endif // LOG_LEVEL

#ifndef PIO_UNIT_TESTING // Cannot use these for testing
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

#endif // DEFINES_H
