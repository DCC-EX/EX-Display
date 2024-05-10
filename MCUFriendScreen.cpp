#include "Defines.h"
#ifdef NEEDS_MCU

#include "MCUFriendScreen.h"

MCUFriendScreen::MCUFriendScreen(MCUFRIEND_kbv &tft) : EXScreen(), _tft(tft) {}

void MCUFriendScreen::setupScreen(uint8_t rotation, uint8_t textSize, uint16_t backgroundColour) {

  const GFXfont *gfxFont = TEXT_FONT;
  CONSOLE.print(F("DEBUG Font: first|last|yAdvance: "));
  CONSOLE.print(gfxFont->first);
  CONSOLE.print(F("|"));
  CONSOLE.print(gfxFont->last);
  CONSOLE.print(F("|"));
  CONSOLE.println(gfxFont->yAdvance);

  uint16_t screenId = _tft.readID();
  CONSOLE.print("TFT ID: 0x");
  CONSOLE.println(screenId, HEX);
  if (screenId == 0xD3D3) {
    screenId = 0x9486;
  }
  _tft.begin(screenId);
  _tft.setRotation(rotation);
  _tft.setFont(gfxFont);
  _tft.setTextSize(textSize);
#ifdef INVERT_SCREEN
  _tft.invertDisplay(screenId);
#endif
  _tft.fillScreen(backgroundColour);
  fontHeight = gfxFont->yAdvance;
  fontWidth = getCharacterWidth("A");
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

uint8_t MCUFriendScreen::getCharacterWidth(const char *character) {
  int16_t x1, y1;
  uint16_t w, h;
  _tft.getTextBounds(character, 0, 0, &x1, &y1, &w, &h);
  return w;
}

void MCUFriendScreen::clearScreen(uint16_t backgroundColour) { _tft.fillScreen(backgroundColour); }

void MCUFriendScreen::writeRow(uint8_t row, uint8_t column, uint16_t fontColour, uint16_t backgroundColour,
                               uint8_t maxLength, char *message) {
  CONSOLE.print(F("row:"));
  CONSOLE.println(row);
  // uint16_t textRow = ((row+1) * fontHeight) + row;
  uint16_t textRow = ((row + 1) * fontHeight);
  CONSOLE.print(F("textRow:"));
  CONSOLE.println(textRow);
  uint16_t width = fontWidth * maxLength;
  uint16_t paddedColumn = column + width;
  _tft.fillRect(1, ((textRow - fontHeight) + 10), DISPLAY_WIDTH, (fontHeight), backgroundColour);
  _tft.setTextColor(fontColour, backgroundColour);
  //_tft.setCursor(paddedColumn, textRow);
  _tft.setCursor(1, textRow);
  _tft.print(message);
}

#endif
