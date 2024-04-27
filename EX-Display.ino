
#include <Arduino.h>
#include "AtFinder.h"
#include "config.h"
#include "Defines.h"
// #include "EX-Screen.h"

// callback function when a <@ id row "text"> message detected 
void processDisplay(int16_t screenId,int16_t screenRow, char* text) {
    CONSOLE.print(F("\n id="));
    CONSOLE.print(screenId);
    CONSOLE.print(F(" row="));
    CONSOLE.print(screenRow);
    CONSOLE.print(F(" text=\""));
    CONSOLE.print(text);
    CONSOLE.print(F("\"\n"));

    /* DISABLE TO START
    if (text[0]=='\0'){
        DisplayLines[screenId][screenRow].inuse=false;
      }
      else {     
        DisplayLines[screenId][screenRow].inuse=true;
      }
    DisplayLines[screenId][screenRow].row=screenRow;  
    strcpy (DisplayLines[screenId][screenRow].text,  text);

    ScreenChanged[screenId]=true;
    */

}

bool StartupPhase = true;
long timestamp = 0;
long screencount = 0;

    
void setup() {
    CONSOLE.begin(115200);
    CS_LISTEN.begin(115200); // Start Serial1 for listening to messages

    // Tell AtFinder our maximum supported text length,
    // and how to call back when found.
    AtFinder::setup(100,processDisplay);

    // SCREEN::TFT_Startup(); 
    //tft.invertDisplay(1);
    //tft.invertDisplay(0);

    CONSOLE.println("End of Setup");
    delay(1000);

    timestamp = millis();

}

void loop() {

    // Check if we are in the startup phase 
    // This phase inhibits screen drawing until the startup messages are
    // issued by the CS
    if (StartupPhase) {
        if ((millis() - timestamp) >= STARTUP_TIME){
                StartupPhase=false;
                screencount=millis();
        }
    }

    // each byte received form serial is passed to the parse 
    if (CS_LISTEN.available()) AtFinder::processInputChar(CS_LISTEN.read());

// No data incoming so see if we need to display anything
/* DISABLE TO START
    if (StartupPhase==false){

        if (ScreenChanged[THIS_SCREEN_NUM]==true) {
            CONSOLE.print("Time to draw a screen line");
            SCREEN::StartScreenPrint();
            PrintInProgress=true;
            ScreenChanged[THIS_SCREEN_NUM] = false;
        }
        
        if (PrintInProgress==true) { 
            CONSOLE.println("Pinting a line");
            SCREEN::PrintALine();
        }
  }
*/

/* DISABLE TO START
#ifndef USE_TOUCH 
    //Check Page Time to see if we need to scroll
    if((millis()-screencount) > SCROLLTIME) {

        if (THIS_SCREEN_NUM >= MAX_SCREENS-1) {
        THIS_SCREEN_NUM=0;
        }
        else {
        THIS_SCREEN_NUM++;
        
        }
        screencount=millis();
        ScreenChanged[THIS_SCREEN_NUM] = true;

    }
#else
    if (SCREEN::check_touch) {
        if (THIS_SCREEN_NUM >= MAX_SCREENS-1) {
            THIS_SCREEN_NUM=0;
            }
            else {
            THIS_SCREEN_NUM++;
            
            }

            ScreenChanged[THIS_SCREEN_NUM] = true;
        }
    }

#endif
*/

}