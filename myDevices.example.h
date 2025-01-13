/*
 *  © 2024 Peter Cole
 *
 *  This is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  It is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this code.  If not, see <https://www.gnu.org/licenses/>.
 */

/**
 * @file myDevices.example.h
 * @brief This is an example myDevices.h outlining the available devices that can be configured
 * @details
 * DO NOT EDIT THIS FILE! Copy it to myDevices.h and edit that.
 * Each available type has an example and description.
 * Note that there are no default devices as there are too many available user options to provide a sensible default.
 * Any parameters with prefaced by * are optional and can be ommitted as per the examples displayed.
 *
 * Each display has an auto generated ID starting at 0, and these are generated in the order the displays are defined in
 * myDevices.h.
 */

/**
 * Display devices using the TFT_eSPI display library
 *
 * USER_DISPLAY(TFT_eSPIDisplay, rotation, text font, text colour, background colour, *chip select pin)
 *
 * Example for a single display with rotation set to 1, text font FreeMono12pt7b, white text colour, and black background colour
 * Omit the final chip select pin parameter for a single display.
 * TEXT_FONT is a default font provided in the display header file and is set to FONT_TFT_ESPI_MEDIUM i.e. FreeMono12pt7b.
 * If a defferent font is requires substitute the font define for TEXT_FONT in the example below.
 * USER_DISPLAY(TFT_eSPIDisplay, 1, TEXT_FONT, TFT_WHITE, TFT_BLACK)
 *
 * Example for two displays as above, but specifying the chip select pin to manually switch the displays
 * This is necessary as the TFT_eSPI library doesn't directly support multiple displays
 * USER_DISPLAY(TFT_eSPIDisplay, 1, TEXT_FONT, TFT_WHITE, TFT_BLACK, 15)
 * USER_DISPLAY(TFT_eSPIDisplay, 1, TEXT_FONT, TFT_WHITE, TFT_BLACK, 16)
 * 
 * The available fonts that are defined for use are listed at the top of the appropriate display header file 
 * In the case of TFT_eSPI screens that is TFT_eSPIDisplay.h.  These are a selection of fonts that have been define from the 
 * library GFXFF FreeFonts.
 * 
 * If you wish to use a font that is not defined in the header file, it is possible to add an elternative (see config.example.h)
 * 
 * Uncomment and edit one or more lines below as required for your setup.
 */

// USER_DISPLAY(TFT_eSPIDisplay, 1, TEXT_FONT, TFT_WHITE, TFT_BLACK)
// USER_DISPLAY(TFT_eSPIDisplay, 1, TEXT_FONT, TFT_WHITE, TFT_BLACK, 15)
// USER_DISPLAY(TFT_eSPIDisplay, 1, 1TEXT_FONT, TFT_WHITE, TFT_BLACK, 16)

/**
* If using multiple displays on a processor that can support this, it is possible to set a specific font for each screen.
* The following three lines give an example that has been tested with three SPI displays on an ESP32.  Each display is
* configured with a different font from the list available.
* Note that each screen has been given a different orientation.  This works to a point but has a limitation imposed by the
* library.  Orientations 180 degrees opposed work OK, but an orientation 90 degrees to the first will not have the background
* rendered correctly i.e the height and width attributes do not adjust.
* If using mixed orientations its best to use 0 & 2 or 1 & 3.
*
* USER_DISPLAY(TFT_eSPIDisplay, 1, FONT_TFT_ESPI_SMALL, TFT_WHITE, TFT_BLACK, 12)
* USER_DISPLAY(TFT_eSPIDisplay, 2, FONT_TFT_ESPI_SERIF_BOLD_ITALIC, TFT_WHITE, TFT_BLUE, 13)
* USER_DISPLAY(TFT_eSPIDisplay, 3, FONT_TFT_ESPI_LARGE, TFT_WHITE, TFT_RED, 14)
*/

/**
 * Display devices using the MCUFRIEND_kbv display library
 * 
 * USER_DISPLAY(MCU_Display, ......)
 *
 * Uncomment and edit one or more lines below as required for your setup.
 */

/**
 * Display devices using **OLED**?? library
 * 
 * USER_DISPLAY(OLED_Display, ......)
 * 
 * Uncomment and edit one or more lines below as required for your setup.
 */

/**
 * Input devices for touch screens using the TFT_eSPI display library by bodmer, which require an existing display
 * instance to be defined
 * 
 * USER_INPUT(TFT_eSPITouch, display ID)
 * 
 * Example using the first defined TFT_eSPIDisplay instance which will have ID 0
 * USER_INPUT(TFT_eSPITouch, 0)
 * 
 * Uncomment and edit one or more lines below as required for your setup.
 */

// USER_INPUT(TFT_eSPITouch, 0)
