/*
 *  © 2024, Matt Bidwell, Paul Antoine, Colin Murdoch, Chris Harlow
 *  All rights reserved.
 *
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
 *  along with CommandStation.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <Arduino.h>
#include <MCUFRIEND_kbv.h>
#include <Adafruit_GFX.h>
#include "config.h"
#include "EXScreen.h"
#include "Defines.h"
#include "DisplayFunctions.h"
#include "EXDisplayRow.h"
#include "EXDisplayClass.h"

MCUFRIEND_kbv tft;

#include "Arial9pt7b.h"
//#include "FreeSans12pt7b.h"


int ScreenLines;


void TFT_Startup()
{

    uint16_t ID = tft.readID();
    CONSOLE.print("TFT ID = 0x");
    CONSOLE.println(ID, HEX);
    // #ifdef DEBUG
    // CONSOLE.println("Calibrate for your Touch Panel");
    // #endif
    //if (ID == 0xD3D3) ID = 0x9486; // write-only shield

    tft.begin(ID);
  
    tft.setRotation(1);           
    tft.setTextColor(0xFFFF); 
    tft.fillScreen(BLACK);

    // create a string of blanks for the display.
    // This does not seem necessary as we draw the whole screen.
    // for (byte x=0; x<=MAX_LINE_LENGTH; x++){
    //   blankmsg[x]=' ';
    // }
    // blankmsg[MAX_LINE_LENGTH+1]='\0';

    SCREEN::StartScreenPrint();

}

void showmsgXY(int x, int y, int sz, const char *msg)
{
    tft.setFont();
    tft.setFont(&Arial9pt7b);
    tft.setCursor(x, y); 
    tft.setTextSize(sz);
    tft.print(msg);
       
}

void setScreenRows(uint8_t rowId) {


}

void CheckScreens(){

    if (ScreenChanged[currentScreenID]==true) {
        CONSOLE.print("Time to draw a screen");
        SCREEN::StartScreenPrint();
        PrintInProgress=false;
        ScreenChanged[currentScreenID] = false;
          
        EXDisplay *display = EXDisplay::getDisplayByNumber(currentScreenID);
        if (display) {
            EXDisplayRow *row = display->getFirstRow();
            CONSOLE.println("Pinting a line");
            SCREEN::PrintALine(row->getRowNumber(), row->getRowText());
            PrintInProgress=true;
        }
        else {
          SCREEN::PrintNoData();
        }
      } 
      else {
        if (PrintInProgress) {
            EXDisplayRow *row = row->getNext();
            SCREEN::PrintALine(row->getRowNumber(), row->getRowText());
        }
      
    }        
}

void TFT_DrawHeader() {

    char header[25] = {""};
    sprintf(header, "DCC-EX   SCREEN %d\n", currentScreenID);
    tft.setTextColor(YELLOW);
    showmsgXY(1, 20, 1, header);
    tft.drawFastHLine(0, 25, tft.width(), WHITE);
    tft.setTextColor(WHITE);  // set this for all screen lines
    
}


void StartScreenPrint() {
    
    CONSOLE.println("New Page");
    tft.fillScreen(BLACK);

    TFT_DrawHeader();

    CONSOLE.println("Drawn Header\n");
    NextRowToPrint=0;
    NextScreenLine=0;

}

void PrintNoData() {

  showmsgXY(100, 100, 1, "No Data");

}


void PrintALine(int Row, char * text) {

  int vpos = (NextScreenLine * 21) + 44;

  //showmsgXY(1, vpos, 1, blankmsg);

  showmsgXY(1, vpos, 1, text);
  // increment the screen & line count
  NextRowToPrint++;
  NextScreenLine++;

  if (NextRowToPrint >= MAX_ROWS) {
    //We've reached the end of this data for this page
    PrintInProgress=false;
    
    // Any blank lines needed?
    while (NextScreenLine<MAX_ROWS){
      vpos = (NextScreenLine * 21) + 44;
      //showmsgXY(1, vpos, 1, blankmsg);
      NextScreenLine++;
    }
    NextRowToPrint = 0;
    NextScreenLine = 0;
  }
  
}


void DisplayScreen(){

  for (byte x=0;x<10;x++){
    //printf("Line %d - Use - %d - %s\n", x, DisplayLines[currentScreenID][x].inuse, DisplayLines[currentScreenID][x].text);
  }

}

bool check_touch() {

  return false;
  
}