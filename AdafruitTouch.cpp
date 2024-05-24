#include "Defines.h"

#if defined(NEEDS_MCU) && defined(USE_TOUCH)

#include "AdafruitTouch.h"

AdafruitTouch::AdafruitTouch(TouchScreen &touchScreen) : InputMethod(), _touchScreen(touchScreen) {}

void AdafruitTouch::begin() {
  if (!_screen) {
    return;
  }
  CONSOLE.print(F("Screen Height|Width: "));
  CONSOLE.print(_screen->getHeight());
  CONSOLE.print(F("|"));
  CONSOLE.println(_screen->getWidth());
}

void AdafruitTouch::processInput() {
  _touchScreen.getPoint();
}

#endif
