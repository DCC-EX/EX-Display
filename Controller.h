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

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "CallbackInterface.h"
#include "DisplayManager.h"
#include "Logger.h"
#include "ScreenManager.h"
#include <Arduino.h>

/// @brief Class for the central controller for EX-Display
/// All application activities are controlled through this class to manage screens, displays, and user input
class Controller : public CallbackInterface {
public:
  /// @brief Constructor for the Controller
  Controller(Stream *consoleStream, Stream *commandStationStream, DisplayManager *displayManager, Logger *logger);

  /// @brief Processes all ongoing activities, monitoring streams, receiving user input, updates displays, etc.
  /// Call at least once per main loop iteration
  void update();

  /// @brief Method to implement updating a screen
  /// @param screenId ID of the screen to update
  /// @param row Row number to update
  /// @param text Text to update
  void updateScreen(uint8_t screenId, uint8_t row, const char *text) override;

  /// @brief Method to implement to respond to an input action
  /// @param action PRESS_UP, PRESS_DOWN, PRESS_LEFT, PRESS_RIGHT, PRESS_CENTRE
  void onInputAction(InputAction action) override;

  /// @brief Destructor for the Controller
  ~Controller() override;

private:
  Stream *_consoleStream;
  Stream *_commandStationStream;
  DisplayManager *_displayManager;
  Logger *_logger;
  ScreenManager *_screenManager;
};

#endif // CONTROLLER_H
