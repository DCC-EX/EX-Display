#ifndef EX_DISPLAY_H
#define EX_DISPLAY_H

#if __has_include("config.h")
#include "config.h"
#else
#warning Configuration file "config.h" not found, using example file "config.example.h"
#include "config.example.h"
#endif

#if defined(ARDUINO_AVR_MEGA2560)
#define RX_PIN 0 // Define the RX pin for Serial1
#define CONSOLE Serial
#define CS_LISTEN Serial1
//#define RX_PIN 19 // Define the RX pin for Serial1

#elif defined(ARDUINO_AVR_UNO)
#define RX_PIN 0
#define CONSOLE Serial
#define CS_LISTEN Serial
#elif defined(ESP32)
#define RX_PIN 0
#define CONSOLE Serial
#define CS_LISTEN Serial

#elif defined(ARDUINO_NUCLEO_F411RE) 
#define CONSOLE Serial
HardwareSerial Serial1(PB7, PA15);  // Rx=PB7, Tx=PA15 -- CN7 pins 17 and 21 - F411RE
#define CS_LISTEN Serial1
#define RX_PIN PB7;

#elif defined(ARDUINO_NUCLEO_F446RE) 
#define CONSOLE Serial
HardwareSerial Serial5(PD2, PC12);  // Rx=PD2, Tx=PC12 -- UART5 - F446RE
#define CS_LISTEN Serial5
#define RX_PIN PD2;
     
#endif

#endif