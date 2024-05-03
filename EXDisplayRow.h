#ifndef EXDisplayRow_H
#define EXDisplayRow_H

#include <Arduino.h>

/**
 * @brief Class for each row associated with a display.
 * Each row is a member of a linked list which is an attribute of an EXDisplay object.
 *
 */
class EXDisplayRow {
public:
  /// @brief Constructor for the EXDisplayRow object
  /// @param rowNumber Row number on the display, 0 - 255
  EXDisplayRow(uint8_t rowNumber);

  /// @brief Get the row number this should be displayed on
  /// @return 0 - 255
  uint8_t getRowNumber();

  /// @brief Update the text for the specified row
  /// @param rowText Char array containing the text
  void setRowText(char *rowText);

  /// @brief Get the text associated with this row
  /// @return Char array
  char *getRowText();

  /// @brief Check if this row has been changed, set when setRowText called, reset when getRowText called
  /// @return True|False
  bool isChanged();

  /// @brief Set the physical screen row this row should be rendered/drawn on and provide the max rows for the screen
  /// @param displayRow 0 - 255
  /// @param maxScreenRows Maximum number of rows the screen can display - sets _needsRender
  void setDisplayRow(uint8_t displayRow, uint8_t maxScreenRows);

  /// @brief calculated to determine which screen row is used
  /// @return 0 - 255
  uint8_t getDisplayRow();

  /// @brief Check if this row fits on a physical display and needs to be rendered/drawn
  /// @return True|False
  bool needsRender();

  /// @brief Set the pointer to the next EXDisplayRow object in the linked list
  /// @param next Pointer to the next EXDisplayRow object
  void setNext(EXDisplayRow *next);

  /// @brief Get the next row
  /// @return Pointer to the next EXDisplayRow object in the linked list
  EXDisplayRow *getNext();

private:
  uint8_t _rowNumber;  // This is the row number received from the parser
  uint8_t _maxMalloc;  // This is the calculated maximum length of the text received from the parser
  char *_rowText;      // This is the text received from the parser
  bool _changed;       // Flag set when text received from the parser is different to rowText
  uint8_t _displayRow; // This is the calculated physical row on a display that this line belongs on
  bool _needsRender;   // Flag that is set when row belongs on a physical display, false when off-screen
  EXDisplayRow *_next;
};
#endif