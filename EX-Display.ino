
#include "AtFinder.h"
#include "Defines.h"
#include "DisplayFunctions.h"
#include <Arduino.h>



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

    //Setup the start screen.
    // if (MAX_SCREENS > 1) {
    // currentScreenID = INITIAL_SCREEN;
    // }
    // else {
    //   currentScreenID = 0;
    // }

    timestamp = millis();
    CONSOLE.println(F("End of Setup"));
  
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
  if (CS_LISTEN.available()) {
    AtFinder::processInputChar(CS_LISTEN.read());
  }
  // you can display all rows by sending <@ 255 0 "">

  // No data incoming so see if we need to display anything
  // DISABLE IN STARTUPPHASE
  else {

    /* DISABLE SO IT WILL COMPILE
        if (StartupPhase==false){
            // add thie following in once display is working
            // for (byte x= 0; x<MAX_SCREENS; x++){
            //   if (ScreenChanged[x]) { setScreenRows(x); }
            // }

           SCREEN::CheckScreens();

          // DISABLE TO START
          #ifndef USE_TOUCH
              //Check Page Time to see if we need to scroll
              if((millis()-screencount) > SCROLLTIME) {

                  if (currentScreenID >= MAX_SCREENS-1) {
                  currentScreenID=0;
                  }
                  else {
                  currentScreenID++;

                  }
                  screencount=millis();
                  ScreenChanged[currentScreenID] = true;

              }
          #else
              if (SCREEN::check_touch) {
                  if (currentScreenID >= MAX_SCREENS-1) {
                      currentScreenID=0;
                  }
                  else {
                  currentScreenID++;

                  }

                  ScreenChanged[currentScreenID] = true;

              }

          #endif
        }
    */
  }
}
