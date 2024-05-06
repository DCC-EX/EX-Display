#ifndef CONFIG_H
#define CONFIG_H

// This is the configuration file for EX-Display
// Entries here will control how the screen display will operate

// Define the screen types in use here - this needs to be ultra simplified at some point
// Should we eventually support up to 3 displays?
#define SCREEN_0_TYPE MCU
// #define SCREEN_0_TYPE TFT
// #define SCREEN_1_TYPE MCU
// #define SCREEN_2_TYPE MCU

// DO NOT REMOVE OR MOVE THIS LINE - MUST BE BEFORE FONT DEFINITION
// Include the various fonts and font colours available for use with EX-Display
#include "FontOptions.h"
// Font options
#define TEXT_FONT MEDIUM
#define TEXT_COLOUR WHITE
#define TEXT_SIZE 1
#define BACKGROUND_COLOUR BLACK

// If rotation of the screen is required, set it here
#define SCREEN_ROTATION 1

// First entries about the display you are using
// as we display across the wider part of the screen iwdth is the larger dimension
#define DISPLAY_WIDTH 320
#define DISPLAY_HEIGHT 240

// Now we have to define how many screens you wish to display
// The system output screen is 0.
// An arduino Uno is capable of storing and displaying about 60 lines
// before running out of RAM e.g. (using 30 char lines)
// 4 screens of 16 lines
// 6 screens of 10 lines
// The first paramater tells EX-Display which initial screen to display
#define INITIAL_SCREEN 0

// Now define how many screens you wish to be used in turn
#define MAX_SCREENS 2
#define MAX_ROWS 10

// If a touch screen is in use a touch will swap from screen to screen
// if in use uncomment the following
// #define USE_TOUCH

// if the touch screen not in use, Now define the scroll requirements
#define SCROLLTIME 5000 // 5 seconds

// And now define the maximum text length.
#define MAX_LINE_LENGTH 30

// The startup Timelapse - allows time to handle all the CS output
#define STARTUP_TIME 2000

// Uncomment this line to display debug output
#define DEBUG

#endif