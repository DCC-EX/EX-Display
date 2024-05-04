#include "Defines.h"
#include "TFT_eSPIScreen.h"

TFT_eSPIScreen::TFT_eSPIScreen(TFT_eSPI &tft, uint8_t maxRows, uint8_t maxColumns)
    : EXScreen(maxRows, maxColumns), _tft(tft) {}

void TFT_eSPIScreen::setupScreen(uint8_t rotation, uint16_t textColour, uint16_t backgroundColour) {
  _tft.init();
  _tft.setRotation(rotation);
  _tft.fillScreen(backgroundColour);
  _tft.setCursor(0, 0);
  _tft.print(F("EX-Display"));
}

void TFT_eSPIScreen::writeRow(uint8_t row, uint8_t column, const GFXfont *fontName, uint16_t fontColour,
                              uint8_t textSize, char *message) {
  _tft.setTextSize(textSize);
  _tft.setFreeFont(fontName);
  uint8_t textRow = row * 8;
  _tft.setCursor(column, textRow);
  uint8_t blankLength = strlen(message);
  _tft.setTextColor(BACKGROUND_COLOUR);
  for (uint8_t i = 0; i < blankLength; i++) {
    _tft.print(' ');
  }
  _tft.setCursor(column, textRow);
  _tft.setTextColor(fontColour);
  _tft.print(message);
}
