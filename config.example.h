#ifndef CONFIG_H
#define CONFIG_H

// This is the configuration file for EX-Display
// Entries here will control how the screen display will operate

// Define the pphysical screen types in use here - this needs to be ultra simplified at some point
// Should we eventually support up to 3 displays?
#define SCREEN_TYPE MCU
// #define SCREEN_TYPE TFT
// #define SCREEN_TYPE OLED

// #define OLED_ADDRESS 0x3C

// Define the number of logical displays here
// This is not a good way to do this
#define NUMBER_OF_DISPLAYS 1
#define DISPLAY_1_ID 0
// #define DISPLAY_2_ID 3
// #define DISPLAY_3_ID 8

// DO NOT REMOVE OR MOVE THIS LINE - MUST BE BEFORE FONT DEFINITION
// Include the various fonts and font colours available for use with EX-Display
// Note for monochrome OLEDs you will need to set the OLED colour option here
#include "FontOptions.h"
// Font options
#define TEXT_FONT MEDIUM
#define TEXT_COLOUR WHITE
// #define TEXT_COLOUR OLED_WHITE
#define BACKGROUND_COLOUR BLACK
// #define BACKGROUND_COLOUR OLED_BLACK

// Set the pixel multiplier for text - this will multiple a single pixel by this number
// For OLED, this can only be 1 or 2
#define TEXT_SIZE 1

// If rotation of the screen is required, set it here
// TFT type screens typically require 1 or 3 to rotate from portrait to landscape
// Set to 0 for an OLED screen or 1 to rotate 180 degrees
// #define SCREEN_ROTATION 0
#define SCREEN_ROTATION 1
// #define SCREEN_ROTATION 2
// #define SCREEN_ROTATION 3

// Some screens need inverting. If your screen displays inverted colours uncomment the following line.
//#define INVERT_SCREEN

// First entries about the display you are using
// as we display across the wider part of the screen iwdth is the larger dimension
// These should only be required if using OLED screen type
// #define SCREEN_WIDTH 128
// #define SCREEN_HEIGHT 64

// If a touch screen is in use a touch will swap from screen to screen
// if in use uncomment the following
// #define USE_TOUCH

// If you have a need force recalibrating the touch screen, uncomment this line
// #define FORCE_CALIBRATION

// If using an MCUFRIEND_kbv type screen it requires the Adafruit TouchScreen driver
// You must define the below parameters for this scenario
// If using an MCUFRIEND_kbv type screen it requires the Adafruit TouchScreen driver
// You must define the below parameters for this scenario
// Example pins for Uno/Mega2560
const int XP = 9, XM = A3, YP = A2, YM = 8; // 320x480 ID=0x9488

// Example pins for ESP32 WROOM
// const int XP=32,XM=2,YP=4,YM=35; //320x480 ID=0x9488

// Also if using MCUFRIEND_kbv with the Adafruit TouchScreen driver you must define the below
// parameters for calibration
const int TS_LEFT = 114, TS_RT = 917, TS_TOP = 74, TS_BOT = 931;

// If using push buttons rather than a touch screen, comment out USE_TOUCH above and uncomment the below
// Also efine the GPIO pin used by each push button
// #define USE_BUTTONS

// Example pins for Mega2560
// #define LEFT_BUTTON 22
// #define RIGHT_BUTTON 23
// #define CENTRE_BUTTON 24
// #define UP_BUTTON 25
// #define DOWN_BUTTON 26

// Example pins for ESP32 WROOM
// #define LEFT_BUTTON 32
// #define RIGHT_BUTTON 33
// #define CENTRE_BUTTON 25
// #define UP_BUTTON 26
// #define DOWN_BUTTON 27

// if the touch screen not in use, Now define the scroll requirements
#define SCROLLTIME 1000 // 5 seconds

// If hosting multiple displays on the same screen, set switching delay
#define DISPLAY_SWITCH_TIME 5000

// And now define the maximum text length.
#define MAX_LINE_LENGTH 50

// The startup Timelapse - allows time to handle all the CS output
#define STARTUP_TIME 2000

// Uncomment this line to display debug output
#define DEBUG

// Uncomment this line when wanting to test with serial in put only, and no CS connection
// This overrides the input and only accepts input from the serial console
// #define SERIAL_ONLY

#endif