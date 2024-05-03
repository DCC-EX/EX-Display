#ifndef MCUFRIENDSCREEN_H
#define MCUFRIENDSCREEN_H

#include "EXScreen.h"
#include "MCUFRIEND_kbv.h"
#include <Arduino.h>

class MCUFriendScreen : public EXScreen {
public:
  MCUFriendScreen(uint8_t maxRows, uint8_t maxColumns);

  virtual void setupScreen(uint8_t rotation, uint8_t textColour, uint8_t backgroundColour) override;

  virtual void writeRow(uint8_t row, uint8_t column, const GFXfont *fontName, uint8_t fontColour, uint8_t textSize,
                        char *message) override;

private:
  MCUFRIEND_kbv _tft;
};

#endif
