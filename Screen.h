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

#ifndef SCREEN_H
#define SCREEN_H

#include "ScreenRow.h"
#include <Arduino.h>

/// @brief Class for each screen as received from the EXRAIL SCREEN() command
/// Each Screen instance contains a linked list of ScreenRow instances
/// Screen instances are contained in a linked list managed separately by the ScreenManager
class Screen {
public:
  /// @brief Constructor for each Screen instance
  /// @param screenId ID of this screen as set in EXRAIL SCREEN()
  Screen(uint8_t screenId);

  /// @brief Get the ID for this screen instance
  /// @return Screen ID
  uint8_t getId();

  /// @brief Set the next Screen instance in the list
  /// @param screen Pointer to the next Screen instance
  void setNext(Screen *screen);

  /// @brief Get the next Screen instance in the list
  /// @return Pointer to the next Screen instance
  Screen *getNext();

  /// @brief Update the specified ScreenRow, or create it if it doesn't exist
  /// This will automatically maintain the linked list of ScreenRow instances
  /// Setting text to an empty string "" will delete the associated row from the list
  /// @param screenRowId ScreenRow ID
  /// @param text Text to associated with this ScreenRow
  void updateScreenRow(uint8_t screenRowId, const char *text);

  /// @brief Get the first ScreenRow instance in the list
  /// @return Pointer to the first ScreenRow instance
  ScreenRow *getFirstScreenRow();

  /// @brief Get the ScreenRow instance at the specified ID
  /// @param screenRowId ScreenRow ID to retrieve
  /// @return Pointer to the ScreenRow instance at the ID
  ScreenRow *getScreenRowById(uint8_t screenRowId);

  /// @brief Set the Logger instance
  /// @param logger Pointer to the Logger
  void setLogger(Logger *logger);

  /// @brief Destructor for the Screen instance
  /// Will automatically clean up the associated ScreenRow list
  ~Screen();

private:
  uint8_t _screenId;
  Screen *_next;
  ScreenRow *_firstScreenRow;
  Logger *_logger;

  /// @brief Add a new ScreenRow to the list
  /// @param screenRowId ID of the ScreenRow to add
  /// @param text Text for this ScreenRow
  void _addScreenRow(uint8_t screenRowId, const char *text);

  /// @brief Delete the specified ScreenRow and update the list accordingly
  /// @param screenRow Pointer to the ScreenRow instance to delete
  void _deleteScreenRow(ScreenRow *screenRow);
};

#endif // SCREEN_H
