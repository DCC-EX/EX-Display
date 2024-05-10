#ifndef VERSION_H
#define VERSION_H

// Numeric version here: major.minor.patch
#define VERSION "0.0.6"

// 0.0.6 includes:
//  - Add ability to set individual row colours via the parser
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
