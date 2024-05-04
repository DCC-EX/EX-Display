#include "Defines.h"
#include "TFT_eSPIScreen.h"

TFT_eSPIScreen::TFT_eSPIScreen(uint8_t maxRows, uint8_t maxColumns) : EXScreen(maxRows, maxColumns) { TFT_eSPI _tft = TFT_eSPI(); }

void TFT_eSPIScreen::setupScreen(uint8_t rotation, uint16_t textColour, uint16_t backgroundColour) {
  _tft.init();
  // _tft.fillScreen(backgroundColour);
  // _tft.setCursor(0, 0);
  // _tft.print(F("EX-Display"));
}

void TFT_eSPIScreen::writeRow(uint8_t row, uint8_t column, const GFXfont *fontName, uint16_t fontColour,
                              uint8_t textSize, char *message) {
  _tft.setCursor(column, row);
  _tft.setTextColor(fontColour);
  _tft.print(message);
}
