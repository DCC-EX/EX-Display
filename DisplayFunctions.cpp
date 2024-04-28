#include "Defines.h"
#include "DisplayFunctions.h"
#include "EXDisplayClass.h"

#ifdef DEBUG
bool debug = true;
#else
bool debug = false;
#endif
unsigned long lastRowDisplay = 0;

void updateEXDisplayRow(uint8_t screenId, uint8_t screenRow, char *text) {
  if (screenId >= MAX_SCREENS || screenRow >= MAX_ROWS) {
    return;
  }
  CONSOLE.print(F("\nCallback activated for screen|row|text: "));
  CONSOLE.print(screenId);
  CONSOLE.print(F("|"));
  CONSOLE.print(screenRow);
  CONSOLE.print(F("|"));
  CONSOLE.println(text);
  EXDisplay *display = EXDisplay::getDisplayByNumber(screenId);
  if (!display) {
    display = new EXDisplay(screenId, MAX_ROWS, MAX_LINE_LENGTH, MAX_LINE_LENGTH);
  }
  display->updateRow(screenRow, text);
}

void displayChangedRows() {
  for (EXDisplay *display = EXDisplay::getFirst(); display; display = display->getNext()) {
    for (EXDisplayRow *row = display->getFirstRow(); row; row = row->getNext()) {
      if (row->isChanged()) {
        CONSOLE.print(F("Changed row|text|ticker: "));
        CONSOLE.print(row->getRowNumber());
        CONSOLE.print(F("|"));
        CONSOLE.print(row->getRowText());
        CONSOLE.print(F("|"));
        CONSOLE.println(row->isTicker());
      }
    }
  }
}

void displayAllRows(unsigned long delay) {
  unsigned long timeNow = millis();
  if (timeNow - lastRowDisplay >= delay) {
    lastRowDisplay = timeNow;
    for (EXDisplay *display = EXDisplay::getFirst(); display; display = display->getNext()) {
      CONSOLE.print(F("\n\nDisplay|maxRows|maxRowWidth|maxTextWidth|autoTicker: "));
      CONSOLE.print(display->getDisplayNumber());
      CONSOLE.print(F("|"));
      CONSOLE.print(display->getMaxRows());
      CONSOLE.print(F("|"));
      CONSOLE.print(display->getMaxRowWidth());
      CONSOLE.print(F("|"));
      CONSOLE.print(display->getMaxTextWidth());
      CONSOLE.print(F("|"));
      CONSOLE.println(display->isAutoTicker());
      CONSOLE.println(F("\nRow|Text|Ticker"));
      for (EXDisplayRow *row = display->getFirstRow(); row; row = row->getNext()) {
        CONSOLE.print(row->getRowNumber());
        CONSOLE.print(F("|"));
        CONSOLE.print(row->getRowText());
        CONSOLE.print(F("|"));
        CONSOLE.println(row->isTicker());
      }
    }
  }
}
