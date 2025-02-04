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

#ifndef LOGGER_H
#define LOGGER_H

#include <Arduino.h>

/// @brief Macro for shorter logging calls, assumes a pointer to a Logger instance called _logger
/// LOG(LogLevel, "Message");
#define LOG(level, ...)                                                                                                \
  if (_logger)                                                                                                         \
  _logger->log(level, __VA_ARGS__)

/// @brief Define valid log levels in ascending order
enum LogLevel { LOG_MESSAGE, LOG_NONE, LOG_ERROR, LOG_WARN, LOG_INFO, LOG_DEBUG };

/// @brief Class to enable simple logging to a Stream object with different log levels
/// This enables embedding permanent error, warn, info, and debug messages in the software, with the user defining the
/// log level at compile time if more diagnostics are required
class Logger {
public:
  /// @brief Constructor for the logger
  /// @param outputStream Pointer to a Stream instance to output log messages to (eg. Logger(&Serial);)
  Logger(Stream *outputStream);

  /// @brief Set the log level
  /// @param logLevel Valid LogLevel
  void setLogLevel(LogLevel logLevel);

  /// @brief Get the current log level
  /// @return LogLevel
  LogLevel getLogLevel();

  /// @brief Log a message for the specified log level
  /// @param logLevel Valid LogLevel
  /// @param format Format to apply to the message
  void log(LogLevel logLevel, const char *format, ...);

private:
  Stream *_outputStream;
  LogLevel _currentLevel;
};

#endif // LOGGER_H
