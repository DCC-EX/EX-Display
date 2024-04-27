#ifndef EX_DISPLAY_H
#define EX_DISPLAY_H

#if defined(ARDUINO_AVR_MEGA2560)
     #define RX_PIN 0 // Define the RX pin for Serial1
     #define SERIAL Serial
     //#define SERIAL Serial1
     //#define RX_PIN 19 // Define the RX pin for Serial1

     #elif defined(ARDUINO_AVR_UNO)
     #define RX_PIN 0
     #define SERIAL Serial
     #elif defined(ESP32)
     #define RX_PIN 0
     #define SERIAL Serial

    #elif defined(ARDUINO_NUCLEO_F411RE) 
    HardwareSerial Serial1(PB7, PA15);  // Rx=PB7, Tx=PA15 -- CN7 pins 17 and 21 - F411RE
     #define SERIAL Serial1
     #define RX_PIN PB7;

     #elif defined(ARDUINO_NUCLEO_F446RE) 
     HardwareSerial Serial5(PD2, PC12);  // Rx=PD2, Tx=PC12 -- UART5 - F446RE
     #define SERIAL Serial5
     #define RX_PIN PD2;
     
#endif

#endif