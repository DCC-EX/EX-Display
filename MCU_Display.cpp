/*
 *  © 2024 Peter Cole
 *  © 2025 Colin Murdoch
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

#include "MCU_Display.h"

// Do not load when testing, TFT_eSPI library is incompatible and will cause failures.
#ifndef PIO_UNIT_TESTING

MCUFRIEND_kbv *MCU_Display::_tft = nullptr;  // set up a tft instance with  the MCUFRIEND drivers
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
bool MCU_Display::_tftInitialised = false;

MCU_Display::MCU_Display(uint8_t rotation, const GFXfont *textFont, uint16_t textColour,
                                 uint16_t backgroundColour) {
  _rotation = rotation;
  _textSize = 1; // default text size to save amending display routine.
  _textColour = textColour;
  _backgroundColour = backgroundColour;
  if (_tft == nullptr) {
    _tft = new MCUFRIEND_kbv();
  }
  _gfxFont = textFont;
}

MCU_Display::begin() {
  LOG(LogLevel::LOG_DEBUG, "MCU_Display::begin[%d]()", _displayId);
  if (!_tftInitialised) {
    uint16_t ID = _tft->readID();
    // Serial.print("TFT ID = 0x");
    // Serial.println(ID, HEX);
    // Serial.println("Calibrate for your Touch Panel");
    if (ID == 0xD3D3) ID = 0x9486; // write-only shield
    _tft->begin(ID);
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
      "MCU_Display[%d] settings: "
      "_textSize=%d|_rotation=%d|_textColour=0x%04X|_backgroundColour=0x%04X|_csPin=%d|_fontHeight=%d|_fontWidth=%d|_"
      "maxRow=%d|_"
      "maxColumn=%d",
      _displayId, _textSize, _rotation, _textColour, _backgroundColour, _csPin, _fontHeight, _fontWidth, _maxRow,
      _maxColumn);
  _tft->fillScreen(_backgroundColour);

}

void MCU_Display::clearScreen() {
  LOG(LogLevel::LOG_DEBUG, "MCU_Display::clearScreen[%d]() - colour 0x%04X", _displayId, _backgroundColour);
  _tft->fillScreen(_backgroundColour);
}

void MCU_Display::displayScreen(Screen *screen) {
  // If this display needs redrawing, clear first then process rows
  // Must set a local redraw flag here so we can clear the instance for next time
  if (_needsRedraw) {
    clearScreen();
  }
  for (ScreenRow *row = screen->getFirstScreenRow(); row; row = row->getNext()) {
    if (row->needsRedraw() || _needsRedraw) {
      formatRow(row->getId(), row->getText());
    }
  }
  // Now we've redrawn, clear the flag
  _needsRedraw = false;
}

void MCU_Display::clearRow(uint8_t row) {
  LOG(LogLevel::LOG_DEBUG, "MCU_Display::clearRow[%d](%d)", _displayId, row);
  _tft->setFreeFont(_gfxFont);
  int32_t x = 0;
  int32_t y = 0;
  _getRowPosition(0, row, x, y);
  _tft->fillRect(x, y, _tft->width(), _fontHeight, _backgroundColour);
}

void MCU_Display::displayStartupInfo(const char *version) {
  LOG(LogLevel::LOG_DEBUG, "MCU_Display::displayStartupInfo[%d](%s)", _displayId, version);
  _tft->setRotation(_rotation);
  _tft->setFreeFont(_gfxFont);
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

void MCU_Display::displayFormattedRow(uint8_t row, uint8_t column, RowAttributes attributes, const char *text,
                                          bool append) {
  LOG(LogLevel::LOG_DEBUG, "MCU_Display::displayFormattedRow(%d, %d, {%d, %d, %d, %d, %d, 0x%04X}, %s, %d)", row,
      column, attributes.colourSet, attributes.isUnderlined, attributes.isLine, attributes.alwaysTicker,
      attributes.neverTicker, attributes.textColour, text, append);
  if (text == nullptr) {
    return;
  }
  _tft->setFreeFont(_gfxFont);
  int32_t x = 0;
  int32_t y = 0;
  _getRowPosition(column, row, x, y);
  uint16_t colour;
  if (attributes.colourSet) { // Set custom colour if set
    colour = attributes.textColour;
  } else { // Otherwise use display default
    colour = _textColour;
  }
  LOG(LogLevel::LOG_DEBUG, "setTextColour(0x%04X)", colour);
  _tft->setTextColor(colour);
  if (!append) { // If this isn't appending to existing text, clear the row first
    clearRow(row);
  }
  if (attributes.isLine) { // Draw horizontal line if it is
    int32_t x1 = 0;
    int32_t x2 = _tft->width();
    // Vertical start - half way up the font height
    int32_t y1 = y + (_fontHeight / 2);
    int32_t y2 = y1;
    LOG(LogLevel::LOG_DEBUG, "drawLine(x1=%d, y1=%d, x2=%d, y2=%d, 0x%04X)", x1, y1, x2, y2, colour);
    _tft->drawLine(x1, y1, x2, y2, colour);
  } else { // Otherwise underline if flagged, and draw text
    if (attributes.isUnderlined) {
      _tft->drawLine(0, y + _fontHeight - 1, _tft->width(), y + _fontHeight - 1, colour);
    }
    _tft->drawString(text, x, y);
  }
}

TFT_eSPI *MCU_Display::getTFT_eSPIInstance() {
  LOG(LogLevel::LOG_DEBUG, "MCU_Display::getTFT_eSPIInstance[%d]", _displayId);
  return _tft;
}

bool MCU_Display::tftInitialised() { return _tftInitialised; }

MCU_Display *MCU_Display::create(uint8_t rotation, const GFXfont *textFont, uint16_t textColour,
                                         uint16_t backgroundColour) {
  MCU_Display *newDisplay = new MCU_Display(rotation, textFont, textColour, backgroundColour);
  return newDisplay;
}

MCU_Display::~MCU_Display() {
  delete _tft;
  _tft = nullptr;
}

void MCU_Display::_getRowPosition(uint8_t column, uint8_t row, int32_t &x, int32_t &y) {
  LOG(LogLevel::LOG_DEBUG, "MCU_Display::_getRowPosition[%d](%d, %d, %d, %d)", _displayId, column, row, x, y);
  x = column * _fontWidth;
  y = (row * _fontHeight);
  LOG(LogLevel::LOG_DEBUG, "MCU_Display::_getRowPosition[%d] x=%d|_fontWidth=%d|y=%d|_fontHeight=%d", _displayId, x,
      _fontWidth, y, _fontHeight);
}

#endif //PIO_UNIT_TESTING