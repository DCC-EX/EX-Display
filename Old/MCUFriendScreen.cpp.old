#include "Defines.h"
#ifdef NEEDS_MCU

#include "MCUFriendScreen.h"

MCUFriendScreen::MCUFriendScreen() : PhysicalScreen() {
  _tft = new MCUFRIEND_kbv();
}

PhysicalScreen *MCUFriendScreen::setupScreen(uint8_t rotation, uint8_t textSize, uint16_t backgroundColour) {

  const GFXfont *gfxFont = TEXT_FONT;

  uint16_t screenId = _tft->readID();
  CONSOLE.print("TFT ID: 0x");
  CONSOLE.println(screenId, HEX);
  if (screenId == 0xD3D3) {
    screenId = 0x9486;
  }
  if (screenId == 0x0) {
    CONSOLE.println(F("NO SCREEN DODGY FORCE TO 0x9486"));
    screenId = 0x9341;
  }
  _tft->begin(screenId);
  _tft->setRotation(rotation);
  _tft->setFont(gfxFont);
  _tft->setTextSize(textSize);
  _tft->setTextWrap(false);
#ifdef INVERT_SCREEN
  _tft->invertDisplay(screenId);
#endif
  _tft->fillScreen(backgroundColour);
  _fontHeight = gfxFont->yAdvance;
  _fontWidth = getCharacterWidth("A");
  _maxRows = _tft->height() / _fontHeight;
  _maxRowLength = _tft->width() / _fontWidth;
  CONSOLE.println(F("\n~~ SETUP PARAMETERS ~~"));
  CONSOLE.print(F("MCUFRIEND_kbv parameters: _tft->height()|_tft->width(): "));
  CONSOLE.print(_tft->height());
  CONSOLE.print(F("|"));
  CONSOLE.println(_tft->width());
  CONSOLE.print(F("_maxRows|_maxRowLength|_fontHeight|_fontWidth: "));
  CONSOLE.print(_maxRows);
  CONSOLE.print(F("|"));
  CONSOLE.print(_maxRowLength);
  CONSOLE.print(F("|"));
  CONSOLE.print(_fontHeight);
  CONSOLE.print(F("|"));
  CONSOLE.println(_fontWidth);
  CONSOLE.println(F("~~ END SETUP PARAMETERS ~~\n"));
  return this;
}

uint8_t MCUFriendScreen::getCharacterWidth(const char *character) {
  int16_t x1, y1;
  uint16_t w, h;
  _tft->getTextBounds(character, 0, 0, &x1, &y1, &w, &h);
  return w;
}

void MCUFriendScreen::clearScreen(uint16_t backgroundColour) { _tft->fillScreen(backgroundColour); }

void MCUFriendScreen::clearRow(uint8_t row, uint16_t backgroundColour) {
  uint16_t textRow = ((row + 1) * _fontHeight);
  int32_t x = 0;
  int32_t y = ((textRow - _fontHeight) + 10);
  int32_t w = _fontWidth * _maxRowLength;
  int32_t h = _fontHeight;
  _tft->fillRect(x, y, w, h, backgroundColour);
}

void MCUFriendScreen::writeRow(uint8_t row, uint8_t column, uint16_t fontColour, uint16_t backgroundColour,
                               uint8_t maxLength, char *message, bool underlined) {
  uint16_t textRow = ((row + 1) * _fontHeight);
  uint16_t width = _fontWidth * maxLength;
  _tft->fillRect(1, ((textRow - _fontHeight) + 10), _tft->width(), (_fontHeight), backgroundColour);
  _tft->setTextColor(fontColour, backgroundColour);
  _tft->setCursor(1, textRow);
  _tft->print(message);
  if (underlined) {
    _tft->drawLine(column, textRow + _fontHeight, width, textRow + _fontHeight, fontColour);
  }
  // CONSOLE.println(F("\n~~ WRITE ROW PARAMETERS ~~"));
  // CONSOLE.print(F("textRow|width: "));
  // CONSOLE.print(textRow);
  // CONSOLE.print(F("|"));
  // CONSOLE.println(width);
  // CONSOLE.println(F("~~ END WRITE ROW PARAMETERS ~~\n"));
  CONSOLE.print(F("Printing row: "));
  CONSOLE.println(message);
}

void MCUFriendScreen::writeLine(uint8_t row, uint8_t column, uint8_t lineLength, uint16_t lineColour,
                                uint16_t backgroundColour) {
  // Horizontal start/end
  int32_t x1 = column;
  int32_t x2 = _fontWidth * lineLength;
  // Vertical start - half way up the font height
  int32_t y1 = (row * _fontHeight) + row + (_fontHeight / 2);
  int32_t y2 = y1;
  clearRow(row, backgroundColour);
  _tft->drawLine(x1, y1, x2, y2, lineColour);
}

uint16_t MCUFriendScreen::getHeight() { return _tft->height(); }

uint16_t MCUFriendScreen::getWidth() { return _tft->width(); }

#endif
