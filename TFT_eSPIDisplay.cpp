/*
 *  © 2024 Peter Cole
 *
 *  This is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  It is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this code.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "TFT_eSPIDisplay.h"

// Do not load when testing, TFT_eSPI library is incompatible and will cause failures.
#ifndef PIO_UNIT_TESTING

TFT_eSPI *TFT_eSPIDisplay::_tft = nullptr;
bool TFT_eSPIDisplay::_tftInitialised = false;

//TFT_eSPIDisplay::TFT_eSPIDisplay(uint8_t rotation, uint8_t textSize, uint16_t textColour, uint16_t backgroundColour) {
TFT_eSPIDisplay::TFT_eSPIDisplay(uint8_t rotation, const GFXfont *textFont, uint16_t textColour, uint16_t backgroundColour) {
  _rotation = rotation;
  //_textSize = textSize;
  _textSize = 1; // default text size to save amending display routine.
  _textColour = textColour;
  _backgroundColour = backgroundColour;
  if (_tft == nullptr) {
    _tft = new TFT_eSPI();
  }
  _gfxFont = textFont;
  // switch (textSize) {
  //   case 1:
  //     _gfxFont = TEXT_FONT;
  //     break;
  //   case 2:
  //     _gfxFont = ALTERNATE_FONT1;
  //   case 3:
  //     _gfxFont = ALTERNATE_FONT2;
  //     break;
  //   default:
  //     _gfxFont = TEXT_FONT;
  //     break;
  // }
}

TFT_eSPIDisplay::TFT_eSPIDisplay(uint8_t rotation, const GFXfont *textFont, uint16_t textColour, uint16_t backgroundColour,
                                 int csPin) {
  _rotation = rotation;
  _textSize = 1;    // default text size to save amending display routine.
  _textColour = textColour;
  _backgroundColour = backgroundColour;
  _csPin = csPin;
  if (_tft == nullptr) {
    _tft = new TFT_eSPI();
  }
  _gfxFont = textFont;
  // switch (textSize) {
  //   case 1:
  //     _gfxFont = TEXT_FONT;
  //     break;
  //   case 2:
  //     _gfxFont = ALTERNATE_FONT1;
  //   case 3:
  //     _gfxFont = ALTERNATE_FONT2;
  //     break;
  //   default:
  //     _gfxFont = TEXT_FONT;
  //     break;
  // }
  
}


void TFT_eSPIDisplay::begin() {
  LOG(LogLevel::LOG_DEBUG, "TFT_eSPIDisplay::begin[%d]()", _displayId);
  if (!_tftInitialised) {
    _tft->init();
    _tftInitialised = true;
  }
  _tft->setTextSize(_textSize);
  _tft->setRotation(_rotation);
  _tft->setTextColor(_textColour);
  _tft->setFreeFont(_gfxFont);
  _fontHeight = _gfxFont->yAdvance;
  _fontWidth = _tft->textWidth("A");
  _maxRow = _tft->height() / _fontHeight;
  _maxColumn = _tft->width() / _fontWidth;
  LOG(LogLevel::LOG_DEBUG,
      "TFT_eSPIDisplay[%d] settings: "
      "_textSize=%d|_rotation=%d|_textColour=0x%04X|_backgroundColour=0x%04X|_csPin=%d|_fontHeight=%d|_fontWidth=%d|_"
      "maxRow=%d|_"
      "maxColumn=%d",
      _displayId, _textSize, _rotation, _textColour, _backgroundColour, _csPin, _fontHeight, _fontWidth, _maxRow,
      _maxColumn);
  _tft->fillScreen(_backgroundColour);
}

void TFT_eSPIDisplay::clearScreen() {
  LOG(LogLevel::LOG_DEBUG, "TFT_eSPIDisplay::clearScreen[%d]() - colour 0x%04X", _displayId, _backgroundColour);
  _tft->fillScreen(_backgroundColour);
}

void TFT_eSPIDisplay::displayScreen(Screen *screen) {
  // If this display needs redrawing, clear first then process rows
  // Must set a local redraw flag here so we can clear the instance for next time
  if (_needsRedraw) {
    clearScreen();
  }
  for (ScreenRow *row = screen->getFirstScreenRow(); row; row = row->getNext()) {
    if (row->needsRedraw() || _needsRedraw) {
      displayRow(row->getId(), row->getText(), false, 0);
    }
  }
  // Now we've redrawn, clear the flag
  _needsRedraw = false;
}

void TFT_eSPIDisplay::displayRow(uint8_t row, const char *text, bool underlined, uint8_t column) {
  if (text == nullptr) {
    return;
  }
  int32_t x = 0;
  int32_t y = 0;
  _getRowPosition(column, row, x, y);
  LOG(LogLevel::LOG_DEBUG, "TFT_eSPIDisplay::displayRow[%d](%d, %s, %d, %d) at X=%d|Y=%d", _displayId, row, text,
      underlined, column, x, y);
  _tft->setTextColor(_textColour);
  LOG(LogLevel::LOG_DEBUG, "setTextColour(0x%04X)", _textColour);
  if (column == 0) {
    clearRow(row);
  }
  _tft->drawString(text, x, y);
}

void TFT_eSPIDisplay::clearRow(uint8_t row) {
  LOG(LogLevel::LOG_DEBUG, "TFT_eSPIDisplay::clearRow[%d](%d)", _displayId, row);
  int32_t x = 0;
  int32_t y = 0;
  _getRowPosition(0, row, x, y);
  _tft->fillRect(x, y, _tft->width(), _fontHeight, _backgroundColour);
}

void TFT_eSPIDisplay::displayStartupInfo(const char *version) {
  LOG(LogLevel::LOG_DEBUG, "TFT_eSPIDisplay::displayStartupInfo[%d](%s)", _displayId, version);
  _tft->fillScreen(0xFFFF);
  int32_t x = 0;
  int32_t y = 0;
  _tft->setTextColor(0x01C8);
  _getRowPosition(0, 0, x, y);
  _tft->drawString("DCC-", x, y);
  _tft->setTextColor(0x03B6);
  _getRowPosition(4, 0, x, y);
  _tft->drawString("EX", x, y);
  _tft->setTextColor(0x01C8);
  _getRowPosition(0, 1, x, y);
  _tft->drawString("EX-Display", x, y);
  _getRowPosition(0, 2, x, y);
  _tft->drawString("Version: ", x, y);
  _tft->setTextColor(0x03B6);
  _getRowPosition(9, 2, x, y);
  _tft->drawString(version, x, y);
}

TFT_eSPI *TFT_eSPIDisplay::getTFT_eSPIInstance() {
  LOG(LogLevel::LOG_DEBUG, "TFT_eSPIDisplay::getTFT_eSPIInstance[%d]", _displayId);
  return _tft;
}

bool TFT_eSPIDisplay::tftInitialised() { return _tftInitialised; }

// TFT_eSPIDisplay *TFT_eSPIDisplay::create(uint8_t rotation, uint8_t textSize, uint16_t textColour,
//                                          uint16_t backgroundColour) {
//   TFT_eSPIDisplay *newDisplay = new TFT_eSPIDisplay(rotation, textSize, textColour, backgroundColour);
//   return newDisplay;
// }
TFT_eSPIDisplay *TFT_eSPIDisplay::create(uint8_t rotation, const GFXfont *textFont, uint16_t textColour,
                                         uint16_t backgroundColour) {
  TFT_eSPIDisplay *newDisplay = new TFT_eSPIDisplay(rotation, textFont, textColour, backgroundColour);
  return newDisplay;
}

TFT_eSPIDisplay *TFT_eSPIDisplay::create(uint8_t rotation, const GFXfont *textFont, uint16_t textColour,
                                         uint16_t backgroundColour, int csPin) {
  TFT_eSPIDisplay *newDisplay = new TFT_eSPIDisplay(rotation, textFont, textColour, backgroundColour, csPin);
  return newDisplay;
}

TFT_eSPIDisplay::~TFT_eSPIDisplay() {
  delete _tft;
  _tft = nullptr;
}

void TFT_eSPIDisplay::_getRowPosition(uint8_t column, uint8_t row, int32_t &x, int32_t &y) {
  LOG(LogLevel::LOG_DEBUG, "TFT_eSPIDisplay::_getRowPosition[%d](%d, %d, %d, %d)", _displayId, column, row, x, y);
  x = column * _fontWidth;
  y = (row * _fontHeight);
  LOG(LogLevel::LOG_DEBUG, "TFT_eSPIDisplay::_getRowPosition[%d] x=%d|_fontWidth=%d|y=%d|_fontHeight=%d", _displayId, x,
      _fontWidth, y, _fontHeight);
}

#endif // PIO_UNIT_TESTING
