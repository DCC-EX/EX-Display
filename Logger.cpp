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

#include "Logger.h"

Logger::Logger(Stream *outputStream) : _outputStream(outputStream), _currentLevel(LogLevel::WARN) {}

void Logger::setLogLevel(LogLevel logLevel) { _currentLevel = logLevel; }

LogLevel Logger::getLogLevel() { return _currentLevel; }

void Logger::log(LogLevel logLevel, const char *format, ...) {
  if (logLevel <= _currentLevel) {
    // Setup the prefix
    const char *prefix;
    switch (logLevel) {
    case LogLevel::MESSAGE:
      prefix = "[MESSAGE] ";
      break;
    case LogLevel::ERROR:
      prefix = "[ERROR] ";
      break;
    case LogLevel::WARN:
      prefix = "[WARN] ";
      break;
    case LogLevel::INFO:
      prefix = "[INFO] ";
      break;
    case LogLevel::DEBUG:
      prefix = "[DEBUG] ";
      break;
    default:
      prefix = "";
      break;
    }

    // Calculate buffer size from args + prefix
    va_list args;
    va_start(args, format);
    // Get size of string + null terminator
    int size = vsnprintf(nullptr, 0, format, args) + 1;
    // End args processing
    va_end(args);

    // Allocate buffer including prefix size
    size_t totalSize = size + strlen(prefix);
    char *buffer = new char[totalSize];

    if (buffer == nullptr) {
      _outputStream->println("[ERROR] Logger::log memory allocation failed");
      return;
    }

    // Copy prefix to buffer
    strcpy(buffer, prefix);

    // Start args processing
    va_start(args, format);
    // Get the string into the buffer after the prefix
    vsnprintf(buffer + strlen(prefix), size, format, args);
    // End args processing
    va_end(args);

    // Output formatted message
    _outputStream->println(buffer);

    // Clean up
    delete[] buffer;
  }
}
