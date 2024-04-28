
#include <Arduino.h>
#include "AtFinder.h"
#include "Defines.h"
#include "DisplayFunctions.h"
#include "EXDisplayClass.h"

// #include "EXScreen.h"

/* MOVED TO DisplayFunctions - now updateDisplayRows()
// callback function when a <@ id row "text"> message detected
void processDisplay(int16_t screenId, int16_t screenRow, char *text) {
  CONSOLE.print(F("\n id="));
  CONSOLE.print(screenId);
  CONSOLE.print(F(" row="));
  CONSOLE.print(screenRow);
  CONSOLE.print(F(" text=\""));
  CONSOLE.print(text);
  CONSOLE.print(F("\"\n"));

  if (text[0]=='\0'){
      DisplayLines[screenId][screenRow].inuse=false;
    }
    else {
      DisplayLines[screenId][screenRow].inuse=true;
    }
  DisplayLines[screenId][screenRow].row=screenRow;
  strcpy (DisplayLines[screenId][screenRow].text,  text);

  ScreenChanged[screenId]=true;
}
*/

bool StartupPhase = true;
long timestamp = 0;
long screencount = 0;


// Chris just doing this for manual testing on my mega... so I can debug down the serial monitor 
#undef CS_LISTEN
#define CS_LISTEN Serial


void setup() {
  CONSOLE.begin(115200);
  CS_LISTEN.begin(115200); // Start Serial1 for listening to messages

  // Tell AtFinder our maximum supported text length,
  // and how to call back when found.
  AtFinder::setup(100, updateEXDisplayRow);

  // SCREEN::TFT_Startup();
  // tft.invertDisplay(1);
  // tft.invertDisplay(0);

  // HARDWARE SETUP TODO..... Create an EXDisplay instance for each screen this ino wants to display.
  //  The updateEXDisplayRow will ignore messages destined for screens we dont have.
  // For testing lets create some  
  new EXDisplay(0,16);   // id 0, physical screen width 16
  new EXDisplay(1,32);


  CONSOLE.println(F("End of Setup"));
  delay(1000);

  timestamp = millis();
}

void loop() {

  // Check if we are in the startup phase
  // This phase inhibits screen drawing until the startup messages are
  // issued by the CS
  if (StartupPhase) {
    if ((millis() - timestamp) >= STARTUP_TIME) {
      StartupPhase = false;
      screencount = millis();
    }
  }

  // each byte received form serial is passed to the parse
  if (CS_LISTEN.available())
    AtFinder::processInputChar(CS_LISTEN.read());

  // you can display all rows by sending <@ 255 0 "">

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
