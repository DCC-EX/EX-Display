#include "Defines.h"
#ifdef NEEDS_MCU

#ifndef MCUFRIENDSCREEN_H
#define MCUFRIENDSCREEN_H

#include "EXScreen.h"
#include <Adafruit_GFX.h>
#include <Arduino.h>
#include <MCUFRIEND_kbv.h>
#ifdef USE_TOUCH
  #include <TouchScreen.h>
#endif

class MCUFriendScreen : public EXScreen {
public:
  MCUFriendScreen(MCUFRIEND_kbv &tft);
  #ifdef USE_TOUCH
    TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
  #endif

  virtual void setupScreen(uint8_t rotation, uint8_t textSize, uint16_t backgroundColour) override;

  virtual void clearScreen(uint16_t backgroundColour) override;

  virtual void clearRow(uint8_t row, uint16_t backgroundColour) override;

  virtual void writeRow(uint8_t row, uint8_t column, uint16_t fontColour, uint16_t backgroundColour, uint8_t maxLength,
                        char *message, bool underlined) override;

  virtual void writeLine(uint8_t row, uint8_t column, uint8_t lineLength, uint16_t lineColour,
                         uint16_t backgroundColour) override;
  
  #ifdef USE_TOUCH

    virtual void MCUFriendScreen::defineButtons();

    bool MCUFriendScreen::Touch_getXY(void);

    void MCUFriendScreen::CheckButtons();

  #endif

  uint8_t returnHeight();

  uint8_t returnWidth();

  uint16_t returnTFT();

  uint8_t getCharacterWidth(const char *character);
  byte _buttonPressed;
  byte _debounceDelay;           //  the debounce time; increase if the output flickers

  #ifdef USE_TOUCH
    // Define the operating buttons
    //Adafruit_GFX_Button btn1, btn2, btn3, btn4, btn5;
    Adafruit_GFX_Button _key[5];
    int _pixel_x, _pixel_y;     //Touch_getXY() updates global vars
  #endif

private:
  MCUFRIEND_kbv &_tft;
  
};

#endif  // end USE_TOUCH include

#endif // end overall include guard
