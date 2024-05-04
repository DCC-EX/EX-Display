#ifndef EX_DISPLAY_H
#define EX_DISPLAY_H

#if __has_include("config.h")
#include "config.h"
#else
#warning Configuration file "config.h" not found, using example file "config.example.h"
#include "config.example.h"
#endif

// Set default parameters if not set in config.h for some reason
#ifndef TEXT_FONT
#define TEXT_FONT ARIAL9PT7B
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

// Set up console and CS listener for Mega
#if defined(ARDUINO_AVR_MEGA2560)
#define RX_PIN 0 // Define the RX pin for Serial1
#define CONSOLE Serial
#define CS_LISTEN Serial1
//#define RX_PIN 19 // Define the RX pin for Serial1
// Set up console and CS listener for Uno
#elif defined(ARDUINO_AVR_UNO)
#define RX_PIN 0
#define CONSOLE Serial
#define CS_LISTEN Serial
// Set up console and CS listener for ESP32
#elif defined(ESP32)
#define RX_PIN 0
#define CONSOLE Serial
#define CS_LISTEN Serial
// Set up console and CS listener for F411RE
#elif defined(ARDUINO_NUCLEO_F411RE) 
#define CONSOLE Serial
HardwareSerial Serial1(PB7, PA15);  // Rx=PB7, Tx=PA15 -- CN7 pins 17 and 21 - F411RE
#define CS_LISTEN Serial1
#define RX_PIN PB7;
// Set up console and CS listener for F446RE
#elif defined(ARDUINO_NUCLEO_F446RE) 
#define CONSOLE Serial
HardwareSerial Serial5(PD2, PC12);  // Rx=PD2, Tx=PC12 -- UART5 - F446RE
#define CS_LISTEN Serial5
#define RX_PIN PD2;
     
#endif

#endif