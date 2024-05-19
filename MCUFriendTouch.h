#include "Defines.h"
#ifdef USE_TOUCH

#ifndef MCUFRIENDTOUCH_H
#define MCUFRIENDTOUCH_H

#include "EXTouch.h"
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Touchscreen.h>
#include "config.h"
#include <SPI.h>   // most older screens use SPI

#define MINPRESSURE 200
#define MAXPRESSURE 1000

class MCUFriendTouch : public EXTouch {
public:
  MCUFriendTouch(TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300));

  virtual void setupTouch();

  virtual void drawButtons(uint16_t fontColour, uint16_t backgroundColour);

  bool touchGetXY();

  void checkButtons();

  uint8_t tft;

  uint8_t screenHeight;

  uint8_t screenWidth;

private:
  TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300)

  uint8_t _buttonPressed; // Indicates which button was pressed
  
};

#endif // end include guard

#endif // end ifdef USE_TOUCH