#include "Defines.h"
#ifdef NEEDS_TFT

#include <TFT_eSPIScreen.h>

TFT_eSPIScreen::TFT_eSPIScreen(TFT_eSPI &tft) : EXScreen(), _tft(tft) {}

void TFT_eSPIScreen::setupScreen(uint8_t rotation, uint8_t textSize, uint16_t backgroundColour) {
  const GFXfont *gfxFont = TEXT_FONT;
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

void TFT_eSPIScreen::clearRow(uint8_t row, uint16_t backgroundColour) {
  int32_t x = (row * fontHeight) + row;
  int32_t y = 0;
  int32_t w = fontWidth * maxColumns;
  int32_t h = fontHeight;
  CONSOLE.print(F("clearRow x|y|w|h|colour: "));
  CONSOLE.print(F("|"));
  CONSOLE.print(x);
  CONSOLE.print(F("|"));
  CONSOLE.print(y);
  CONSOLE.print(F("|"));
  CONSOLE.print(w);
  CONSOLE.print(F("|"));
  CONSOLE.print(h);
  CONSOLE.print(F("|0x"));
  CONSOLE.println(backgroundColour, HEX);
  _tft.drawRect(x, y, w, h, backgroundColour);
}

void TFT_eSPIScreen::writeRow(uint8_t row, uint8_t column, uint16_t fontColour, uint16_t backgroundColour,
                              uint8_t maxLength, char *message) {
  uint16_t textRow = (row * fontHeight) + row;
  uint16_t width = fontWidth * maxLength;
  _tft.setTextPadding(width);
  _tft.setTextColor(fontColour, backgroundColour);
  _tft.drawString(message, column, textRow);
}

void TFT_eSPIScreen::writeLine(uint8_t row, uint8_t column, uint8_t lineLength, uint16_t lineColour,
                               uint16_t backgroundColour) {
  // Horizontal start/end
  int32_t x1 = column;
  int32_t x2 = fontWidth * lineLength;
  // Vertical start - half way up the font height
  int32_t y1 = (row * fontHeight) + row + (fontHeight / 2);
  int32_t y2 = y1;
  clearRow(row, backgroundColour);
  _tft.drawLine(x1, y1, x2, y2, lineColour);
}

#endif
