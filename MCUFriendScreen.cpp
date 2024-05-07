#include "Defines.h"
#include "MCUFriendScreen.h"

MCUFriendScreen::MCUFriendScreen(MCUFRIEND_kbv &tft) : EXScreen(), _tft(tft) {}

void MCUFriendScreen::setupScreen(uint8_t rotation, const GFXfont *gfxFont, uint8_t textSize,
                                  uint16_t backgroundColour) {
  uint16_t screenId = _tft.readID();
  CONSOLE.print("TFT ID: 0x");
  CONSOLE.println(screenId, HEX);
  if (screenId == 0xD3D3) {
    screenId = 0x9486;
  }
  _tft.begin(screenId);
  _tft.setRotation(rotation);
  #ifdef INVERT_SCREEN
    _tft.invertDisplay(screenId);
  #endif
  _tft.fillScreen(backgroundColour);
  _tft.setFont(gfxFont);
  _tft.setTextSize(textSize);

  //fontHeight = gfxFont->yAdvance;
  fontHeight = getFontHeight(gfxFont);

  uint8_t fontWidth = getCharacterWidth('A');
  maxRows = _tft.height() / fontHeight;
  maxColumns = _tft.width() / fontWidth;
}

uint8_t MCUFriendScreen::getCharacterWidth(char character) {
  int16_t x1, y1;
  uint16_t w, h;
  _tft.getTextBounds(&character, 0, 0, &x1, &y1, &w, &h);
  return w;
}

uint8_t MCUFriendScreen::getFontHeight(const GFXfont *font) {
  // Calculate font height (vertical advance - maximum ascent)
  //return font->yAdvance - font->glyph->yOffset;
    CONSOLE.print(F("| yAdvance"));
    CONSOLE.print(font->yAdvance);
    CONSOLE.print(F("| yOffset"));
    CONSOLE.print(font->glyph->yOffset);
  return font->yAdvance;
}

void MCUFriendScreen::clearScreen(uint16_t backgroundColour) { _tft.fillScreen(backgroundColour); }

void MCUFriendScreen::writeRow(uint8_t row, uint8_t column, uint16_t fontColour, uint16_t backgroundColour,
                               uint8_t maxLength, char *message) {
  uint16_t textRow = (row * fontHeight) + row;
  uint8_t fontWidth = getCharacterWidth('A');
  uint16_t width = fontWidth * maxLength;
    CONSOLE.print(F("Write to screen DisplayRow|Column|Message: "));
    CONSOLE.print(row);
    CONSOLE.print(F("|"));
    CONSOLE.print(column);
    CONSOLE.print(F("|"));
    CONSOLE.println(message);
  uint16_t paddedColumn = column + width;
  _tft.setTextColor(fontColour, backgroundColour);
  _tft.setCursor(paddedColumn, textRow);
  _tft.print(message);
    
    CONSOLE.print(F("row "));
    CONSOLE.print(row);
    CONSOLE.print(F("|"));
    CONSOLE.print(F("textRow "));
    CONSOLE.print(textRow);
    CONSOLE.print(F("|"));
    CONSOLE.print(F("fontheight "));
    CONSOLE.print(fontHeight);
    CONSOLE.print(F("|"));


    
}

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
