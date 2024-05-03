#include "Defines.h"
#include "MCUFriendScreen.h"

MCUFriendScreen::MCUFriendScreen(uint8_t maxRows, uint8_t maxColumns) : EXScreen(maxRows, maxColumns) {
  MCUFRIEND_kbv _tft;
}

void MCUFriendScreen::setupScreen(uint8_t rotation, uint8_t textColour, uint8_t backgroundColour) {
  uint16_t screenId = _tft.readID();
  CONSOLE.print("TFT ID: 0x");
  CONSOLE.println(screenId, HEX);
  if (screenId == 0xD3D3) {
    screenId = 0x9486;
  }
  _tft.begin(screenId);
  _tft.setRotation(rotation);
  _tft.setTextColor(textColour);
  _tft.fillScreen(backgroundColour);
}

void MCUFriendScreen::writeRow(uint8_t row, uint8_t column, const GFXfont *fontName, uint8_t textSize,
                               uint8_t fontColour, char *message) {
  CONSOLE.print(F("Write to screen DisplayRow|Message: "));
  CONSOLE.print(row);
  CONSOLE.print(F("|"));
  CONSOLE.println(message);
  _tft.setFont(fontName);
  _tft.setTextColor(fontColour);
  _tft.setCursor(column, row);
  _tft.setTextSize(textSize);
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
