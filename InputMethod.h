#ifndef INPUTMETHOD_H
#define INPUTMETHOD_H

#include "Defines.h"
#include "PhysicalScreen.h"
#include <Arduino.h>

/*
This class is to abstract input methods from controlling the physical screen.

This class should be extended by hardware specific classes that implement the virtual methods in this class to interact
with a physical screen.

The aim is to have five buttons (or equivalent sections on a touch screen) that represent left, right, up, down, and
centre. These may have both push and hold methods to perform different actions.

InputMethod instances will be in a linked list to cycle through to process inputs, and each InputMethod instance should
have a pointer to a screen to control.
*/

#if defined(USE_TOUCH)
struct ButtonDimensions {
  uint16_t xStart = 0;
  uint16_t xEnd = 0;
  uint16_t yStart = 0;
  uint16_t yEnd = 0;
};
#elif defined(USE_BUTTONS)
struct ButtonPin {
  uint8_t pin;
};
#endif

enum Button {
  LeftButton = 0,
  RightButton = 1,
  CentreButton = 2,
  UpButton = 3,
  DownButton = 4,
  NoButton = 5,
};

class InputMethod {
public:
  /// @brief Constructor for the InputMethod class
  InputMethod();

  virtual void begin() = 0;

  virtual Button processInput() = 0;

  void setScreen(PhysicalScreen *screen);

protected:
  InputMethod *_next;      // Next input instance in the list
  PhysicalScreen *_screen; // Physical screen instance associated with this input
  uint8_t _inputNumber;    // Auto incrementing number, enables multiple touch screens

#if defined(USE_TOUCH)
  ButtonDimensions _buttons[5];
  void _calculateButtons();
#elif defined(USE_BUTTONS)
  ButtonPin _buttons[5];
#endif

  static InputMethod *_first; // Start a linked list to cater for multiple inputs
  static uint8_t _inputCount; // Count of all inputs
};

#endif
