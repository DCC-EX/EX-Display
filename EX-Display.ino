#include "AtFinder.h"
#include "Defines.h"
#include "DisplayFunctions.h"
#include "InputMethod.h"
#include "version.h"
#include <Arduino.h>


bool StartupPhase = true;
unsigned long timestamp = 0;
long screencount = 0;

#if SCREEN_TYPE == MCU
#include "MCUFriendScreen.h"
MCUFRIEND_kbv tft;
MCUFriendScreen *screen = new MCUFriendScreen(tft);
#ifdef USE_TOUCH
#include "AdafruitTouch.h"
TouchScreen touchScreen = TouchScreen(XP, YP, XM, YM, 300);
InputMethod *input = new AdafruitTouch(touchScreen);
#endif
#elif SCREEN_TYPE == TFT
#include "TFT_eSPIScreen.h"
TFT_eSPI tft = TFT_eSPI();
TFT_eSPIScreen *screen = new TFT_eSPIScreen(tft);
#if defined(USE_TOUCH)
#include "TFT_eSPITouch.h"
InputMethod *input = new TFT_eSPITouch(tft);
#endif
#elif SCREEN_TYPE == OLED_SSD1306
#include "OLEDScreen.h"
Adafruit_SSD1306 oled = Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);
OLEDScreen *screen = new OLEDScreen(oled);
#elif SCREEN_TYPE == OLED_SH1106
#include "OLEDScreen.h"
Adafruit_SH1106G oled = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);
OLEDScreen *screen = new OLEDScreen(oled);
#endif

#if defined(USE_BUTTONS)
#include "PushButton.h"
InputMethod *input = new PushButton(LEFT_BUTTON, RIGHT_BUTTON, CENTRE_BUTTON, UP_BUTTON, DOWN_BUTTON);
#endif

void setup() {
  CONSOLE.begin(115200);
  CS_LISTEN.begin(115200); // Start Serial1 for listening to messages

  CONSOLE.print(F("EX-Display v"));
  CONSOLE.println(VERSION);

#ifdef NEEDS_OLED
  Wire.begin();
#endif

  // Setup our physical screens first - required before adding displays
  screen->setupScreen(SCREEN_ROTATION, TEXT_SIZE, BACKGROUND_COLOUR);

  // Add the displays to the screen
#if defined(DISPLAY_1_ID)
  screen->addDisplay(DISPLAY_1_ID, TEXT_COLOUR, BACKGROUND_COLOUR);
#endif
#if defined(DISPLAY_2_ID)
  screen->addDisplay(DISPLAY_2_ID, TEXT_COLOUR, BACKGROUND_COLOUR);
#endif
#if defined(DISPLAY_3_ID)
  screen->addDisplay(DISPLAY_3_ID, TEXT_COLOUR, BACKGROUND_COLOUR);
#endif

  // Tell AtFinder our maximum supported text length,
  // and how to call back when found.
  AtFinder::setup(100, updateDisplayRow);

  // Create display instances
  for (LogicalDisplay *display = screen->getFirstDisplay(); display; display = display->getNext()) {
    CONSOLE.print(F("Display ID|Max Rows|Max Columns: "));
    CONSOLE.print(display->getDisplayNumber());
    CONSOLE.print(F("|"));
    CONSOLE.print(screen->getMaxRows());
    CONSOLE.print(F("|"));
    CONSOLE.println(display->getMaxRowLength());
  }

  screen->writeRow(0, 0, TEXT_COLOUR, BACKGROUND_COLOUR, 0, "EX-Display", false);
  screen->writeRow(1, 0, TEXT_COLOUR, BACKGROUND_COLOUR, 0, VERSION, false);

  delay(2000);

  screen->clearScreen(BACKGROUND_COLOUR);

  timestamp = millis();

#if defined(USE_TOUCH) || defined(USE_BUTTONS)
  input->setScreen(screen);
  input->begin();
#endif

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
    if (!StartupPhase) {
      updateScreen();
#if defined(USE_TOUCH) || defined(USE_BUTTONS)
      Button inputButton = input->processInput();
      switch (inputButton) {
        case LeftButton:
          CONSOLE.println(F("Left button pressed"));
          break;

        case RightButton:
          CONSOLE.println(F("Right button pressed"));
          break;

        case CentreButton:
          CONSOLE.println(F("Centre button pressed"));
          break;

        case UpButton:
          CONSOLE.println(F("Up button pressed"));
          break;

        case DownButton:
          CONSOLE.println(F("Down button pressed"));
          break;

        default:
          break;
      }
#endif
    }
  }
}
