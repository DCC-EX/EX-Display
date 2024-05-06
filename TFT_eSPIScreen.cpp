#include "Defines.h"
#include "TFT_eSPIScreen.h"

TFT_eSPIScreen::TFT_eSPIScreen(TFT_eSPI &tft)
    : EXScreen(), _tft(tft) {}

void TFT_eSPIScreen::setupScreen(uint8_t rotation, const GFXfont *gfxFont, uint8_t textSize,
                                 uint16_t backgroundColour) {
  _tft.init();
  _tft.setRotation(rotation);
  _tft.fillScreen(backgroundColour);
  _tft.setFreeFont(gfxFont);
  _tft.setTextSize(textSize);
  fontHeight = gfxFont->yAdvance;
  uint8_t fontWidth = _tft.textWidth("A");
  maxRows = _tft.height() / fontHeight;
  maxColumns = _tft.width() / fontWidth;
  CONSOLE.print(F("Height|Width|maxRows|maxColumns: "));
  CONSOLE.print(_tft.height());
  CONSOLE.print(F("|"));
  CONSOLE.print(_tft.width());
  CONSOLE.print(F("|"));
  CONSOLE.print(maxRows);
  CONSOLE.print(F("|"));
  CONSOLE.println(maxColumns);
}

void TFT_eSPIScreen::clearScreen(uint16_t backgroundColour) { _tft.fillScreen(backgroundColour); }

void TFT_eSPIScreen::writeRow(uint8_t row, uint8_t column, uint16_t fontColour, uint16_t backgroundColour,
                              uint8_t maxLength, char *message) {
  uint16_t textRow = (row * fontHeight) + row;
  uint16_t width = _tft.textWidth("A") * maxLength;
  CONSOLE.print(F("row|fontHeight|textRow|maxLength|textWidth|width "));
  CONSOLE.print(F("|"));
  CONSOLE.print(row);
  CONSOLE.print(F("|"));
  CONSOLE.print(fontHeight);
  CONSOLE.print(F("|"));
  CONSOLE.print(textRow);
  CONSOLE.print(F("|"));
  CONSOLE.print(maxLength);
  CONSOLE.print(F("|"));
  CONSOLE.print(_tft.textWidth("A"));
  CONSOLE.print(F("|"));
  CONSOLE.println(width);
  _tft.setTextPadding(width);
  _tft.setTextColor(fontColour, backgroundColour);
  _tft.drawString(message, column, textRow);
}
