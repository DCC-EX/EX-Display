#ifndef TFT_ESPITOUCH_H
#define TFT_ESPITOUCH_H

#include "Defines.h"

#if defined(NEEDS_TFT) && defined(USE_TOUCH)
#include "InputMethod.h"
#include <Arduino.h>
#include <TFT_eSPI.h>

class TFT_eSPITouch : public InputMethod {
public:
  /// @brief Constructor for the TFT_eSPITouch instance
  /// @param tftTouch Reference to an existing TFT_eSPI instance
  TFT_eSPITouch(TFT_eSPI &tftTouch);

  void begin() override;

  void processInput() override;

private:
  TFT_eSPI &_tftTouch;
};

#endif // NEEDS_TFT and USE_TOUCH

#endif
