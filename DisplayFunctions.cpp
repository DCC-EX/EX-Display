#include "Defines.h"
#include "DisplayFunctions.h"

#ifdef DEBUG
bool debug = true;
#else
bool debug = false;
#endif

// This function is called from AtFinder when a
// <@ screenid row "text"> message is discovered.

void updateDisplayRow(uint8_t screenId, uint8_t screenRow, char *text) {

  // special diagnostic to dump buffers on request
  if (screenId == 255) {
    displayAllRows();
    return;
  }

  for (PhysicalScreen *screen = PhysicalScreen::getFirst(); screen; screen = screen->getNext()) {
    for (LogicalDisplay *display = screen->getFirstDisplay(); display; display = display->getNext()) {
      if (display->getDisplayNumber() == screenId) {
        display->updateRow(screenRow, text);
        return;
      }
    }
  }
}

void updateScreen() {
  for (PhysicalScreen *screen = PhysicalScreen::getFirst(); screen; screen = screen->getNext()) {
#ifdef SCROLLTIME
    for (LogicalDisplay *display = screen->getFirstDisplay(); display; display = display->getNext()) {
      display->autoScroll(SCROLLTIME);
    }
#endif
#ifdef DISPLAY_SWITCH_TIME
    screen->autoSwitch(DISPLAY_SWITCH_TIME);
#endif
    screen->processActiveDisplay();
  }
}

void displayAllRows() {
  for (PhysicalScreen *screen = PhysicalScreen::getFirst(); screen; screen = screen->getNext()) {
    CONSOLE.print(F("\n~~ All displays and rows for screen "));
    CONSOLE.print(screen->getScreenNumber());
    CONSOLE.println(F(" ~~"));

    for (LogicalDisplay *display = screen->getFirstDisplay(); display; display = display->getNext()) {
      CONSOLE.print(F("\nRows for display "));
      CONSOLE.println(display->getDisplayNumber());
      CONSOLE.println(F("Row|Display Row|Message|isChanged|needsRender"));
      for (LogicalDisplayRow *row = display->getFirstRow(); row; row = row->getNext()) {
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
}
