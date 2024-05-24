#include "Defines.h"
#ifdef NEEDS_TFT

#include "TFT_eSPIScreen.h"

TFT_eSPIScreen::TFT_eSPIScreen(TFT_eSPI &tft) : PhysicalScreen(), _tft(tft) {}

void TFT_eSPIScreen::setupScreen(uint8_t rotation, uint8_t textSize, uint16_t backgroundColour) {
  const GFXfont *gfxFont = TEXT_FONT;
  _tft.init();
  _tft.setRotation(rotation);
  _tft.fillScreen(backgroundColour);
  _tft.setFreeFont(gfxFont);
  _tft.setTextSize(textSize);
  _fontHeight = gfxFont->yAdvance;
  _fontWidth = _tft.textWidth("A");
  _maxRows = _tft.height() / _fontHeight;
  _maxRowLength = _tft.width() / _fontWidth;
  CONSOLE.print(F("Setup done: _fontHeight|_fontWidth|_tft.Height()|_tft.Width(): "));
  CONSOLE.print(_fontHeight);
  CONSOLE.print(F("|"));
  CONSOLE.print(_fontWidth);
  CONSOLE.print(F("|"));
  CONSOLE.print(_tft.height());
  CONSOLE.print(F("|"));
  CONSOLE.println(_tft.width());
}

void TFT_eSPIScreen::clearScreen(uint16_t backgroundColour) { _tft.fillScreen(backgroundColour); }

void TFT_eSPIScreen::clearRow(uint8_t row, uint16_t backgroundColour) {
  int32_t x = 0;
  int32_t y = (row * _fontHeight) + row;
  int32_t w = _fontWidth * _maxRowLength;
  int32_t h = _fontHeight;
  _tft.fillRect(x, y, w, h, backgroundColour);
}

void TFT_eSPIScreen::writeRow(uint8_t row, uint8_t column, uint16_t fontColour, uint16_t backgroundColour,
                              uint8_t maxLength, char *message, bool underlined) {
  uint16_t y = (row * _fontHeight) + row;
  uint16_t width = _fontWidth * maxLength;
  _tft.setTextPadding(width);
  _tft.setTextColor(fontColour, backgroundColour);
  if (underlined) {
    _tft.drawLine(column, y + _fontHeight, width, y + _fontHeight, fontColour);
  } else {
    _tft.drawLine(column, y + _fontHeight, width, y + _fontHeight, backgroundColour);
  }
  _tft.drawString(message, column, y);
}

void TFT_eSPIScreen::writeLine(uint8_t row, uint8_t column, uint8_t lineLength, uint16_t lineColour,
                               uint16_t backgroundColour) {
  // Horizontal start/end
  int32_t x1 = column;
  int32_t x2 = _fontWidth * lineLength;
  // Vertical start - half way up the font height
  int32_t y1 = (row * _fontHeight) + row + (_fontHeight / 2);
  int32_t y2 = y1;
  clearRow(row, backgroundColour);
  _tft.drawLine(x1, y1, x2, y2, lineColour);
}

uint16_t TFT_eSPIScreen::getHeight() { return _tft.height(); }

uint16_t TFT_eSPIScreen::getWidth() { return _tft.width(); }

#endif
