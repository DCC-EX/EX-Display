#ifndef MCUFRIENDSCREEN_H
#define MCUFRIENDSCREEN_H

#include <Arduino.h>
#include "MCUFRIEND_kbv.h"
#include "EXScreen.h"

class MCUFriendScreen : public EXScreen {
public:
  MCUFriendScreen();

private:
  MCUFRIEND_kbv _tft;

};

#endif
