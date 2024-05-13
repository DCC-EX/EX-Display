#include "AtFinder.h"
#include "Defines.h"
#include "DisplayFunctions.h"
#include "version.h"
#include <Arduino.h>

bool StartupPhase = true;
unsigned long timestamp = 0;
long screencount = 0;

#if SCREEN_TYPE == MCU
#include "MCUFriendScreen.h"
MCUFRIEND_kbv tft;
MCUFriendScreen *screen = new MCUFriendScreen(tft);
#elif SCREEN_TYPE == TFT
#include "TFT_eSPIScreen.h"
TFT_eSPI tft = TFT_eSPI();
TFT_eSPIScreen *screen = new TFT_eSPIScreen(tft);
#endif

void setup() {
  CONSOLE.begin(115200);
  CS_LISTEN.begin(115200); // Start Serial1 for listening to messages

  CONSOLE.print(F("EX-Display v"));
  CONSOLE.println(VERSION);

  // Tell AtFinder our maximum supported text length,
  // and how to call back when found.
  AtFinder::setup(100, updateEXDisplayRow);

  // Create display instances
#if defined(DISPLAY_1_ID)
  new EXDisplay(DISPLAY_1_ID, screen, 30);
#endif
#if defined(DISPLAY_2_ID)
  new EXDisplay(DISPLAY_2_ID, screen, 30);
#endif
#if defined(DISPLAY_3_ID)
  new EXDisplay(DISPLAY_3_ID, screen, 30);
#endif

  for (EXDisplay *display = EXDisplay::getFirst(); display; display = display->getNext()) {
    display->getEXScreen()->setupScreen(SCREEN_ROTATION, BACKGROUND_COLOUR, TEXT_SIZE);
    CONSOLE.print(F("Display ID|Max Rows|Max Columns: "));
    CONSOLE.print(display->getDisplayNumber());
    CONSOLE.print(F("|"));
    CONSOLE.print(display->getScreenMaxRows());
    CONSOLE.print(F("|"));
    CONSOLE.println(display->getScreenMaxColumns());
  }

  EXDisplay *activeDisplay = EXDisplay::getActiveDisplay();
  activeDisplay->getEXScreen()->writeRow(0, 0, TEXT_COLOUR, BACKGROUND_COLOUR, 0, "EX-Display", false);
  activeDisplay->getEXScreen()->writeRow(1, 0, TEXT_COLOUR, BACKGROUND_COLOUR, 0, VERSION, false);

  delay(2000);

  activeDisplay->getEXScreen()->clearScreen(BACKGROUND_COLOUR);

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
    updateScreen();
  }
}
