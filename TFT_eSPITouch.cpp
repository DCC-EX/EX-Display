#include "Defines.h"
#include "TFT_eSPITouch.h"

#ifdef NEEDS_TFT

TFT_eSPITouch::TFT_eSPITouch(TFT_eSPI &tftTouch) : InputMethod(), _tftTouch(tftTouch) {}

#endif
