#include "Defines.h"
#ifdef NEEDS_TFT

#ifndef TFT_ESPISCREEN_H
#define TFT_ESPISCREEN_H

#include "PhysicalScreen.h"
#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>

class TFT_eSPIScreen : public PhysicalScreen {
public:
  TFT_eSPIScreen(TFT_eSPI &tft);

  virtual void setupScreen(uint8_t rotation, uint8_t textSize, uint16_t backgroundColour) override;

  virtual void clearScreen(uint16_t backgroundColour) override;

  virtual void clearRow(uint8_t row, uint16_t backgroundColour) override;

  virtual void writeRow(uint8_t row, uint8_t column, uint16_t fontColour, uint16_t backgroundColour, uint8_t maxLength,
                        char *message, bool underlined) override;

  virtual void writeLine(uint8_t row, uint8_t column, uint8_t lineLength, uint16_t lineColour,
                         uint16_t backgroundColour) override;

  virtual uint16_t getHeight() override;

  virtual uint16_t getWidth() override;

private:
  TFT_eSPI &_tft;
};

#endif

#endif
