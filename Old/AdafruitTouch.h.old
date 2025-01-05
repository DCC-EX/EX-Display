#ifndef ADAFRUITTOUCH_H
#define ADAFRUITTOUCH_H

#include "Defines.h"

#if defined(NEEDS_MCU) && defined(USE_TOUCH)
#include "InputMethod.h"
#include <Arduino.h>
#include <MCUFRIEND_kbv.h>
#include <SPI.h>
#include <TouchScreen.h>


class AdafruitTouch : public InputMethod {
public:
  /// @brief Constructor for an AdafruitTouch instance
  /// @param touchScreen Reference to an Adafruit TouchScreen instance
  AdafruitTouch(TouchScreen &touchScreen);

  void begin() override;

private:
  TouchScreen &_touchScreen;

  bool _readRawInput(ButtonName button) override;
};

#endif // NEEDS_MCU and USE_TOUCH

#endif
