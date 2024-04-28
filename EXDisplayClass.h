#ifndef DISPLAYCLASS_H
#define DISPLAYCLASS_H

#include <Arduino.h>

#include "EXDisplayRow.h"
/**
 * @brief Class for each display.
 * Each display is in a linked list, with associated rows in a linked list as an attribute of the EXDisplay object.
 *
 */
class EXDisplay {
public:
  EXDisplay(uint8_t displayNumber, uint8_t maxScreenWidth);

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


  /// @brief Get the maximum width of the hardware  - used to determine ticker attribute if text is wider than this
  /// @return 0 - 255
  uint8_t getMaxScreenWidth();

  
  /// @brief Get an EXDisplayRow object for this display by the specified row number
  /// @param rowNumber Row number to retrieve, 0 - 255
  /// @return Pointer to an EXDisplayRow object, or nullptr if not exists
  EXDisplayRow *getRowByNumber(uint8_t rowNumber);

  /// @brief Update text and ticker for the specified row number, will add if it doesn't exist
  /// @param rowNumber Row number to display text on, 0 - 255
  /// @param rowText Char array of text for the row
  void updateRow(uint8_t rowNumber, char *rowText);


  /// @brief Check if there is already a display created at the specified number
  /// @param displayNumber True|False
  /// @return
  static bool displayNumberExists(uint8_t displayNumber);

  /// @brief Get the display and associated row linked list for the specified display number
  /// @param displayNumber Display number to get, 0 - 255
  /// @return EXDisplay object, or nullptr if not exists
  static EXDisplay *getDisplayByNumber(uint8_t displayNumber);

private:
  // chaining displays
  static EXDisplay *_first;
  EXDisplay *_next;
  // display data and rows
  uint8_t _displayNumber;
  EXDisplayRow *_firstRow;
  // Screen management variables added here 
  uint8_t _maxScreenWidth; 
};

#endif
