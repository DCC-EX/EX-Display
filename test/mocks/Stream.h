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

#ifndef STREAM_H
#define STREAM_H

#include <gmock/gmock.h>
#include <string>

/// @brief Class to mock the basic Stream function equivalent of the Arduino framework
class Stream {
public:
  // Output buffer
  std::string buffer;

  /// @brief Print method
  /// @param string String to print
  void print(const std::string &string) {
    buffer += string.c_str(); // Append to buffer
  }

  /// @brief Println method
  /// @param string String to print
  void println(const std::string &string) {
    buffer += string.c_str(); // Append to buffer
    buffer += "\r\n";         // Add newline
  }

  /// @brief Clear the buffer
  void clear() { buffer.clear(); }
};

#endif // STREAM_H
