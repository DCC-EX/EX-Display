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

class InputMethod {
public:
  /// @brief Constructor for the InputMethod class
  InputMethod();

  virtual void begin() = 0;

  virtual void processInput() = 0;

  void setScreen(PhysicalScreen *screen);

protected:
  static InputMethod *_first; //
  InputMethod *_next;
  PhysicalScreen *_screen;
};

#endif
