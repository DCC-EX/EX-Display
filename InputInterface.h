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

#ifndef INPUTINTERFACE_H
#define INPUTINTERFACE_H

#include "CallbackInterface.h"
#include "DisplayInterface.h"
#include "InputActions.h"
#include "Logger.h"

/// @brief Class to abstract away all physical input implementatio to enable multiple input types
/// Default return should be PRESS_NONE
class InputInterface {
public:
  /// @brief Perform any initial once off setup or configuration here and call only once
  virtual void begin() = 0;

  /// @brief Call this method at least once per main loop to monitor for input actions
  /// Any actions should call the callback set in the _callback attribute
  virtual void check() = 0;

  /// @brief Set the instance for callbacks when users trigger an input action
  /// @param callback Class instance derived from the CallbackInterface class
  /// Must call the method onInputAction(InputAction);
  void setCallback(CallbackInterface *callback);

  /// @brief Set the logger instance to use for diagnostic logging
  /// @param logger Pointer to the Logger instance to use
  void setLogger(Logger *logger);

  /// @brief Test if this InputInterface is undergoing calibration as required by touch screens
  /// @return true|false
  bool isCalibrating();

  /// @brief Test if this InputInterface requires a display instance - needed for TFT_eSPI as it shares the instance
  /// @return Display ID of the required display - -1 if not required
  int needsDisplay();

  /// @brief Set the DisplayInterface for this input if required
  /// @param display Pointer to the DisplayInterface
  void setDisplay(DisplayInterface *display);

  /// @brief Set the debounce delay
  /// @param delay Debounce delay in milliseconds (default 50ms)
  void setDebounceDelay(unsigned long delay);

  /// @brief Set the threshold for detecting an input is held
  /// @param threshold Threshold in milliseconds (default 500ms)
  void setHoldThreshold(unsigned long threshold);

  /// @brief Destructor for an InputInterface
  virtual ~InputInterface() = default;

protected:
  /// @brief Pointer to the instance for callbacks
  /// Must implement updateScreen() and onInputAction() methods
  CallbackInterface *_callback = nullptr;
  /// @brief Pointer to the Logger instance for derived classes to use
  Logger *_logger = nullptr;
  /// @brief Flag if the input interface is undergoing calibration - needed for touch screens
  bool _isCalibrating = false;
  /// @brief Display ID if this input interface requires a display instance - needed for TFT_eSPI as it shares the
  /// instance
  int _needsDisplay = -1;
  /// @brief Pointer to the DisplayInterface if this input requires it
  DisplayInterface *_display = nullptr;
  /// @brief Time of the last debounce
  unsigned long _lastDebounceTime = 0;
  /// @brief Inputs must remain constant for this amount of time to be valid
  unsigned long _debounceDelay = 50;
  /// @brief Inputs constant for longer than this threshold change from PRESS to HOLD
  unsigned long _holdThreshold = 500;
  /// @brief Set initial InputAction for comparisons in determining debounce or hold
  InputAction _lastAction = InputAction::PRESS_NONE;
  /// @brief Flag to help determining if input is held
  bool _isHolding = false;

  /// @brief Call this from the derived class' check() method to debounce and detect if the input is a hold vs. press
  /// @param currentAction The InputAction needing to be interpreted
  /// @return Determined InputAction - either debounced press, held, or none
  InputAction _debounceOrHeld(InputAction currentAction);

  /// @brief This method is designed to take an input from a touch screen display and determine which "button"  has been
  /// touched according to the coordinates of the touch. This assumes the touch screen has been calibrated correctly.
  /// @details The display is divided as such:
  /// - The entire left third of the display is the left button
  /// - The entire right third of the display is the right button
  /// - The top third of the resulting centre of the display is the up button
  /// - The bottom third of the resulting centre of the display is the down button
  /// - The centre third of both width and height is the centre button
  /// @param touchX The X coordinate of the touch
  /// @param touchY The Y coordinate of the touch
  /// @param displayWidth Display width in pixels
  /// @param displayHeight Display height in pixels
  /// @return A valid InputAction PRESS type
  InputAction _calculateInputAction(int touchX, int touchY, int displayWidth, int displayHeight);
};

#endif // INPUTINTERFACE_H
