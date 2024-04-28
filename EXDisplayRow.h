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

  
  /// @brief Set the pointer to the next EXDisplayRow object in the linked list
  /// @param next Pointer to the next EXDisplayRow object
  void setNext(EXDisplayRow *next);

  /// @brief Get the next row
  /// @return Pointer to the next EXDisplayRow object in the linked list
  EXDisplayRow *getNext();

private:
  uint8_t _rowNumber;
  uint8_t _maxMalloc;
  char *_rowText;
  bool _changed;
  EXDisplayRow *_next;
};
#endif