#include "Defines.h"
#include "MCUFriendScreen.h"


MCUFriendScreen::MCUFriendScreen(uint8_t maxRows, uint8_t maxColumns) : EXScreen(maxRows, maxColumns) {
  MCUFRIEND_kbv _tft;
}

void EXScreen::writeRow(uint8_t row, char *message) {
  // Method here to write to the display
  CONSOLE.print(F("Write to screen DisplayRow|Message: "));
  CONSOLE.print(row);
  CONSOLE.print(F("|"));
  CONSOLE.println(message);
}
