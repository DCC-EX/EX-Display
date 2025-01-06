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
#include "InputManager.h"
#include "Logger.h"
#include "ScreenManager.h"
#include <Arduino.h>

/// @brief Class for the central controller for EX-Display.
/// All application activities are controlled through this class to manage screens, displays, and user input. All
/// devices have their begin or init type methods called from Controller::begin().
class Controller : public CallbackInterface {
public:
  /// @brief Constructor for this Controller
  /// @param consoleStream Pointer to the Stream for console interactions and log output
  /// @param commandStationStream Pointer to the incoming Stream connected to EX-CommandStation
  /// @param displayManager Pointer to the DisplayManager instance
  /// @param inputManager Pointer to the InputManager instance
  /// @param screenManager Pointer to the ScreenManager instance
  /// @param logger Pointer to the Logger instance
  /// @param pauseDisplayUpdatesUntil Time in milliseconds the EX-Display version will be displayed until
  Controller(Stream *consoleStream, Stream *commandStationStream, DisplayManager *displayManager,
             InputManager *inputManager, ScreenManager *screenManager, Logger *logger,
             unsigned long pauseDisplayUpdatesUntil = 0);

  /// @brief Call once to start displays and input
  void begin();

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
  InputManager *_inputManager;
  ScreenManager *_screenManager;
  unsigned long _pauseDisplayUpdatesUntil;
  bool _pauseDisplayUpdates;

  /// @brief Selects the previous screen for the selected display
  /// @param display Pointer to the DisplayInterface to set
  void _selectPreviousScreen(DisplayInterface *display);

  /// @brief Selects the next screen for the selected display
  /// @param display Pointer to the DisplayInterface to set
  void _selectNextScreen(DisplayInterface *display);
};

#endif // CONTROLLER_H
