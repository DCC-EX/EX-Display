#include "Defines.h"
#include "InputMethod.h"

InputMethod *InputMethod::_first = nullptr;
uint8_t InputMethod::_inputCount = 0;

InputMethod::InputMethod() {
  _next = nullptr;
  _screen = nullptr;
  _inputNumber = _inputCount++;
  for (uint8_t i = 0; i < 5; i++) {
    _buttons[i]._lastDebounceTime = 0;
    _buttons[i]._buttonHoldStartTime = 0;
    _buttons[i]._buttonState = false;
    _buttons[i]._lastButtonState = false;
  }
}

void InputMethod::setScreen(PhysicalScreen *screen) { _screen = screen; }

#ifdef USE_TOUCH
void InputMethod::_calculateButtons() {
  // Left third of full screen height is left button, right third right button
  // Upper third of centre section is up button, lower third down button
  // Centre third of centre section is centre button
  _buttons[LeftButton].xStart = 0;
  _buttons[LeftButton].xEnd = _screen->getWidth() / 3;
  _buttons[LeftButton].yStart = 0;
  _buttons[LeftButton].yEnd = _screen->getHeight();
  _buttons[UpButton].xStart = _buttons[LeftButton].xEnd + 1;
  _buttons[UpButton].xEnd = (_screen->getWidth() / 3) + _buttons[LeftButton].xEnd;
  _buttons[UpButton].yStart = 0;
  _buttons[UpButton].yEnd = (_screen->getHeight() / 3);
  _buttons[CentreButton].xStart = _buttons[UpButton].xStart;
  _buttons[CentreButton].xEnd = _buttons[UpButton].xEnd;
  _buttons[CentreButton].yStart = _buttons[UpButton].yEnd + 1;
  _buttons[CentreButton].yEnd = (_screen->getHeight() / 3) + _buttons[UpButton].yEnd;
  _buttons[DownButton].xStart = _buttons[UpButton].xStart;
  _buttons[DownButton].xEnd = _buttons[UpButton].xEnd;
  _buttons[DownButton].yStart = _buttons[CentreButton].yEnd + 1;
  _buttons[DownButton].yEnd = _screen->getHeight();
  _buttons[RightButton].xStart = _buttons[CentreButton].xEnd + 1;
  _buttons[RightButton].xEnd = _screen->getWidth();
  _buttons[RightButton].yStart = 0;
  _buttons[RightButton].yEnd = _screen->getHeight();
}
#endif
