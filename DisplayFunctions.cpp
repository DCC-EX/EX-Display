#include "Defines.h"
#include "DisplayFunctions.h"
#include "MCUFriendScreen.h"

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
  display->redrawDisplay();
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
