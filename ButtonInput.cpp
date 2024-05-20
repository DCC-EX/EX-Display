#include "ButtonInput.h"
#include "Defines.h"

ButtonInput::ButtonInput(uint8_t button1Pin, uint8_t button2Pin, uint8_t button3Pin, uint8_t button4Pin,
                         uint8_t button5Pin, unsigned long debounceDelay)
    : EXTouch(), _button1Pin(button1Pin), _button2Pin(button2Pin), _button3Pin(button3Pin), _button4Pin(button4Pin),
      _button5Pin(button5Pin), _debouceDelay(debounceDelay) {}
