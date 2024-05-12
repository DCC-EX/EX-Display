#include "Defines.h"
#include "DisplayFunctions.h"

#ifdef DEBUG
bool debug = true;
#else
bool debug = false;
#endif

// This function is called from AtFinder when a
// <@ screenid row "text"> message is discovered.

void updateEXDisplayRow(uint8_t screenId, uint8_t screenRow, char *text) {

  // special diagnostic to dump buffers on request
  if (screenId == 255) {
    displayAllRows();
    return;
  }

  EXDisplay *display = EXDisplay::getDisplayByNumber(screenId);
  if (display) {
    if (embeddedColours(text)) {
      uint16_t textColour;
      uint16_t backgroundColour;
      extractColours(text, &textColour, &backgroundColour);
      display->updateRowColours(screenRow, textColour, backgroundColour);
    } else if (embeddedAttributes(text)) {
      uint8_t attributes;
      extractAttributes(text, &attributes);
      display->updateRowAttributes(screenRow, attributes);
    } else {
      display->updateRowText(screenRow, text);
      CONSOLE.print(F("\nCallback activated for screen|row|text: "));
      CONSOLE.print(screenId);
      CONSOLE.print(F("|"));
      CONSOLE.print(screenRow);
      CONSOLE.print(F("|"));
      CONSOLE.println(text);
      // Set a flag so the screen driver knows something has changed.
      // ScreenChanged[screenId]=true;
      // If this is the current screen we could call a row update line directly from here
      // but do we know which screen row to use?
      // PrintThisLine(screenId, screenRow, text)
    }
  } else {
    CONSOLE.print("\nCallback ignored for screen ");
    CONSOLE.println(screenId);
  }
}

void updateScreen() {
  EXDisplay *display = EXDisplay::getActiveDisplay();
#ifdef SCROLLTIME
  display->autoScroll(SCROLLTIME);
#endif
#ifdef DISPLAY_SWITCH_TIME
  display->autoSwitch(DISPLAY_SWITCH_TIME);
#endif
  display->processDisplay();
}

void displayAllRows() {
  for (EXDisplay *display = EXDisplay::getFirst(); display; display = display->getNext()) {
    CONSOLE.print(F("\n\nRows for display "));
    CONSOLE.println(display->getDisplayNumber());
    CONSOLE.println(F("Row|Display Row|Message|isChanged|needsRender"));
    for (EXDisplayRow *row = display->getFirstRow(); row; row = row->getNext()) {
      CONSOLE.print(row->getRowNumber());
      CONSOLE.print(F("|"));
      CONSOLE.print(row->getDisplayRow());
      CONSOLE.print(F("|"));
      CONSOLE.print(row->getRowText());
      CONSOLE.print(F("|"));
      CONSOLE.print(row->isChanged());
      CONSOLE.print(F("|"));
      CONSOLE.println(row->needsRender());
    }
  }
}

bool embeddedColours(const char *message) {
  // Check for format #0x0000#0x0000#
  if (message[0] != '#' || message[7] != '#' || message[strlen(message) - 1] != '#') {
    return false;
  }
  // Find the positions of the three '#' characters
  char *start = strchr(message, '#');
  if (start == NULL) {
    return false;
  }
  char *middle = strchr(start + 1, '#');
  if (middle ==NULL) {
    return false;
  }
  char *end = strchr(middle + 1, '#');
  if (end == NULL) {
    return false;
  }
  // Check if the hexadecimal values are of the correct length (6 characters)
  if (end - middle - 1 != 6 || middle - start - 1 != 6) {
    return false;
  }
  // Check if the characters between the '#' are valid hexadecimal digits
  if (message[1] != '0' || message[2] != 'x' || middle[1] != '0' || middle[2] != 'x') {
    return false;
  }
  for (const char *p = message + 3; p < middle; p++) {
    if (!((p[0] >= '0' && p[0] <= '9') || (p[0] >= 'A' && p[0] <= 'F'))) {
      return false;
    }
  }
  for (const char *p = middle + 3; p < end; p++) {
    if (!((p[0] >= '0' && p[0] <= '9') || (p[0] >= 'A' && p[0] <= 'F'))) {
      return false;
    }
  }
  return true;
}

void extractColours(char *message, uint16_t *textColour, uint16_t *backgroundColour) {
  // Find first #
  char *start = strchr(message, '#');
  // Convert text colour
  char *endPointer;
  *textColour = (uint16_t)strtol(start + 1, &endPointer, 16);
  // Find next #
  start = strchr(start + 1, '#');
  // Convert background colour
  *backgroundColour = (uint16_t)strtol(start + 1, &endPointer, 16);
}

bool embeddedAttributes(const char *message) {
  // Check for format #00000000#
  if (message[0] != '#' || message[strlen(message) - 1] != '#') {
    return false;
  }
  // Find the positions of the two '#' characters
  char *start = strchr(message, '#');
  if (start == NULL) {
    return false;
  }
  char *end = strchr(start + 1, '#');
  if (end == NULL) {
    return false;
  }
  // Validate that each char is a 0 or 1 only
  for (const char *p = message + 1; p < end; p++) {
    if (!(p[0] >= '0' && p[0] <= '1')) {
      return false;
    }
  }
  return true;
}

void extractAttributes(char *message, uint8_t *attributes) {
  // Find first @
  char *start = strchr(message, '#');
  // Convert text colour
  char *endPointer;
  *attributes = (uint8_t)strtol(start + 1, &endPointer, 10);
}
