#include "Defines.h"
#ifdef NEEDS_OLED
#include "OLEDScreen.h"

#if SCREEN_TYPE == OLED_SSD1306
OLEDScreen::OLEDScreen(Adafruit_SSD1306 &oled, uint8_t muxAddress, uint8_t subBus)
    : EXScreen(), _oled(oled), _muxAddress(muxAddress), _subBus(subBus) {}
#elif SCREEN_TYPE == OLED_SH1106
OLEDScreen::OLEDScreen(Adafruit_SH1106G &oled, uint8_t muxAddress, uint8_t subBus)
    : EXScreen(), _oled(oled), _muxAddress(muxAddress), _subBus(subBus) {}
#endif

void OLEDScreen::setupScreen(uint8_t rotation, uint8_t textSize, uint16_t backgroundColour) {
  const GFXfont *gfxFont = TEXT_FONT;
#if SCREEN_TYPE == OLED_SSD1306
  _oled.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS);
#elif SCREEN_TYPE == OLED_SH1106
  _oled.begin(OLED_ADDRESS);
#endif
  _oled.setRotation(rotation);
  _oled.setFont(gfxFont);
  _oled.setTextSize(textSize);
  _oled.clearDisplay();
  _oled.display();
  fontHeight = gfxFont->yAdvance;
  fontWidth = _getTextWidth();
  maxRows = _oled.height() / fontHeight;
  maxColumns = _oled.width() / fontWidth;
  CONSOLE.print(F("Setup done: fontHeight|fontWidth|tftHeight|tftWidth: "));
  CONSOLE.print(fontHeight);
  CONSOLE.print(F("|"));
  CONSOLE.print(fontWidth);
  CONSOLE.print(F("|"));
  CONSOLE.print(_oled.height());
  CONSOLE.print(F("|"));
  CONSOLE.println(_oled.width());
}

void OLEDScreen::clearScreen(uint16_t backgroundColour) {
  _oled.clearDisplay();
  _oled.display();
}

void OLEDScreen::clearRow(uint8_t row, uint16_t backgroundColour) {
  int16_t x = 0;
  int16_t y = (row * fontHeight) + row;
  int16_t w = fontWidth * maxColumns;
  int16_t h = fontHeight;
  _oled.fillRect(x, y, w, h, backgroundColour);
  _oled.display();
}

void OLEDScreen::writeRow(uint8_t row, uint8_t column, uint16_t fontColour, uint16_t backgroundColour,
                          uint8_t maxLength, char *message, bool underlined) {
  uint16_t x = column;
  uint16_t y = (row * fontHeight) + fontHeight;
  _oled.setTextColor(fontColour);
  _oled.setCursor(x, y);
  _oled.print(message);
  if (underlined) {
    _oled.drawLine(column, y+1, _oled.width(), y+1, fontColour);
  } else {
    _oled.drawLine(column, y+1, _oled.width(), y+1, backgroundColour);
  }
  _oled.display();
  CONSOLE.print(F("\nwriteRow textRow|message: "));
  CONSOLE.print(y);
  CONSOLE.print(F("|"));
  CONSOLE.println(message);
}

void OLEDScreen::writeLine(uint8_t row, uint8_t column, uint8_t lineLength, uint16_t lineColour,
                           uint16_t backgroundColour) {
  // Horizontal start/end
  int16_t x1 = column;
  int16_t x2 = fontWidth * lineLength;
  // Vertical start - half way up the font height
  int16_t y1 = (row * fontHeight) + row + (fontHeight / 2);
  int16_t y2 = y1;
  clearRow(row, backgroundColour);
  _oled.drawLine(x1, y1, x2, y2, lineColour);
  _oled.display();
}

uint8_t OLEDScreen::_getTextWidth() {
  int16_t x1, y1;
  uint16_t w, h;
  _oled.getTextBounds("A", 0, 0, &x1, &y1, &w, &h);
  return w;
}

void OLEDScreen::_switchMUX(uint8_t muxAddress, uint8_t subBus) {
  if (muxAddress == 0 || subBus == 255) {
    return;
  }
  Wire.beginTransmission(muxAddress);
  Wire.write(subBus);
  Wire.endTransmission();
}

#endif
