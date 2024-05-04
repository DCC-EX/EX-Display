#ifndef MCUFRIENDSCREEN_H
#define MCUFRIENDSCREEN_H

#include "EXScreen.h"
#include "MCUFRIEND_kbv.h"
#include <Arduino.h>

class MCUFriendScreen : public EXScreen {
public:
  MCUFriendScreen(MCUFRIEND_kbv &tft, uint8_t maxRows, uint8_t maxColumns);

  virtual void setupScreen(uint8_t rotation, uint16_t textColour, uint16_t backgroundColour) override;

  virtual void writeRow(uint8_t row, uint8_t column, const GFXfont *fontName, uint16_t fontColour, uint8_t textSize,
                        char *message) override;

private:
  MCUFRIEND_kbv _tft;
};

#endif
