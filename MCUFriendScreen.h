#include "Defines.h"
#ifdef NEEDS_MCU

#ifndef MCUFRIENDSCREEN_H
#define MCUFRIENDSCREEN_H

#include "EXScreen.h"
#include <Adafruit_GFX.h>
#include <Arduino.h>
#include <MCUFRIEND_kbv.h>

class MCUFriendScreen : public EXScreen {
public:
  MCUFriendScreen(MCUFRIEND_kbv &tft);

  virtual void setupScreen(uint8_t rotation, uint8_t textSize, uint16_t backgroundColour) override;

  virtual void clearScreen(uint16_t backgroundColour) override;

  virtual void writeRow(uint8_t row, uint8_t column, uint16_t fontColour, uint16_t backgroundColour, uint8_t maxLength,
                        char *message) override;

  uint8_t getCharacterWidth(const char *character);

private:
  MCUFRIEND_kbv &_tft;
  GFXfont _gfxFont;
};

#endif
#endif
