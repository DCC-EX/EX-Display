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

TFT_eSPIDisplay::TFT_eSPIDisplay() {
  _tft = new TFT_eSPI();
  _backgroundColour = 0x0000;
  _textColour = 0xFFFF;
}

void TFT_eSPIDisplay::begin() {
  _tft->init();
  _tft->setFreeFont(&FreeMono12pt7b);
  _tft->setTextSize(1);
  _tft->setRotation(1);
  _tft->setTextColor(_textColour);
  _tft->fillScreen(_backgroundColour);
}

void TFT_eSPIDisplay::clearScreen() { _tft->fillScreen(_backgroundColour); }

void TFT_eSPIDisplay::displayRow(int row, const char *text, bool underlined, int column) {}

void TFT_eSPIDisplay::clearRow(int row) {}

void TFT_eSPIDisplay::displayStartupInfo(const char *version) {
  LOG(LogLevel::DEBUG, "TFT_eSPIDisplay::displayStartupInfo(%s)", version);
  _tft->fillScreen(_backgroundColour);
  _tft->drawString("EX-Display", 0, 20);
  _tft->drawString("Version: ", 0, 40);
  _tft->drawString(version, 100, 40);
}

TFT_eSPI *TFT_eSPIDisplay::getTFT_eSPIInstance() { return _tft; }

TFT_eSPIDisplay::~TFT_eSPIDisplay() {}

#endif // PIO_UNIT_TESTING
