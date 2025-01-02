#ifndef VERSION_H
#define VERSION_H

// Numeric version here: major.minor.patch
#define VERSION "0.0.20"

// 0.0.20 includes:
//  - Update log levels with LOG_ preface to avoid STM32 framework conflicts for ERROR
// 0.0.19 includes:
//  - Resolved multiple TFT_eSPI screens not operating independently by using static TFT_eSPI instance
// 0.0.18 includes:
//  - Added ability to force touchscreen calibration if required
// 0.0.17 includes:
//  - Improved experimental support for multiple TFT_eSPI instances
// 0.0.16 includes:
//  - Add configuration of input device via macro USER_INPUT()
// 0.0.15 includes:
//  - Fix missing redraw functionality when switching screens
//  - Implemented myDevices.h to configure display devices via macro USER_DISPLAY()
// 0.0.14 includes:
//  - Major rewrite using OOP
//  - Swap display/screen terminology - screen is logical from EX-CommandStation, display is physical
//  - Basic function of a single screen 0 to a single display 0
//  - Add tests
// 0.0.13 includes:
//  - Improved user configuration
//  - Swap OLED support to use SSD1306_Ascii
// 0.0.12 includes:
//  - Fixed left button selecting previous logical display
// 0.0.11 includes:
//  - Add InputMethod class with support for TFT_eSPI and MCUFRIEND_kbv touch screens
//  - Also add support for physical push buttons
// 0.0.10 includes:
//  - Refactor so that logical displays are attributes of physical screens
//  - This should simplify addition of touch/input control
//  - Ensure order of logical displays in linked list are in ascending order of number
// 0.0.9 includes:
//  - Add support for SSD1306 and SH1106 I2C connected OLEDs
//  - Disable text wrap
// 0.0.8 includes:
//  - Fix a bug where adding new rows while the screen is scrolling puts them on the wrong row
// 0.0.7 includes:
//  - Move row formatting to the EXDisplayRow class so only one call is needed to set a row up
//  - Change colour attributes to match other formatting options so they can be sent with text
//  - Implement support for deleting a row when sending "" as the message
// 0.0.6 includes:
//  - Add ability to set individual row colours via the parser
//  - Add ability to draw a horizontal line on a row rather than text
//  - Add ability to underline a row
// 0.0.5 includes:
//  - Refactor screen and logical display to enable multiple displays to use the same screen
//  - Enable timed switching between logical displays
//  - Enable timed vertical scrolling when there are more rows than can be on a single screen
//  - Moved display redraw function into the EXDisplay class to simplify screen updates
// 0.0.4 includes:
//  - Adjusted to use Adafruit fonts for MCUFRIEND_kbv
// 0.0.3 includes:
//  - Fixed TFT_eSPI row height calculations and overwrite of previous text
//  - Moved to using TFT_eSPI fonts only
//  - Refactored EXScreen and associated classes
//  - Calculate max rows and columns based on resolution and specified font size
// 0.0.2 includes:
//  - Adding TFT_eSPI library
//  - Implement vertical scrolling
// 0.0.1 includes:
//  - First version number for initial development

#endif
