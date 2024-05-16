#ifndef VERSION_H
#define VERSION_H

// Numeric version here: major.minor.patch
#define VERSION "0.0.8"

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
