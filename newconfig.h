#ifdef USE__NEW_CONFIG

// Current physical screen instantiation

// MCUFRIEND_kbv
MCUFRIEND_kbv tft;
MCUFriendScreen *screen = new MCUFriendScreen(tft);

// TFT_eSPI
TFT_eSPI tft = TFT_eSPI();
TFT_eSPIScreen *screen = new TFT_eSPIScreen(tft);

// SSD1306 OLED
Adafruit_SSD1306 oled = Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);
OLEDScreen *screen = new OLEDScreen(oled);

// SH1106 OLED
Adafruit_SH1106G oled = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);
OLEDScreen *screen = new OLEDScreen(oled);



#if SCREEN_TYPE == MCU
#include "MCUFriendScreen.h"
MCUFRIEND_kbv tft;
MCUFriendScreen *screen = new MCUFriendScreen(tft);
#ifdef USE_TOUCH
#include "AdafruitTouch.h"
TouchScreen touchScreen = TouchScreen(XP, YP, XM, YM, 300);
AdafruitTouch *input = new AdafruitTouch(touchScreen);
#endif
#elif SCREEN_TYPE == TFT
#include "TFT_eSPIScreen.h"
TFT_eSPI tft = TFT_eSPI();
TFT_eSPIScreen *screen = new TFT_eSPIScreen(tft);
#if defined(USE_TOUCH)
#include "TFT_eSPITouch.h"
TFT_eSPITouch *input = new TFT_eSPITouch(tft);
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
PushButton *input = new PushButton(LEFT_BUTTON, RIGHT_BUTTON, CENTRE_BUTTON, UP_BUTTON, DOWN_BUTTON);
#endif

#if defined(DISPLAY_1_ID)
  screen->addDisplay(DISPLAY_1_ID, TEXT_COLOUR, BACKGROUND_COLOUR);
#endif
#if defined(DISPLAY_2_ID)
  screen->addDisplay(DISPLAY_2_ID, TEXT_COLOUR, BACKGROUND_COLOUR);
#endif
#if defined(DISPLAY_3_ID)
  screen->addDisplay(DISPLAY_3_ID, TEXT_COLOUR, BACKGROUND_COLOUR);
#endif

#if defined(USE_TOUCH) || defined(USE_BUTTONS)
  input->setScreen(screen);
  input->begin();
#endif

#endif