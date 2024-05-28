// #define USE_NEW_CONFIG

#ifdef USE_NEW_CONFIG

/* PHYSICAL SCREEN INSTANTIATION*/
// MCUFRIEND_kbv - SCREEN_TYPE MCU
MCUFRIEND_kbv tft;
MCUFriendScreen *screen = new MCUFriendScreen(tft);

// TFT_eSPI - SCREEN_TYPE TFT
TFT_eSPI tft = TFT_eSPI();
TFT_eSPIScreen *screen = new TFT_eSPIScreen(tft);

// SSD1306 OLED - SCREEN_TYPE OLED_SSD1306
Adafruit_SSD1306 oled = Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);
OLEDScreen *screen = new OLEDScreen(oled);

// SH1106 OLED - SCREEN_TYPE OLED_SH1106
Adafruit_SH1106G oled = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);
OLEDScreen *screen = new OLEDScreen(oled);

/* INPUT INSTANTIATION */
// MCUFRIEND_kbv/Adafruit TouchScreen - NEEDS_MCU && USE_TOUCH
TouchScreen touchScreen = TouchScreen(XP, YP, XM, YM, 300);
AdafruitTouch *input = new AdafruitTouch(touchScreen);

// TFT_eSPI touch - NEEDS_TFT && USE_TOUCH
TFT_eSPI tft = TFT_eSPI();
TFT_eSPITouch *input = new TFT_eSPITouch(tft);

// PushButton - USE_BUTTONS
PushButton *input = new PushButton(LEFT_BUTTON, RIGHT_BUTTON, CENTRE_BUTTON, UP_BUTTON, DOWN_BUTTON);

/* These are done in setup() */
void setup() {
  // Add logical display to screen, creates LogicalDisplay instances
  screen->addDisplay(DISPLAY_1_ID, TEXT_COLOUR, BACKGROUND_COLOUR);
  screen->addDisplay(DISPLAY_2_ID, TEXT_COLOUR, BACKGROUND_COLOUR);
  screen->addDisplay(DISPLAY_3_ID, TEXT_COLOUR, BACKGROUND_COLOUR);
  // Set the physical screen the input controls
  // If we have multiple screens, this should change to an active screen and associated linked list
  input->setScreen(screen);
}

#endif