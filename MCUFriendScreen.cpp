#include "Defines.h"
#include "MCUFriendScreen.h"

MCUFriendScreen::MCUFriendScreen(MCUFRIEND_kbv &tft)
    : EXScreen(), _tft(tft) {}

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
  _tft.fillScreen(backgroundColour);
  _tft.setFont(gfxFont);
  _tft.setTextSize(textSize);
  fontHeight = gfxFont->yAdvance;
}

void MCUFriendScreen::clearScreen(uint16_t backgroundColour) { _tft.fillScreen(backgroundColour); }

void MCUFriendScreen::writeRow(uint8_t row, uint8_t column, uint16_t fontColour, uint16_t backgroundColour,
                               uint8_t maxLength, char *message) {
  CONSOLE.print(F("Write to screen DisplayRow|Column|Message: "));
  CONSOLE.print(row);
  CONSOLE.print(F("|"));
  CONSOLE.print(column);
  CONSOLE.print(F("|"));
  CONSOLE.println(message);
  _tft.setTextColor(fontColour, backgroundColour);
  _tft.setCursor(column, row);
  _tft.print(message);
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
