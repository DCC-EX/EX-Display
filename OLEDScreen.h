#include "Defines.h"
#ifdef NEEDS_OLED

#ifndef OLEDSCREEN_H
#define OLEDSCREEN_H

#include "PhysicalScreen.h"
#include <Arduino.h>
#include <SSD1306Ascii.h>
#include <SSD1306AsciiWire.h>
#include <Wire.h>

/// @brief Class to drive monochrome OLEDs with EX-Display, noting all colours are ignored
class OLEDScreen : public PhysicalScreen {
public:
  // OLEDScreen(Adafruit_SSD1306 &oled, uint8_t muxAddress = 0, uint8_t subBus = 255);
  OLEDScreen(uint8_t screenWidth, uint8_t screenHeight, uint8_t deviceAddress = 0x3C, uint8_t muxAddress = 0,
             uint8_t subBus = 255);

  virtual PhysicalScreen *setupScreen(uint8_t rotation, uint8_t textSize, uint16_t backgroundColour) override;

  virtual void clearScreen(uint16_t backgroundColour) override;

  virtual void clearRow(uint8_t row, uint16_t backgroundColour) override;

  virtual void writeRow(uint8_t row, uint8_t column, uint16_t fontColour, uint16_t backgroundColour, uint8_t maxLength,
                        char *message, bool underlined) override;

  virtual void writeLine(uint8_t row, uint8_t column, uint8_t lineLength, uint16_t lineColour,
                         uint16_t backgroundColour) override;

  virtual uint16_t getHeight() override;

  virtual uint16_t getWidth() override;

private:
  SSD1306AsciiWire *_oled;
  uint8_t _screenWidth;
  uint8_t _screenHeight;
  uint8_t _deviceAddress;
  uint8_t _muxAddress;
  uint8_t _subBus;

  /// @brief Private method to get the text width using current font settings
  /// @return Text width
  uint8_t _getTextWidth();

  /// @brief Private method to select the correct MUX and sub bus if required for this screen
  /// @param muxAddress Valid MUX address, 0x70 - 0x77
  /// @param subBus Valid MUX sub bus, 0 - 7
  void _switchMUX();
};

#endif

#endif
