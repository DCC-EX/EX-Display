#include "Defines.h"

#if defined(NEEDS_TFT) && defined(USE_TOUCH)

#include "TFT_eSPITouch.h"

TFT_eSPITouch::TFT_eSPITouch(TFT_eSPI &tftTouch) : InputMethod(), _tftTouch(tftTouch) {}

void TFT_eSPITouch::begin() {}

void TFT_eSPITouch::processInput() {
  uint16_t touchX, touchY;
  if (_tftTouch.getTouch(&touchX, &touchY)) {
    CONSOLE.print(F("Touched X|Y: "));
    CONSOLE.print(touchX);
    CONSOLE.print(F("|"));
    CONSOLE.println(touchY);
  }
}

#endif
