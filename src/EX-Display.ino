
#include <Arduino.h>
#include "AtFinder.h"
#include "config.h"
#include "EX-Screen.h"

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


// callback function when a <@ id row "text"> message detected 
void processDisplay(int16_t screenId,int16_t screenRow, char* text) {
    Serial.print(F("\n id="));
    Serial.print(screenId);
    Serial.print(F(" row="));
    Serial.print(screenRow);
    Serial.print(F(" text=\""));
    Serial.print(text);
    Serial.print(F("\"\n"));
}

bool StartupPhase = true;
long timestamp = 0;
long screencount = 0;

    
void setup() {
    SERIAL.begin(115200);
    //SERIAL1.begin(115200); // Start Serial1 for listening to messages

    // Tell AtFinder our maximum supported text length,
    // and how to call back when found.
    AtFinder::setup(100,processDisplay);

    SCREEN::TFT_Startup(); 
    //tft.invertDisplay(1);
    //tft.invertDisplay(0);

    SERIAL.println("End of Setup");
    delay(1000);

    timestamp = millis();

}

void loop() {

    // Check if we are in the startup phase 
    // This phase inhibits screen drawing until the startup messages are
    // issued by the CS
    if (StartupPhase) {
        if ((millis() - timestamp) >= STARTUP_TIME){
                StartupPhase=false;
                screencount=millis();
        }
    }

    // each byte received form serial is passed to the parse 
    if (Serial.available()) AtFinder::processInputChar(Serial.read());

// No data incoming so see if we need to display anything
    if (StartupPhase==false){

        if (ScreenChanged[THIS_SCREEN_NUM]==true) {
            SERIAL.print("Time to draw a screen line");
            SCREEN::StartScreenPrint();
            PrintInProgress=true;
            ScreenChanged[THIS_SCREEN_NUM] = false;
        }
        
        if (PrintInProgress==true) { 
            SERIAL.println("Pinting a line");
            SCREEN::PrintALine();
        }
  }

    //Check Page Time to see if we need to scroll
    if((millis()-screencount) > SCROLLTIME) {

        if (THIS_SCREEN_NUM >= MAX_SCREENS-1) {
        THIS_SCREEN_NUM=0;
        }
        else {
        THIS_SCREEN_NUM++;
        
        }
        screencount=millis();
        ScreenChanged[THIS_SCREEN_NUM] = true;

    }


}