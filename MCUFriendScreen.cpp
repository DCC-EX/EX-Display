#include "Defines.h"
#ifdef NEEDS_MCU

#include "MCUFriendScreen.h"

MCUFriendScreen::MCUFriendScreen(MCUFRIEND_kbv &tft) : EXScreen(), _tft(tft) {}

void MCUFriendScreen::setupScreen(uint8_t rotation, uint8_t textSize, uint16_t backgroundColour) {

  const GFXfont *gfxFont = TEXT_FONT;

  uint16_t screenId = _tft.readID();
  CONSOLE.print("TFT ID: 0x");
  CONSOLE.println(screenId, HEX);
  if (screenId == 0xD3D3) {
    screenId = 0x9486;
  }
  if (screenId == 0x0) {
    CONSOLE.println(F("NO SCREEN DODGY FORCE TO 0x9486"));
    screenId = 0x9341;
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
  CONSOLE.println(F("\n~~ SETUP PARAMETERS ~~"));
  CONSOLE.print(F("MCUFRIEND_kbv parameters: _tft.height()|_tft.width(): "));
  CONSOLE.print(_tft.height());
  CONSOLE.print(F("|"));
  CONSOLE.println(_tft.width());
  CONSOLE.print(F("config.h parameters DISPLAY_HEIGHT|DISPLAY_WIDTH: "));
  CONSOLE.print(DISPLAY_HEIGHT);
  CONSOLE.print(F("|"));
  CONSOLE.println(DISPLAY_WIDTH);
  CONSOLE.print(F("maxRows|maxColumns|fontHeight|fontWidth: "));
  CONSOLE.print(maxRows);
  CONSOLE.print(F("|"));
  CONSOLE.print(maxColumns);
  CONSOLE.print(F("|"));
  CONSOLE.print(fontHeight);
  CONSOLE.print(F("|"));
  CONSOLE.println(fontWidth);
  CONSOLE.println(F("~~ END SETUP PARAMETERS ~~\n"));
}

uint8_t MCUFriendScreen::getCharacterWidth(const char *character) {
  int16_t x1, y1;
  uint16_t w, h;
  _tft.getTextBounds(character, 0, 0, &x1, &y1, &w, &h);
  return w;
}

void MCUFriendScreen::clearScreen(uint16_t backgroundColour) { _tft.fillScreen(backgroundColour); }

void MCUFriendScreen::clearRow(uint8_t row, uint16_t backgroundColour) {
  uint16_t textRow = ((row + 1) * fontHeight);
  int32_t x = 0;
  int32_t y = ((textRow - fontHeight) + 10);
  int32_t w = fontWidth * maxColumns;
  int32_t h = fontHeight;
  _tft.fillRect(x, y, w, h, backgroundColour);
}

void MCUFriendScreen::writeRow(uint8_t row, uint8_t column, uint16_t fontColour, uint16_t backgroundColour,
                               uint8_t maxLength, char *message, bool underlined) {
  uint16_t textRow = ((row + 1) * fontHeight);
  uint16_t width = fontWidth * maxLength;
  _tft.fillRect(1, ((textRow - fontHeight) + 10), DISPLAY_WIDTH, (fontHeight), backgroundColour);
  _tft.setTextColor(fontColour, backgroundColour);
  _tft.setCursor(1, textRow);
  _tft.print(message);
  if (underlined) {
    _tft.drawLine(column, textRow + fontHeight, width, textRow + fontHeight, fontColour);
  }
  CONSOLE.println(F("\n~~ WRITE ROW PARAMETERS ~~"));
  CONSOLE.print(F("textRow|width: "));
  CONSOLE.print(textRow);
  CONSOLE.print(F("|"));
  CONSOLE.println(width);
  CONSOLE.println(F("~~ END WRITE ROW PARAMETERS ~~\n"));
}

void MCUFriendScreen::writeLine(uint8_t row, uint8_t column, uint8_t lineLength, uint16_t lineColour,
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
