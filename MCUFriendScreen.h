#ifndef MCUFRIENDSCREEN_H
#define MCUFRIENDSCREEN_H

#include "EXScreen.h"
#include "MCUFRIEND_kbv.h"
#include <Arduino.h>


class MCUFriendScreen : public EXScreen {
public:
  MCUFriendScreen(uint8_t maxRows, uint8_t maxColumns);

private:
  MCUFRIEND_kbv _tft;
};

#endif
