#ifndef EXTOUCH_H
#define EXTOUCH_H

#include "Defines.h"
#include <Arduino.h>

/* Notes and thoughts
This should be completely independent of hardware
- Ability to use a touch screen
- Ability to use physical push buttons
- Are there other types?
Inputs... suggest we just emulate buttons with touch screen areas, so the class extending this would define pixel
coordinates etc., but this class only knows about buttons/generic inputs. Thinking we allow for 5 areas:
- Left/right edges to navigate back and forth between logical displays
- Top/bottom of centre to scroll up/down
- Centre to... what exactly? Do we need this?
To keep independent of hardware, we shouldn't need pixel locations etc. in this class, rather just represent each
individual button, so left of screen might be button 0, top button 1, right button 2, etc.
The button should map to a task, ie. switch display, scroll up, etc.
I think there is a way to do this with a callback type setup, but not sure how to do that just yet.
Brief start made on ButtonInput class, but does debounce need to be across all inputs or just physical buttons?
*/

/// @brief This EXTouch class is designed to be extended by other touch screen classes that define the methods to
/// perform the requesite activities according to the library in use to assess touches to the physical display or other
/// input methods (eg. push buttons). This allows all physical interaction methods to be consistent regardless of the
/// library or driver in use, allowing this code to support multiple different input/touch types without needing to have
/// the main functions call different libraries/methods. As this is a virtual only class, every virtual method must be
/// declared and defined in the class that extends this.
class EXTouch {
public:
  /// @brief Constructor for a new EXTouch object
  EXTouch() {}

  /// @brief Virtual function to implement to setup the touch screen parameters
  virtual void setupTouch();

  /// @brief Virtual function to implement to clear the entire screen
  /// @param fontColour Valid colour to set the button text to
  /// @param backgroundColour Valid colour to set the button colour to
  virtual void drawButtons(uint16_t fontColour, uint16_t backgroundColour);

  /// @brief Virtual function test if the screen was pressed.  Returns true or false
  bool touchGetXY();

  /// @brief Virtual function to check which of the buttons was pressed.
  /// sets the variable buttonPressed to the array element of the buttons.
  void checkButtons();

  /// @brief Address of the tft object created in the Screen.cpp
  uint8_t tft;

  /// @brief Height of the screen in use to assist button location
  uint8_t screenHeight;

  /// @brief Width of the screen in use to assist button location
  uint8_t screenWidth;
};

#endif // end include guard
