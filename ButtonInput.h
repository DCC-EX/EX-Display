#ifndef BUTTONINPUT_H
#define BUTTONINPUT_H

#include "Defines.h"
#include "EXTouch.h"
#include <Arduino.h>

class ButtonInput : EXTouch {
public:
  ButtonInput(uint8_t button1Pin, uint8_t button2Pin, uint8_t button3Pin, uint8_t button4Pin, uint8_t button5Pin,
              unsigned long debounceDelay = 10);

private:
  uint8_t _button1Pin;
  uint8_t _button2Pin;
  uint8_t _button3Pin;
  uint8_t _button4Pin;
  uint8_t _button5Pin;
  unsigned long _debouceDelay;
};

#endif
