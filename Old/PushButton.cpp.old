#include "Defines.h"

#if defined(USE_BUTTONS)

#include "PushButton.h"

PushButton::PushButton(uint8_t leftPin, uint8_t rightPin, uint8_t centrePin, uint8_t upPin, uint8_t downPin)
    : InputMethod() {
  _buttons[LeftButton].pin = leftPin;
  _buttons[RightButton].pin = rightPin;
  _buttons[CentreButton].pin = centrePin;
  _buttons[UpButton].pin = upPin;
  _buttons[DownButton].pin = downPin;
}

void PushButton::begin() {
  pinMode(_buttons[LeftButton].pin, INPUT_PULLUP);
  pinMode(_buttons[RightButton].pin, INPUT_PULLUP);
  pinMode(_buttons[CentreButton].pin, INPUT_PULLUP);
  pinMode(_buttons[UpButton].pin, INPUT_PULLUP);
  pinMode(_buttons[DownButton].pin, INPUT_PULLUP);
}

bool PushButton::_readRawInput(ButtonName button) {
  return digitalRead(_buttons[button].pin) == LOW;
}

#endif
