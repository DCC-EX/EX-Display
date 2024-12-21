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

#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

#include "Screen.h"

/// @brief Class to manage all EX-Display screens
class ScreenManager {
public:
  /// @brief Constructor for the ScreenManager
  ScreenManager();

  /// @brief Add a new Screen
  /// @param screenId ID of the Screen
  void addScreen(uint8_t screenId);

  /// @brief Get the first Screen instance in the list
  /// @return Pointer to the first Screen instance
  Screen *getFirstScreen();

  /// @brief Get the Screen with the specified ID
  /// @param screenId ID of the Screen instance to retrieve
  /// @return Pointer to the Screen instance
  Screen *getScreenById(uint8_t screenId);

  /// @brief Set the Logger instance
  /// @param logger Pointer to the Logger
  void setLogger(Logger *logger);

  /// @brief Destructor for the ScreenManager
  ~ScreenManager();

private:
  Screen *_firstScreen;
  Logger *_logger;
};

#endif // SCREENMANAGER_H
