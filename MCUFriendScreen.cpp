#include "Defines.h"
#include "MCUFriendScreen.h"


MCUFriendScreen::MCUFriendScreen(uint8_t maxRows, uint8_t maxColumns) : EXScreen(maxRows, maxColumns) {
  MCUFRIEND_kbv _tft;
}

void EXScreen::writeRow(uint8_t row, uint8_t column, uint8_t colour, char *message) {
  // Method here to write to the display

    tft.setFont(&Arial9pt7b); // may need to make this variable
    tft.setTextColor(colour);
    tft.setCursor(column, row); 
    tft.setTextSize(1);
    tft.print(message);

}

void EXScreen::newPage(uint8_t screenId) {
  // Method here to write new page to the display
    CONSOLE.println("New Page");
    tft.fillScreen(BLACK);
    char header[25] = {""};
    sprintf(header, "DCC-EX   SCREEN %d\n", screenId);
    tft.setTextColor(YELLOW);
    showmsgXY(1, 20, 1, header);
    tft.drawFastHLine(0, 25, tft.width(), WHITE);
    tft.setTextColor(WHITE);  // set this for all screen lines
    
void EXScreen::writeRow(uint8_t row, char *message) {
  // Method here to write to the display
  CONSOLE.print(F("Write to screen DisplayRow|Message: "));
  CONSOLE.print(row);
  CONSOLE.print(F("|"));
  CONSOLE.println(message);
}

void EXSCREEN::startUp(uint8_t rotation, int8_t colour) {
  // method to initalise display
  uint16_t ID = tft.readID();
    CONSOLE.print("TFT ID = 0x");
    CONSOLE.println(ID, HEX);
  if (ID == 0xD3D3) ID = 0x9486; // write-only shield
  tft.begin(ID);
  
  tft.setRotation(rotation);           
  tft.setTextColor(colour); 
  tft.fillScreen(BLACK);

}