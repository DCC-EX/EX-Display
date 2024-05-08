#ifndef EXDISPLAYCLASS_H
#define EXDISPLAYCLASS_H

#include <Arduino.h>

#include "Defines.h"
#include "EXDisplayRow.h"
#include "EXScreen.h"

/**
 * @brief Class for each display.
 * Each display is in a linked list, with associated rows in a linked list as an attribute of the EXDisplay object.
 *
 */
class EXDisplay {
public:
  /// @brief Constructor for the EXDisplay class
  /// @param displayNumber The ID of this display, 0 - 254
  /// @param exScreen Pointer to an associated EXScreen object to use for the physical display
  /// @param maxScreenWidth Maximum number of characters that will fit on the physical screen, 0 - 255
  EXDisplay(uint8_t displayNumber, EXScreen *exScreen, uint8_t maxScreenWidth);

  /// @brief Get the first EXDisplay object in the linked list
  /// @return Pointer to the first EXDisplay object
  static EXDisplay *getFirst();

  /// @brief Get the next EXDisplay object in the linked list
  /// @return Pointer to the next EXDisplay object
  EXDisplay *getNext();

  /// @brief Get the first EXDisplayRow object associated with this display
  /// @return Pointer to the first EXDisplayRow object for this display
  EXDisplayRow *getFirstRow();

  /// @brief Get the display's number
  /// @return 0 - 255
  uint8_t getDisplayNumber();

  /// @brief Get an EXDisplayRow object for this display by the specified row number
  /// @param rowNumber Row number to retrieve, 0 - 255
  /// @return Pointer to an EXDisplayRow object, or nullptr if not exists
  EXDisplayRow *getRowByNumber(uint8_t rowNumber);

  /// @brief Update text and ticker for the specified row number, will add if it doesn't exist
  /// @param rowNumber Row number to display text on, 0 - 255
  /// @param rowText Char array of text for the row
  void updateRow(uint8_t rowNumber, char *rowText);

  /// @brief Scroll one row vertically
  void scroll();

  /// @brief Method to automatically update row positions for automatic vertical scrolling
  /// @param scrollDelay Time in milliseconds between vertical scrolling updates
  void autoScroll(unsigned long scrollDelay);

  /// @brief Get the EXScreen object associated with this display
  /// @return Pointer to the associated EXScreen object
  EXScreen *getEXScreen();

  /// @brief Get the maximum number of rows displayable on the associated screen
  /// @return 0 - 255
  uint8_t getScreenMaxRows();

  /// @brief Get the maximum number of columns displayable on the associated screen
  /// @return 0 - 255
  uint8_t getScreenMaxColumns();

  /// @brief Check if this display needs to be redrawn
  /// @return True|False
  bool needsRedraw();

  /// @brief Reset the needsRedraw flag
  void resetRedraw();

  /// @brief Check if there is already a display created at the specified number
  /// @param displayNumber True|False
  /// @return
  static bool displayNumberExists(uint8_t displayNumber);

  /// @brief Get the display and associated row linked list for the specified display number
  /// @param displayNumber Display number to get, 0 - 255
  /// @return EXDisplay object, or nullptr if not exists
  static EXDisplay *getDisplayByNumber(uint8_t displayNumber);

  /// @brief Get the currently selected display
  /// @return Pointer to the currently selected display
  static EXDisplay *getActiveDisplay();

  /// @brief Switch active display to the next display in the linked list
  static void switchActiveDisplay();

private:
  // chaining displays
  static EXDisplay *_first;
  EXDisplay *_next;
  // display data and rows
  uint8_t _displayNumber;
  EXDisplayRow *_firstRow;
  EXScreen *_exScreen;
  // Screen management variables added here
  uint8_t _maxScreenWidth;       // Maximum number of chars that can fit on the physical screen
  uint8_t _numberOfRows;         // Calculated number of rows for this screen
  uint8_t _scrollPosition;       // Row number that is top of screen for scrolling support
  unsigned long _lastScrollTime; // Last time in milliseconds an auto scroll was done
  bool _needsRedraw;             // Flag if this display needs to be redrawn
  static EXDisplay *_activeDisplay;
};

#endif
