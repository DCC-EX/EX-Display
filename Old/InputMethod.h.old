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

struct Button {
#if defined(USE_TOUCH)
  uint16_t xStart = 0;
  uint16_t xEnd = 0;
  uint16_t yStart = 0;
  uint16_t yEnd = 0;
#elif defined(USE_BUTTONS)
  uint8_t pin;
#endif
  unsigned long _lastDebounceTime;
  unsigned long _buttonHoldStartTime;
  bool _buttonState;
  bool _lastButtonState;
};

enum ButtonName {
  LeftButton = 0,
  RightButton = 1,
  CentreButton = 2,
  UpButton = 3,
  DownButton = 4,
  NoButton = 5,
};

enum ButtonState {
  Pressed = 0,
  Held = 1,
  Released = 2,
  None = 3,
};

struct ButtonResult {
  ButtonName button;
  ButtonState state;
};

class InputMethod {
public:
  /// @brief Constructor for the InputMethod class
  InputMethod();

  virtual void begin() = 0;

  ButtonResult processInput();

  void setScreen(PhysicalScreen *screen);

protected:
  PhysicalScreen *_screen; // Physical screen instance associated with this input
  uint8_t _inputNumber;    // Auto incrementing number, enables multiple touch screens

  Button _buttons[5];
#if defined(USE_TOUCH)
  void _calculateButtons();
#endif
  virtual bool _readRawInput(ButtonName button) = 0;

  static const unsigned long _debounceDelay = 50;
  static const unsigned long _holdThreshold = 500;
};

#endif
