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

#ifndef SCREENROW_H
#define SCREENROW_H

#include "Logger.h"
#include <Arduino.h>

class ScreenRow {
public:
  /// @brief Constructor for each ScreenRow instance
  /// @param screenRowId ID of this ScreenRow
  ScreenRow(uint8_t screenRowId);

  /// @brief Get the ID of this ScreenRow
  /// @return ID of this ScreenRow
  uint8_t getId();

  /// @brief Set the next ScreenRow instance in the list
  /// @param screenRow Pointer to the next ScreenRow instance
  void setNext(ScreenRow *screenRow);

  /// @brief Get the next ScreenRow instance in the list
  /// @return Pointer to the next ScreenRow instance
  ScreenRow *getNext();

  /// @brief Set the text associated with this ScreenRow
  /// @param text Text for this ScreenRow
  void setText(const char *text);

  /// @brief Get the text associated with this ScreenRow
  /// @return Text for this ScreenRow
  const char *getText();

  /// @brief Set the Logger instance
  /// @param logger Pointer to the Logger
  void setLogger(Logger *logger);

  /// @brief Test if this row needs to be redrawn
  /// @return true|false
  bool needsRedraw();

  /// @brief Destructor for each ScreenRow instance
  ~ScreenRow();

private:
  uint8_t _screenRowId;
  char *_text;
  ScreenRow *_next;
  Logger *_logger;
  bool _needsRedraw;
};

#endif // SCREENROW_H
