#ifndef EX_DISPLAY_H
#define EX_DISPLAY_H

#define MCU 1
#define TFT 2
#define OLED_SSD1306 3
#define OLED_SH1106 4

#if __has_include("config.h")
#include "config.h"
#else
#warning Configuration file "config.h" not found, using example file "config.example.h"
#include "config.example.h"
#endif

// Set default parameters if not set in config.h for some reason
#ifndef TEXT_FONT
#define TEXT_FONT MEDIUM
#endif
#ifndef TEXT_COLOUR
#define TEXT_COLOUR WHITE
#endif
#ifndef TEXT_SIZE
#define TEXT_SIZE 1
#endif
#ifndef BACKGROUND_COLOUR
#define BACKGROUND_COLOUR BLACK
#endif
#ifndef SCREEN_ROTATION
#define SCREEN_ROTATION 1
#endif

#if SCREEN_TYPE == MCU
#define NEEDS_MCU
#define SCREEN_0 new EXDisplay(0, new MCUFriendScreen(tft), 30);
#elif SCREEN_TYPE == TFT
#define NEEDS_TFT
#define SCREEN_0 new EXDisplay(0, new TFT_eSPIScreen(tft), 30);
#elif SCREEN_TYPE == OLED_SSD1306 || SCREEN_TYPE == OLED_SH1106
#define NEEDS_OLED
#define SCREEN_0 new EXDisplay(0, new OLEDScreen(oled), 30);
#else
#error A screen type for the first screen has not been set, you must define either MCU or TFT
#endif

// Set up console and CS listener for Mega
#if defined(ARDUINO_AVR_MEGA2560)
#define RX_PIN 0 // Define the RX pin for Serial1
#define CONSOLE Serial
#define CS_LISTEN Serial1
//#define RX_PIN 19 // Define the RX pin for Serial1
#define USE_EEPROM
// Set up console and CS listener for Uno
#elif defined(ARDUINO_AVR_UNO)
#define RX_PIN 0
#define CONSOLE Serial
#define CS_LISTEN Serial
#define USE_EEPROM
// Set up console and CS listener for ESP32
#elif defined(ARDUINO_ARCH_ESP32)
#define RX_PIN 0
#define CONSOLE Serial
#define CS_LISTEN Serial
#define USE_SPIFFS
// Set up console and CS listener for F411RE
#elif defined(ARDUINO_NUCLEO_F411RE)
#define CONSOLE Serial
HardwareSerial Serial1(PB7, PA15); // Rx=PB7, Tx=PA15 -- CN7 pins 17 and 21 - F411RE
#define CS_LISTEN Serial1
#define RX_PIN PB7;
#define USE_FLASH
// Set up console and CS listener for F446RE
#elif defined(ARDUINO_NUCLEO_F446RE)
#define CONSOLE Serial
HardwareSerial Serial5(PD2, PC12); // Rx=PD2, Tx=PC12 -- UART5 - F446RE
#define CS_LISTEN Serial5
#define RX_PIN PD2;
#define USE_FLASH
#endif

// If user has defined SERIAL_ONLY, override CS_LISTEN
#ifdef SERIAL_ONLY
#undef CS_LISTEN
#define CS_LISTEN Serial
#endif

#endif