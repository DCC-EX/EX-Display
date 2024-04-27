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
#include "EX-Screen.h"


#ifdef DEBUG
  #if defined(ARDUINO_AVR_UNO)
    // for the Uno include this so we can use printf
    #include "LibPrintf.h"
  #endif
#endif

MCUFRIEND_kbv tft;

#include "Arial9pt7b.h"
//#include "FreeSans12pt7b.h"


int ScreenLines;


void TFT_Startup()
{

    uint16_t ID = tft.readID();
    SERIAL.print("TFT ID = 0x");
    SERIAL.println(ID, HEX);
    // #ifdef DEBUG
    // SERIAL.println("Calibrate for your Touch Panel");
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

    StartScreenPrint();

}

void showmsgXY(int x, int y, int sz, const char *msg)
{
    tft.setFont();
    tft.setFont(&Arial9pt7b);
    tft.setCursor(x, y); 
    tft.setTextSize(sz);
    tft.print(msg);
       
}

void TFT_DrawHeader() {

    char header[HDDR_SIZE] = {""};
    sprintf(header, "DCC-EX   SCREEN %d\n", THIS_SCREEN_NUM);
    tft.setTextColor(YELLOW);
    //printf("Header to show = %s", header);
    showmsgXY(1, 20, 1, header);
    tft.drawFastHLine(0, 25, tft.width(), WHITE);
    tft.setTextColor(WHITE);
    
}



void testprint(byte lines){

  char message[30];
  int vpos=0;

  for (byte no=1; no<(lines+1); no++)
  {
    vpos = (no * 21) + 22;

    #ifdef DEBUG
      printf(message, "Line : %d Pos %d", no, vpos);
      SERIAL.println(message);
    #endif

    showmsgXY(1, vpos, 1, message);
    
    }

}


void parseData(char * message){

  printf("Calling Parser with %s\n", message);

  bool success = DCCEXInbound::parse(message);
  
  if (success) {
    char opcode = DCCEXInbound::getOpcode();
    int paramCount = DCCEXInbound::getParameterCount();
    if (opcode == '@' && paramCount == 3) {
      int screenNo = DCCEXInbound::getNumber(0);
      int screenRow = DCCEXInbound::getNumber(1);
      char screentext[MAX_LINE_LENGTH+1];
      strcpy(screentext, DCCEXInbound::getTextParameter(2));
      if (screentext[0]=='\0'){
        DisplayLines[screenNo][screenRow].inuse=false;
      }
      else {     
        DisplayLines[screenNo][screenRow].inuse=true;
      }
      DisplayLines[screenNo][screenRow].row=screenRow;  
      strcpy (DisplayLines[screenNo][screenRow].text,  screentext);

      ScreenChanged[screenNo]=true;

      printf("Processed Screen : %d Row %d - %s\n", screenNo, screenRow, DisplayLines[screenNo][screenRow].text);

      #ifdef DEBUG
        // SERIAL.print(" Buffer - ");
        // SERIAL.println(buffer);
        // SERIAL.print("msg = ");
        // SERIAL.println(msg);
        // printf("pos1 %d Pos2 %d Pos3 %d Pos4 %d Last %d\n", pos1, pos2, pos3, pos4, lastchar);
        printf("Screen : %d Row %d - %s\n", screenNo, screenRow, DisplayLines[screenNo][screenRow].text);
      #endif
    }
  }

  // if (ScreenDrawn){
  //   printf("Printing single line %d", screenRow);
  //   PrintSingleLine(screenNo, screenRow);
  // }
}

void StartScreenPrint() {
    
    SERIAL.println("New Page");
    tft.fillScreen(BLACK);

    TFT_DrawHeader();

    SERIAL.println("Drawn Header\n");
    NextRowToPrint=0;
    NextScreenLine=0;
    #ifdef DEBUG
    DisplayScreen();  // debug output only
    #endif

}

void PrintSingleLine(byte screenNo, byte screenRow) {
    printf("Printing lines %d\n", screenRow);
    // Find which screen row to print on
    byte Row = 0;
    for (byte x=0; x<=screenRow; x++) {
      if (DisplayLines[screenNo][x].row<screenRow){
        if (DisplayLines[screenNo][x].inuse==true) {
          Row=Row+1;
        }
      }
    }
    printf("Row found - %d\n", Row);
    //NextRowToPrint=Row;
    byte vpos = (Row * 21) + 44;
    //showmsgXY(1, vpos, 1, blankmsg);
    //tft.fillRect(1,(vpos-21),320, 20, BLACK);

    showmsgXY(1, vpos, 1, DisplayLines[THIS_SCREEN_NUM][Row].text);
    
}

void PrintALine() {
  
  int vpos=0;
  //printf("Printing a line %d MAX %d\n", NextRowToPrint, MAX_ROWS);
  //delay(50);
  if (DisplayLines[THIS_SCREEN_NUM][NextRowToPrint].inuse==true) {
    printf("Print row %d screen %d\n", NextScreenLine, THIS_SCREEN_NUM);
    vpos = (NextScreenLine * 21) + 44;
    
    //showmsgXY(1, vpos, 1, blankmsg);

    showmsgXY(1, vpos, 1, DisplayLines[THIS_SCREEN_NUM][NextRowToPrint].text);

    printf("Printing Row %d - %s\n", NextScreenLine, DisplayLines[THIS_SCREEN_NUM][NextRowToPrint].text);
    // increment the screen line count
    NextScreenLine++;
  }
  // increment the data line count
  NextRowToPrint++;

  if (NextRowToPrint >= MAX_ROWS) {
    //We've reached the end of this page
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
  //if (screenNo == 0){
   // byte vpos = (screenRow * 21) + 44;
  //   tft.fillRect(1,vpos,320, 20, BLACK);
   //  showmsgXY(1, vpos, 1, msg);
  //}

  for (byte x=0;x<10;x++){
    printf("Line %d - Use - %d - %s\n", x, DisplayLines[THIS_SCREEN_NUM][x].inuse, DisplayLines[THIS_SCREEN_NUM][x].text);
  }

}

