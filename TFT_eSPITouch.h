#ifndef TFT_ESPITOUCH_H
#define TFT_ESPITOUCH_H

#include "Defines.h"

#ifdef NEEDS_TFT
#include "InputMethod.h"
#include <Arduino.h>
#include <TFT_eSPI.h>

class TFT_eSPITouch : public InputMethod {
public:
  /// @brief Constructor for the TFT_eSPITouch instance
  /// @param tftTouch Reference to an existing TFT_eSPI instance
  TFT_eSPITouch(TFT_eSPI &tftTouch);

private:
  TFT_eSPI &_tftTouch;
};

#endif // NEEDS_TFT

#endif
