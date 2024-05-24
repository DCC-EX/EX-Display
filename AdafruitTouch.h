#ifndef ADAFRUITTOUCH_H
#define ADAFRUITTOUCH_H

#include "Defines.h"

#if defined(NEEDS_MCU) && defined(USE_TOUCH)

#include "InputMethod.h"
#include <Arduino.h>
#include <SPI.h>
#include <TouchScreen.h>

class AdafruitTouch : public InputMethod {
public:
  /// @brief Constructor for an AdafruitTouch instance
  /// @param touchScreen Reference to an Adafruit TouchScreen instance
  AdafruitTouch(TouchScreen &touchScreen);

  void begin();

  void processInput();

private:
  TouchScreen &_touchScreen;
};

#endif // NEEDS_MCU and USE_TOUCH

#endif
