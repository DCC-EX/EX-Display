/*
 *  © 2025 Peter Cole
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

#include "DisplayInterface.h"

void DisplayInterface::setNext(DisplayInterface *display) { _next = display; }

DisplayInterface *DisplayInterface::getNext() { return _next; }

void DisplayInterface::setLogger(Logger *logger) { _logger = logger; }

void DisplayInterface::setId(uint8_t displayId) { _displayId = displayId; }

uint8_t DisplayInterface::getId() { return _displayId; }

void DisplayInterface::setScreenId(int screenId) {
  _needsRedraw = true;
  _screenId = screenId;
}

int DisplayInterface::getScreenId() { return _screenId; }

int DisplayInterface::getCSPin() { return _csPin; }

void DisplayInterface::setNeedsRedraw(bool redraw) { _needsRedraw = redraw; }

bool DisplayInterface::needsRedraw() { return _needsRedraw; }

void DisplayInterface::formatRow(DisplayInterface *display, int rowId, const char *text) {
  RowAttributes attributes = {false, false, false, false,
                              0xFFFF}; /** We need to return RowAttributes, set them false to start with white text */
  /** We're starting just looking for initial modifiers, no colours, so if our first char is not a ` then we have no
   * modifier and should just call our display method with everything as is. */
  int textLength = strlen(text) + 1;
  for (int i = 0; i < textLength; i++) {
    char check = text[i];
    if (check != '`') {
      display->displayFormattedRow(rowId, 0, attributes, text, false);
      return;
    }
  }
}
