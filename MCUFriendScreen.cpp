#include "MCUFriendScreen.h"

MCUFriendScreen::MCUFriendScreen(uint8_t maxRows, uint8_t maxColumns) : EXScreen(maxRows, maxColumns) {
  MCUFRIEND_kbv _tft;
}

void EXScreen::writeRow(uint8_t row, uint8_t column, char *message) {
  // Method here to write to the display
}
