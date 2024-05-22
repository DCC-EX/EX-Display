#include "Defines.h"
#ifdef NEEDS_OLED

#ifndef OLEDSCREEN_H
#define OLEDSCREEN_H

#include "PhysicalScreen.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include <Wire.h>

/// @brief Class to drive monochrome OLEDs with EX-Display, noting all colours are ignored
class OLEDScreen : public PhysicalScreen {
public:
#if SCREEN_TYPE == OLED_SSD1306
  OLEDScreen(Adafruit_SSD1306 &oled, uint8_t muxAddress = 0, uint8_t subBus = 255);
#elif SCREEN_TYPE == OLED_SH1106
  OLEDScreen(Adafruit_SH1106G &oled, uint8_t muxAddress = 0, uint8_t subBus = 255);
#endif

  virtual void setupScreen(uint8_t rotation, uint8_t textSize, uint16_t backgroundColour) override;

  virtual void clearScreen(uint16_t backgroundColour) override;

  virtual void clearRow(uint8_t row, uint16_t backgroundColour) override;

  virtual void writeRow(uint8_t row, uint8_t column, uint16_t fontColour, uint16_t backgroundColour, uint8_t maxLength,
                        char *message, bool underlined) override;

  virtual void writeLine(uint8_t row, uint8_t column, uint8_t lineLength, uint16_t lineColour,
                         uint16_t backgroundColour) override;

private:
#if SCREEN_TYPE == OLED_SSD1306
  Adafruit_SSD1306 &_oled;
#elif SCREEN_TYPE == OLED_SH1106
  Adafruit_SH1106G &_oled;
#endif
  uint8_t _muxAddress;
  uint8_t _subBus;

  /// @brief Private method to get the text width using current font settings
  /// @return Text width
  uint8_t _getTextWidth();

  /// @brief Private method to select the correct MUX and sub bus if required for this screen
  /// @param muxAddress Valid MUX address, 0x70 - 0x77
  /// @param subBus Valid MUX sub bus, 0 - 7
  static void _switchMUX(uint8_t muxAddress, uint8_t subBus);
};

#endif

#endif
