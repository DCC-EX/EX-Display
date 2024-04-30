#include "Defines.h"
#include "DisplayFunctions.h"
#include "EXDisplayClass.h"
#include "EXScreen.h"

#ifdef DEBUG
bool debug = true;
#else
bool debug = false;
#endif
unsigned long lastRowDisplay = 0;

// This function is called from AtFinder when a 
// <@ screenid row "text"> message is discovered.

void updateEXDisplayRow(uint8_t screenId, uint8_t screenRow, char *text) {
  
  // special diagnostic to dump buffers on request
  if (screenId==255) {
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
    ScreenChanged[screenId]=true;
    // If this is the current screen we could call a row update line directly from here
    // but do we know which screen row to use?
    // PrintThisLine(screenId, screenRow, text)
  }
  else {
    CONSOLE.print("\nCallback ignored for screen ");
    CONSOLE.println(screenId);
  }
  
}


void displayAllRows() {
    for (EXDisplay *display = EXDisplay::getFirst(); display; display = display->getNext()) {
      CONSOLE.print(F("\n\nDisplay: "));
      CONSOLE.print(display->getDisplayNumber());
      CONSOLE.println(F("|"));
      for (EXDisplayRow *row = display->getFirstRow(); row; row = row->getNext()) {
        CONSOLE.print(row->getRowNumber());
        CONSOLE.print(F("|"));
        CONSOLE.println(row->getRowText());
      }
    }
  }
