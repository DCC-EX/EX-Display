#include "Defines.h"
#ifdef NEEDS_OLED
#include "OLEDScreen.h"

OLEDScreen::OLEDScreen(uint8_t screenWidth, uint8_t screenHeight, uint8_t deviceAddress = 0x3C, uint8_t muxAddress,
                       uint8_t subBus)
    : PhysicalScreen(), _screenWidth(screenWidth), _screenHeight(screenHeight), _deviceAddress(deviceAddress),
      _muxAddress(muxAddress), _subBus(subBus) {
        _oled = new SSD1306AsciiWire;
      }

PhysicalScreen *OLEDScreen::setupScreen(uint8_t rotation, uint8_t textSize, uint16_t backgroundColour) {
  _switchMUX();
  if (_screenWidth == 132 && _screenHeight == 64) {
    _oled->begin(&SH1106_128x64, _deviceAddress);
    _screenWidth = 128;
  } else if (_screenWidth == 128 && _screenHeight == 64) {
    _oled->begin(&Adafruit128x64, _deviceAddress);
  } else if (_screenWidth == 128 && _screenHeight == 32) {
    _oled->begin(&Adafruit128x32, _deviceAddress);
  }
  // _oled->setRotation(rotation);
  // _oled->setFont(gfxFont);
  // _oled->setTextSize(textSize);
  // _oled->setTextWrap(false);
  // _oled->clearDisplay();
  // _oled->display();
  // _fontHeight = gfxFont->yAdvance;
  // _fontWidth = _getTextWidth();
  // _maxRows = _oled->height() / _fontHeight;
  // _maxRowLength = _oled->width() / _fontWidth;
  // CONSOLE.print(F("Setup done: _fontHeight|_fontWidth|_oled->Height|_oled->Width: "));
  // CONSOLE.print(_fontHeight);
  // CONSOLE.print(F("|"));
  // CONSOLE.print(_fontWidth);
  // CONSOLE.print(F("|"));
  // CONSOLE.print(_oled->height());
  // CONSOLE.print(F("|"));
  // CONSOLE.println(_oled->width());
  return this;
}

void OLEDScreen::clearScreen(uint16_t backgroundColour) {
  // _oled->clearDisplay();
  // _oled->display();
}

void OLEDScreen::clearRow(uint8_t row, uint16_t backgroundColour) {
  // int16_t x = 0;
  // int16_t y = (row * _fontHeight) + row;
  // int16_t w = _fontWidth * _maxRowLength;
  // int16_t h = _fontHeight;
  // _oled->fillRect(x, y, w, h, backgroundColour);
  // _oled->display();
}

void OLEDScreen::writeRow(uint8_t row, uint8_t column, uint16_t fontColour, uint16_t backgroundColour,
                          uint8_t maxLength, char *message, bool underlined) {
  // uint16_t x = column;
  // uint16_t y = (row * _fontHeight) + _fontHeight;
  // _oled->setTextColor(fontColour);
  // _oled->setCursor(x, y);
  // _oled->print(message);
  // if (underlined) {
  //   _oled->drawLine(column, y + 1, _oled->width(), y + 1, fontColour);
  // } else {
  //   _oled->drawLine(column, y + 1, _oled->width(), y + 1, backgroundColour);
  // }
  // _oled->display();
  CONSOLE.print(F("\nwriteRow textRow|message: "));
  CONSOLE.print(y);
  CONSOLE.print(F("|"));
  CONSOLE.println(message);
}

void OLEDScreen::writeLine(uint8_t row, uint8_t column, uint8_t lineLength, uint16_t lineColour,
                           uint16_t backgroundColour) {
  // Horizontal start/end
  // int16_t x1 = column;
  // int16_t x2 = _fontWidth * lineLength;
  // // Vertical start - half way up the font height
  // int16_t y1 = (row * _fontHeight) + row + (_fontHeight / 2);
  // int16_t y2 = y1;
  // clearRow(row, backgroundColour);
  // _oled->drawLine(x1, y1, x2, y2, lineColour);
  // _oled->display();
}

uint16_t OLEDScreen::getHeight() { /*return _oled->height();*/ }

uint16_t OLEDScreen::getWidth() { /*return _oled->width();*/ }

uint8_t OLEDScreen::_getTextWidth() {
  // int16_t x1, y1;
  // uint16_t w, h;
  // _oled->getTextBounds("A", 0, 0, &x1, &y1, &w, &h);
  // return w;
  return 0;
}

void OLEDScreen::_switchMUX() {
  if (_muxAddress == 0 || _subBus == 255) {
    return;
  }
  Wire.beginTransmission(_muxAddress);
  Wire.write(_subBus);
  Wire.endTransmission();
}

#endif
