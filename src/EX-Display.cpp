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
//
#include "EX-Display.h"
//#include "LinkedList.h"
#ifdef DEBUG
//#include "LibPrintf.h"
#endif

MCUFRIEND_kbv tft;

#include "Arial9pt7b.h"
//#include "FreeSans12pt7b.h"

#if defined(ARDUINO_AVR_MEGA2560)
     #define RX_PIN 0 // Define the RX pin for Serial1
     #define SERIAL Serial
     //#define SERIAL Serial1
     //#define RX_PIN 19 // Define the RX pin for Serial1

     #elif defined(ARDUINO_AVR_UNO)
     #define RX_PIN 0
     #define SERIAL Serial
     #elif defined(ESP32)
     #define RX_PIN 0
     #define SERIAL Serial

    #elif defined(ARDUINO_NUCLEO_F411RE) 
    HardwareSerial Serial1(PB7, PA15);  // Rx=PB7, Tx=PA15 -- CN7 pins 17 and 21 - F411RE
     #define SERIAL Serial1
     #define RX_PIN PB7;

     #elif defined(ARDUINO_NUCLEO_F446RE) 
     HardwareSerial Serial5(PD2, PC12);  // Rx=PD2, Tx=PC12 -- UART5 - F446RE
     #define SERIAL Serial5
     #define RX_PIN PD2;
     
#endif

//LinkedList<String> ListBuffer;
//byte ItemsInBuffer =0;
//LinkedList<DisplayLine*> myScreenList = LinkedList<DisplayLine*>();
//int ScreenIndex[MAX_ROWS][MAX_SCREENS];
int ScreenLines;


//int16_t currentXPos = 0; // Track the current x-position for printing text
//int16_t currentYPos = 0; // Track the current y-position for printing text


void setup() {
  SERIAL.begin(115200); // Start the serial communication
  //SERIAL1.begin(115200); // Start Serial1 for listening to messages

  TFT_Startup(); // Initialize the display
  //tft.invertDisplay(1);
  tft.invertDisplay(0);

  SERIAL.println("End of Setup");

  timestamp = millis();


}

void loop() {

  if (StartupPhase) {
    if ((millis() - timestamp) >= 8000){
            StartupPhase=false;
            screencount=millis();
    }
  }

  if (SERIAL.available()) { // Check if data is available on Serial1
    String message = SERIAL.readStringUntil('\n'); // Read the incoming message
    message.trim(); // Remove leading and trailing whitespaces
    
    int found = message.indexOf("<@");
    if (found>=0) {
      printf("<@ found at char %d\n", found);
    #ifdef DEBUG
        SERIAL.println(message);
        if (found>=1){
        message.remove(0,found);
        }
        SERIAL.println(message);
    #endif

      // Save to the buffer
      ParseData(message);

      if (StartupPhase) 
        {
          printf("Time ms = %d\n", millis()-timestamp);
        }
      
    }
  }
  else {
  // No data incoming so see if we need to display anything
    if (StartupPhase==false){
      if (ScreenChanged[THIS_SCREEN_NUM]==true) {

          if (PrintInProgress==true) { 

              PrintALine();
          }
          else {
            StartScreenPrint();
          }
      }
    }
  }

  //Check Page Time
  if((millis()-screencount) > 15000) {

    if (THIS_SCREEN_NUM == MAX_SCREENS-1) {
      THIS_SCREEN_NUM=0;
    }
    else {
      THIS_SCREEN_NUM++;
      StartScreenPrint();
    }
  screencount=millis();
  }

}


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

    StartScreenPrint();

}

void TFT_DrawHeader() {

    char header[HDDR_SIZE] = {""};
    sprintf(header, "DCC-EX   SCREEN %d", THIS_SCREEN_NUM);
    showmsgXY(1, 20, 1, YELLOW, header);
    tft.drawFastHLine(0, 25, tft.width(), WHITE);
    
}

void showmsgXY(int x, int y, byte sz, uint16_t colour, char *msg)
{
    tft.setFont();
    tft.setFont(&Arial9pt7b);
  
    tft.setCursor(x, y);
    tft.setTextColor(colour);
    tft.setTextSize(sz);
    tft.print(msg);
   
    
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

    //showmsgXY(1, vpos, 1, WHITE, message);
    showmsgXY(1, vpos, 1, static_cast<uint16_t>(WHITE), message);
    
    }

}


void ParseData(String message){
  
  int pos1 = message.indexOf(' ')+1;  //finds location of first SPACE
  int pos2 = message.indexOf(' ', pos1);   //finds location of second 
  int screenNo = (message.substring(pos1, pos2)).toInt();
  int pos3 = message.indexOf(' ', pos2+1);
  int screenRow = (message.substring(pos2+1, pos3)).toInt();
  int pos4 = message.indexOf('"')+1; // finds location of start of desc
  int lastchar = message.indexOf('"', pos4+1);
  char msg[MAX_LINE_LENGTH+1];
  DisplayLines[screenNo][screenRow].inuse=true;
  DisplayLines[screenNo][screenRow].row=screenRow;
  String buffer = message.substring(pos4, lastchar);
  buffer.toCharArray(msg, MAX_LINE_LENGTH);
  strcpy (DisplayLines[screenNo][screenRow].text, msg);
  // set a flag to indicate a screen has changed.
  ScreenChanged[screenNo]=true;

  #ifdef DEBUG
    SERIAL.print(" Buffer - ");
    SERIAL.println(buffer);
    SERIAL.print("msg = ");
    SERIAL.println(msg);
    // printf("pos1 %d Pos2 %d Pos3 %d Pos4 %d Last %d\n", pos1, pos2, pos3, pos4, lastchar);
    printf("Screen : %d Row %d - %s\n", screenNo, screenRow, DisplayLines[screenNo][screenRow].text);
  #endif

  // if (ScreenDrawn){
  //   printf("Printing single line %d", screenRow);
  //   PrintSingleLine(screenNo, screenRow);
  // }
}

void StartScreenPrint() {
    
    SERIAL.println("New Page");
    tft.fillScreen(BLACK);
    TFT_DrawHeader();
    SERIAL.println("Drawn Header");
    PrintInProgress=true;
    NextRowToPrint=0;
    NextScreenLine=0;

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
    //showmsgXY(1, vpos, 1, WHITE, "                              ");
    showmsgXY(1, vpos, 1, static_cast<uint16_t>(WHITE), "                              ");
    tft.fillRect(1,(vpos-21),320, 20, BLACK);
    char msg[MAX_LINE_LENGTH];
    strcpy(msg, DisplayLines[THIS_SCREEN_NUM][Row].text);
    showmsgXY(1, vpos, 1, WHITE, msg);
    
}

void PrintALine() {

  printf("Printing a line %d MAX %d", NextRowToPrint, MAX_ROWS);
  delay(50);
  if (DisplayLines[THIS_SCREEN_NUM][NextRowToPrint].inuse==true) {
    printf("Print row %d screen %d\n", NextScreenLine, THIS_SCREEN_NUM);
    byte vpos = (NextScreenLine * 21) + 44;
    
    //showmsgXY(1, vpos, 1, WHITE, "                              ");
    showmsgXY(1, vpos, 1, static_cast<uint16_t>(WHITE), "                              ");
    char msg[MAX_LINE_LENGTH];
    strcpy(msg, DisplayLines[THIS_SCREEN_NUM][NextRowToPrint].text);
    showmsgXY(1, vpos, 1, WHITE, msg);
    printf("Printing Row %d - %s", NextScreenLine, msg);
    // increment the screen line count
    NextScreenLine++;
  }
  // increment the data line count
  NextRowToPrint++;

  if (NextRowToPrint >= MAX_ROWS) {
    //We've reached the end of this page
    PrintInProgress=false;
    ScreenChanged[THIS_SCREEN_NUM]=false;
    DisplayScreen();  // just for debug
    // Any blank lines needed?
    while (NextScreenLine<MAX_ROWS){
      byte vpos = (NextScreenLine * 21) + 44;
      showmsgXY(1, vpos, 1, WHITE, "                              ");
      NextScreenLine++;
    }
  }
  
}


void DisplayScreen(){
  //if (screenNo == 0){
   // byte vpos = (screenRow * 21) + 44;
  //   tft.fillRect(1,vpos,320, 20, BLACK);
   //  showmsgXY(1, vpos, 1, WHITE, msg);
  //}

  for (byte x=0;x<10;x++){
    printf("Line %d - Use - %d - %s\n", x, DisplayLines[THIS_SCREEN_NUM][x].inuse, DisplayLines[THIS_SCREEN_NUM][x].text);
  }

}