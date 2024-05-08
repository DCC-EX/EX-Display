#ifdef NEEDS_TFT

CONSOLE.println("Loading TFT_eSPI code");

#include "Defines.h"
#include <TFT_eSPIScreen.h>

TFT_eSPIScreen::TFT_eSPIScreen(TFT_eSPI &tft) : EXScreen(), _tft(tft) {}

void TFT_eSPIScreen::setupScreen(uint8_t rotation, const GFXfont *gfxFont, uint8_t textSize,
                                 uint16_t backgroundColour) {
  _tft.init();
  _tft.setRotation(rotation);
  _tft.fillScreen(backgroundColour);
  _tft.setFreeFont(gfxFont);
  _tft.setTextSize(textSize);
  fontHeight = gfxFont->yAdvance;
  fontWidth = _tft.textWidth("A");
  maxRows = _tft.height() / fontHeight;
  maxColumns = _tft.width() / fontWidth;
  CONSOLE.print(F("Setup done: fontHeight|fontWidth|tftHeight|tftWidth: "));
  CONSOLE.print(fontHeight);
  CONSOLE.print(F("|"));
  CONSOLE.print(fontWidth);
  CONSOLE.print(F("|"));
  CONSOLE.print(_tft.height());
  CONSOLE.print(F("|"));
  CONSOLE.println(_tft.width());
}

void TFT_eSPIScreen::clearScreen(uint16_t backgroundColour) { _tft.fillScreen(backgroundColour); }

void TFT_eSPIScreen::writeRow(uint8_t row, uint8_t column, uint16_t fontColour, uint16_t backgroundColour,
                              uint8_t maxLength, char *message) {
  uint16_t textRow = (row * fontHeight) + row;
  uint16_t width = fontWidth * maxLength;
  _tft.setTextPadding(width);
  _tft.setTextColor(fontColour, backgroundColour);
  _tft.drawString(message, column, textRow);
}

#endif
