#ifndef TFT_ESPISCREEN_H
#define TFT_ESPISCREEN_H

#include "EXScreen.h"
#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>

class TFT_eSPIScreen : public EXScreen {
public:
  TFT_eSPIScreen(uint8_t maxRows, uint8_t maxColumns);

  virtual void setupScreen(uint8_t rotation, uint16_t textColour, uint16_t backgroundColour) override;

  virtual void writeRow(uint8_t row, uint8_t column, const GFXfont *fontName, uint16_t fontColour, uint8_t textSize,
                        char *message) override;

private:
  TFT_eSPI _tft;
};

#endif
