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

#include "EX-Display.h"
#include "LinkedList.h"
#ifdef DEBUG
#include "LibPrintf.h"
#endif

MCUFRIEND_kbv tft;

#include "Arial9pt7b.h"
//#include "FreeSans12pt7b.h"

// #if defined(ARDUINO_AVR_MEGA2560)
//   #define RX_PIN 19 // Define the RX pin for Serial1
//   #elif defined(ARDUINO_AVR_UNO)
//   #define RX_PIN 0
//   #define Serial1 Serial
//   #endif

//LinkedList<String> ListBuffer;
//byte ItemsInBuffer =0;
//LinkedList<DisplayLine*> myScreenList = LinkedList<DisplayLine*>();
//int ScreenIndex[MAX_ROWS][MAX_SCREENS];
int ScreenLines;


//int16_t currentXPos = 0; // Track the current x-position for printing text
//int16_t currentYPos = 0; // Track the current y-position for printing text


void setup() {
  Serial.begin(115200); // Start the serial communication
  //Serial1.begin(115200); // Start Serial1 for listening to messages

  TFT_Startup(); // Initialize the display

  tft.setTextColor(0xFFFF); // White color

  //Clear the Index array
  for (byte r=0;r<MAX_ROWS;r++) {
    for (byte s=0;s<MAX_SCREENS;s++){
      DisplayLines[s][r].inuse=false;
      DisplayLines[s][r].row=r;
      DisplayLines[s][r].text[0]=" ";
    }
  }

  Serial.println("End of Setup");

}

void loop() {

  //Serial.print("Loop");

  if (Serial.available()) { // Check if data is available on Serial1
    String message = Serial.readStringUntil('\n'); // Read the incoming message
    message.trim(); // Remove leading and trailing whitespaces
   
    //currentYPos += FONT_SIZE * 8; // Move to the next line for the next message
    //currentXPos = 0; // Reset X position for the new line
    
    String key = message.substring(0,2);
    if (key == "<@"){

      #ifdef DEBUG
        Serial.print(message.substring(0,2));
        Serial.print("  -  ");
        Serial.println(message);
      #endif

      // Save to the buffer
      ParseData(message);
      
    }
  }
  else
  {
    if(PrintInProgress){
      PrintALine();
    }
    else{
      if (ScreenChanged[THIS_SCREEN_NUM]=true)
      {
        
        StartScreenPrint();
      }
    }
  }

}


void TFT_Startup()
{

    uint16_t ID = tft.readID();
    Serial.print("TFT ID = 0x");
    Serial.println(ID, HEX);
    #ifdef DEBUG
    Serial.println("Calibrate for your Touch Panel");
    #endif
    if (ID == 0xD3D3) ID = 0x9486; // write-only shield

    tft.begin(ID);
  
    tft.setRotation(1);           
    tft.setTextColor(0xFFFF); 
    tft.fillScreen(BLACK);

    TFT_DrawHeader();

}

void TFT_DrawHeader() {

    char header[HDDR_SIZE] = {""};
    sprintf(header, "DCC-EX   SCREEN %d", THIS_SCREEN_NUM);
    showmsgXY(1, 20, 1, YELLOW, header);
    tft.drawFastHLine(0, 25, tft.width(), WHITE);
    delay(5000);
}

void showmsgXY(int x, int y, byte sz, char colour, char *msg)
{
    tft.setFont();
    tft.setFont(&Arial9pt7b);
  
    tft.setCursor(x, y);
    tft.setTextColor(colour);
    tft.setTextSize(sz);

    #ifdef DEBUG
    tft.print(msg);
    #endif
    
}

void testprint(byte lines){

  char message[30];
  int vpos=0;

  for (byte no=1; no<(lines+1); no++)
  {
    vpos = (no * 21) + 22;

    #ifdef DEBUG
    printf(message, "Line : %d Pos %d", no, vpos);
    Serial.println(message);
    #endif

    showmsgXY(1, vpos, 1, WHITE, message);
    
    }

}

// void displayMessage(String message) {
//   // Iterate through each character in the message
//   for (size_t i = 0; i < message.length(); i++) {
//     char character = message.charAt(i); // Get the current character

//     // Check if adding the character will exceed the display width
//     if (currentXPos + CHAR_WIDTH > DISPLAY_WIDTH) {
//       // Move to the next line
//       currentXPos = 0;
//       currentYPos += FONT_SIZE * 8; // Move down by one font height

//       // Check if adding the character will exceed the display height
//       if (currentYPos + FONT_SIZE * 8 > DISPLAY_HEIGHT) {
//         // Clear the screen if all lines are used
//         tft.fillScreen(0);
//         currentXPos = 0;
//         currentYPos = 0;
//       }
//     }

//     // Handle newline character
//     if (character == '\n') {
//       // Move to the next line
//       currentXPos = 0;
//       currentYPos += FONT_SIZE * 8; // Move down by one font height
//     } else {
//       // Print the character at the current position
//       tft.setCursor(currentXPos, currentYPos);
//       tft.write(character);

//       // Update x-position for the next character
//       currentXPos += CHAR_WIDTH;
//     }
//   }
// }

void ParseData(String message){
  
  int pos1 = message.indexOf(' ')+1;  //finds location of first SPACE
  int pos2 = message.indexOf(' ', pos1);   //finds location of second 
  int screenNo = (message.substring(pos1, pos2)).toInt();
  //ScreenItem->screen = (message.substring(pos1, pos2)).toInt();
  int pos3 = message.indexOf(' ', pos2+1);
  int screenRow = (message.substring(pos2+1, pos3)).toInt();
  //ScreenItem->row = (message.substring(pos2+1, pos3)).toInt();
  int pos4 = message.indexOf('"')+1; // finds location of start of desc
  int lastchar = message.indexOf('"', pos4+1);
  char msg[35];
  DisplayLines[screenNo][screenRow].inuse=true;
  DisplayLines[screenNo][screenRow].row=screenRow;
  message.substring(pos4, lastchar).toCharArray(DisplayLines[screenNo][screenRow].text, MAX_LINE_LENGTH);

  ScreenChanged[screenNo]=true;

  #ifdef DEBUG
  // printf("pos1 %d Pos2 %d Pos3 %d Pos4 %d Last %d\n", pos1, pos2, pos3, pos4, lastchar);
  //printf("Screen : %d Row %d - %s\n", screenNo, screenRow, msg);
  #endif

}

void StartScreenPrint() {
    
    tft.fillScreen(BLACK);
    TFT_DrawHeader();
    PrintInProgress=true;
    NextRowToPrint=0;
    NextScreenLine=0;

}

void PrintALine() {

  if (DisplayLines[THIS_SCREEN_NUM][NextRowToPrint].inuse) {
    byte vpos = (NextScreenLine * 21) + 44;
    //   tft.fillRect(1,vpos,320, 20, BLACK);
    char msg[MAX_LINE_LENGTH];
    strcpy(msg, DisplayLines[THIS_SCREEN_NUM][NextRowToPrint].text);
    showmsgXY(1, vpos, 1, WHITE, *msg);
    NextRowToPrint++;
    NextScreenLine++;  
  }
  if (NextRowToPrint == MAX_ROWS) {
    // We've reached the end of this page
    PrintInProgress=false;
    NextRowToPrint=0;
    NextScreenLine=0;
    ScreenChanged[THIS_SCREEN_NUM]=false;
  }
  //}
}

void DisplayScreen(){
  //if (screenNo == 0){
   // byte vpos = (screenRow * 21) + 44;
  //   tft.fillRect(1,vpos,320, 20, BLACK);
   //  showmsgXY(1, vpos, 1, WHITE, msg);
  //}

}