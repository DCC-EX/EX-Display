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
    display->updateRow(screenRow, text);
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
