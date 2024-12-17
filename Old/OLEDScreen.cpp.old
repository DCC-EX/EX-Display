#include "Defines.h"
#ifdef NEEDS_OLED
#include "OLEDScreen.h"

OLEDScreen::OLEDScreen(uint8_t screenWidth, uint8_t screenHeight, uint8_t deviceAddress, uint8_t muxAddress,
                       uint8_t subBus)
    : PhysicalScreen(), _screenWidth(screenWidth), _screenHeight(screenHeight), _deviceAddress(deviceAddress),
      _muxAddress(muxAddress), _subBus(subBus) {
  if ((_screenHeight != 32 && _screenHeight != 64) || (_screenWidth != 128 && _screenHeight != 132)) {
    CONSOLE.println(F("Invalid screen width/height specified"));
    return;
  }
  _oled = new SSD1306AsciiWire;
  _textSize = 1;
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
  if (rotation == 1) {
    _oled->displayRemap(true);
  }
  _oled->setFont(TEXT_FONT);
  if (textSize == 2) {
    _textSize = 2;
    _oled->set2X();
  } else {
    _oled->set1X();
  }
  _oled->clear();
  // _fontHeight = _oled->fontHeight();
  _fontHeight = 8 * _textSize; // This is pretty much hard coded by the library for row calculations
  _fontWidth = _oled->fontWidth();
  _maxRows = _oled->displayHeight() / _fontHeight;
  _maxRowLength = _oled->displayWidth() / _fontWidth;
  CONSOLE.print(F("Setup done: _fontHeight|_fontWidth|_oled->Height|_oled->Width: "));
  CONSOLE.print(_fontHeight);
  CONSOLE.print(F("|"));
  CONSOLE.print(_fontWidth);
  CONSOLE.print(F("|"));
  CONSOLE.print(_oled->displayHeight());
  CONSOLE.print(F("|"));
  CONSOLE.println(_oled->displayWidth());
  return this;
}

void OLEDScreen::clearScreen(uint16_t backgroundColour) {
  _switchMUX();
  _oled->clear();
}

void OLEDScreen::clearRow(uint8_t row, uint16_t backgroundColour) {
  _switchMUX();
  _oled->setCursor(0, row * _textSize);
  _oled->clearToEOL();
}

void OLEDScreen::writeRow(uint8_t row, uint8_t column, uint16_t fontColour, uint16_t backgroundColour,
                          uint8_t maxLength, char *message, bool underlined) {
  _switchMUX();
  _oled->setCursor(column, row * _textSize);
  _oled->print(message);
  CONSOLE.print(F("\nwriteRow textRow|message: "));
  CONSOLE.print(row);
  CONSOLE.print(F("|"));
  CONSOLE.println(message);
}

void OLEDScreen::writeLine(uint8_t row, uint8_t column, uint8_t lineLength, uint16_t lineColour,
                           uint16_t backgroundColour) {}

uint16_t OLEDScreen::getHeight() { return _oled->displayHeight(); }

uint16_t OLEDScreen::getWidth() { return _oled->displayWidth(); }

void OLEDScreen::_switchMUX() {
  if (_muxAddress == 0 || _subBus == 255) {
    return;
  }
  Wire.beginTransmission(_muxAddress);
  Wire.write(_subBus);
  Wire.endTransmission();
}

#endif
