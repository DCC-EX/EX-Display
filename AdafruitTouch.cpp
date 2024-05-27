#include "Defines.h"

#if defined(NEEDS_MCU) && defined(USE_TOUCH)

#include "AdafruitTouch.h"

AdafruitTouch::AdafruitTouch(TouchScreen &touchScreen) : InputMethod(), _touchScreen(touchScreen) {}

void AdafruitTouch::begin() {
  if (!_screen) {
    return;
  }
  _calculateButtons();
}

bool AdafruitTouch::_readRawInput(ButtonName button) {
  TSPoint tsPoint = _touchScreen.getPoint();
  if (tsPoint.z > _touchScreen.pressureThreshhold) {
    uint16_t x = map(tsPoint.x, TS_MINX, TS_MAXX, 0, _screen->getWidth());
    uint16_t y = map(tsPoint.y, TS_MINY, TS_MAXY, 0, _screen->getHeight());
    if (x >= _buttons[button].xStart && x <= _buttons[button].xEnd && y >= _buttons[button].yStart &&
        y <= _buttons[button].yEnd) {
      return true;
    }
  }
  return false;
}

#endif
