#include "config.h"
#ifdef NEEDS_MCU


#include "Defines.h"
#include "MCUFriendScreen.h"

//CONSOLE.println("Loading MCUFRIEND code");

MCUFriendScreen::MCUFriendScreen(MCUFRIEND_kbv &tft) : EXScreen(), _tft(tft) {}

void MCUFriendScreen::setupScreen(uint8_t rotation, const GFXfont *gfxFont, uint8_t textSize,
                                  uint16_t backgroundColour) {

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
  uint16_t textRow = (row * fontHeight) + row;
  uint16_t width = fontWidth * maxLength;
  uint16_t paddedColumn = column + width;
  _tft.setTextColor(fontColour, backgroundColour);
  //_tft.setCursor(paddedColumn, textRow);
  _tft.setCursor(1, textRow);
  _tft.print(message);
}

// void MCUFriendScreen::writeHeaderRow(uint8_t row, uint8_t column, uint16_t fontColour, uint16_t backgroundColour,
//                                      uint8_t maxLength, char *message) {

//   CONSOLE.print(F("Heading at column "));
//   CONSOLE.print(column);
//   // uint16_t textRow = ((row +1) * fontHeight) + fontHeight;
//   _tft.setTextColor(fontColour, backgroundColour);
//   _tft.setCursor(row, column);
//   _tft.print(message);
//   _tft.drawFastHLine(0, 30, _tft.width(), WHITE);
// }

/*
void EXScreen::newPage(uint8_t screenId) {
  // Method here to write new page to the display
    CONSOLE.println("New Page");
    tft.fillScreen(BLACK);
    char header[25] = {""};
    sprintf(header, "DCC-EX   SCREEN %d\n", screenId);
    tft.setTextColor(YELLOW);
    showmsgXY(1, 20, 1, header);
    tft.drawFastHLine(0, 25, tft.width(), WHITE);
    tft.setTextColor(WHITE);  // set this for all screen lines
*/

#endif