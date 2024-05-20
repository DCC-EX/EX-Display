#ifndef EXTOUCH_H
#define EXTOUCH_H

#include "Defines.h"
#include <Arduino.h>
#include <SPI.h>   // most older screens use SPI

// is the followinf block needed?
#if SCREEN_TYPE == MCU
#include <Adafruit_GFX.h>
//#include <Touchscreen.h>
#elif SCREEN_TYPE == TFT
#include <TFT_eSPI.h>
#endif

/// @brief This EXTouch class is designed to be extended by other touch screen classes that define the methods to perform the
/// requesite activities according to the library in use to assess touches to the physical display.
/// This allows all physical screen methods to be consistent regardless of the library or driver in use, allowing this
/// code to support multiple different display types without needing to have the main functions call different
/// libraries/methods. As this is a virtual only class, every virtual method must be declared and defined in the class
/// that extends this.
class EXTouch {
public:
  /// @brief Constructor for a new EXTouch object
  EXTouch() {
    int pixel_x;    }  The x & y coordinates of a touch point
    int pixel_y;    }
    buttonPressed = 0;
    buttonNumber = 0;
    buttonHeld = false;
  }

  /// @brief Virtual function to implement to setup the touch screen parameters
  virtual void setupTouch();

  /// @brief Virtual function to implement to clear the entire screen
  /// @param option indicator for which screen buttons to be setup
  /// @param fontColour Valid colour to set the button text to
  /// @param backgroundColour Valid colour to set the button colour to
  virtual void drawButtons(byte option, uint16_t fontColour, uint16_t backgroundColour);

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
