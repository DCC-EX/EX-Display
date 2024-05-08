#include "AtFinder.h"
#include "Defines.h"
#include "DisplayFunctions.h"
#include "version.h"
#include <Arduino.h>

bool StartupPhase = true;
unsigned long timestamp = 0;
long screencount = 0;

// Chris just doing this for manual testing on my mega... so I can debug down the serial monitor
#if defined(ARDUINO_AVR_MEGA2560)
#undef CS_LISTEN
#define CS_LISTEN Serial
#endif

#if SCREEN_0_TYPE == MCU
#include "MCUFriendScreen.h"
MCUFRIEND_kbv tft;
#elif SCREEN_0_TYPE == TFT
#include "TFT_eSPIScreen.h"
TFT_eSPI tft = TFT_eSPI();
#endif

void setup() {
  CONSOLE.begin(115200);
  CS_LISTEN.begin(115200); // Start Serial1 for listening to messages

  CONSOLE.print(F("EX-Display v"));
  CONSOLE.println(VERSION);

  // Tell AtFinder our maximum supported text length,
  // and how to call back when found.
  AtFinder::setup(100, updateEXDisplayRow);

  // HARDWARE SETUP TODO..... Create an EXDisplay instance for each screen this ino wants to display.
  //  The updateEXDisplayRow will ignore messages destined for screens we dont have.
  // For testing lets create some
  SCREEN_0
#ifdef SCREEN_1_TYPE
  SCREEN_1
#endif
#ifdef SCREEN_2_TYPE
  SCREEN_2
#endif

  for (EXDisplay *display = EXDisplay::getFirst(); display; display = display->getNext()) {
    display->getEXScreen()->clearScreen(BACKGROUND_COLOUR);
  }

  for (EXDisplay *display = EXDisplay::getFirst(); display; display = display->getNext()) {
    display->getEXScreen()->setupScreen(SCREEN_ROTATION, TEXT_SIZE, BACKGROUND_COLOUR);
    display->getEXScreen()->writeRow(0, 0, TEXT_COLOUR, BACKGROUND_COLOUR, 1, "EX-Display");
    display->getEXScreen()->writeRow(1, 0, TEXT_COLOUR, BACKGROUND_COLOUR, 1, VERSION);

    CONSOLE.print(F("Display ID|Max Rows|Max Columns: "));
    CONSOLE.print(display->getDisplayNumber());
    CONSOLE.print(F("|"));
    CONSOLE.print(display->getScreenMaxRows());
    CONSOLE.print(F("|"));
    CONSOLE.println(display->getScreenMaxColumns());
  }

  delay(2000);

  for (EXDisplay *display = EXDisplay::getFirst(); display; display = display->getNext()) {
    display->getEXScreen()->clearScreen(BACKGROUND_COLOUR);
  }

  // Setup the start screen.
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
    updateScreens();
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
