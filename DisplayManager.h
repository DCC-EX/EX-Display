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

#ifndef DISPLAYMANAGER_H
#define DISPLAYMANAGER_H

#include "DisplayInterface.h"
#include "Logger.h"

/// @brief Manages all physical displays
class DisplayManager {
public:
  /// @brief Constructor for the DisplayManager
  DisplayManager();

  /// @brief Add a DisplayInterface derived instance to the list of displays
  /// @param display Pointer to the instance to add
  void addDisplay(DisplayInterface *display);

  /// @brief Parses the displays configured in myConfig.h and creates the list of displays
  void createDisplayList();

  /// @brief Get the first DisplayInterface derived instance in the list of displays
  /// @return Pointer to the first instance
  DisplayInterface *getFirstDisplay();

  /// @brief Set the Logger instance
  /// @param logger Pointer to the Logger
  void setLogger(Logger *logger);

  /// @brief Destructor for the DisplayManager
  ~DisplayManager();

private:
  DisplayInterface *_firstDisplay;
  Logger *_logger;
  uint8_t _nextDisplayId;
};

#endif // DISPLAYMANAGER_H
