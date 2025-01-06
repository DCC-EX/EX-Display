#ifndef TFT_ESPITOUCH_H
#define TFT_ESPITOUCH_H

#include "Defines.h"

#if defined(NEEDS_TFT) && defined(USE_TOUCH)
#ifdef USE_SPIFFS
#include <FS.h>
#endif
#include "InputMethod.h"
#include <Arduino.h>
#include <TFT_eSPI.h>

class TFT_eSPITouch : public InputMethod {
public:
  /// @brief Constructor for the TFT_eSPITouch instance
  /// @param tftTouch Reference to an existing TFT_eSPI instance
  TFT_eSPITouch(TFT_eSPI &tft);

  void begin() override;

private:
  TFT_eSPI &_tft;

#ifdef USE_SPIFFS
  char _calibrationFile[20];
#endif
  bool _setCalibration();
  bool _doCalibration();
  bool _readRawInput(ButtonName button) override;
};

#endif // NEEDS_TFT and USE_TOUCH

#endif
