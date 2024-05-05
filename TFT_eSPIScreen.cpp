#include "Defines.h"
#include "TFT_eSPIScreen.h"

TFT_eSPIScreen::TFT_eSPIScreen(TFT_eSPI &tft, uint8_t maxRows, uint8_t maxColumns)
    : EXScreen(maxRows, maxColumns), _tft(tft) {}

void TFT_eSPIScreen::setupScreen(uint8_t rotation, const GFXfont *gfxFont, uint8_t textSize,
                                 uint16_t backgroundColour) {
  _tft.init();
  _tft.setRotation(rotation);
  _tft.fillScreen(backgroundColour);
  _tft.setFreeFont(gfxFont);
  _tft.setTextSize(textSize);
  fontHeight = gfxFont->yAdvance;
}

void TFT_eSPIScreen::clearScreen(uint16_t backgroundColour) { _tft.fillScreen(backgroundColour); }

void TFT_eSPIScreen::writeRow(uint8_t row, uint8_t column, uint16_t fontColour, uint16_t backgroundColour,
                              uint8_t maxLength, char *message) {
  uint8_t textRow = (row * fontHeight) + fontHeight;
  uint8_t width = _tft.textWidth("A") * maxLength;
  _tft.setTextPadding(width);
  _tft.setTextColor(fontColour, backgroundColour);
  _tft.drawString(message, column, textRow);
}
