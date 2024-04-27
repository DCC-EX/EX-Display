#ifndef DISPLAYCLASS_H
#define DISPLAYCLASS_H

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
  /// @param rowText Char array of text for the row, max length is the EXDisplay object's maxRowWidth attribute
  /// @param ticker True to ticker even if shorter than screen width, false not to ticker even if wider than screen width
  EXDisplayRow(uint8_t rowNumber, char *rowText, bool ticker = false, bool changed = true);

  /// @brief Get the row number this should be displayed on
  /// @return 0 - 255
  uint8_t getRowNumber();

  /// @brief Update the text for the specified row
  /// @param rowText Char array containing the text
  void setRowText(char *rowText);

  /// @brief Get the text associated with this row
  /// @return Char array
  char *getRowText();

  /// @brief Update the ticker flag for the specified row
  /// @param ticker True|False
  void setTicker(bool ticker);
  
  /// @brief Check if this row should scroll horizontally as a ticker
  /// @return True|False
  bool isTicker();

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
  char *_rowText;
  bool _ticker;
  bool _changed;
  EXDisplayRow *_next;
};

/**
 * @brief Class for each display.
 * Each display is in a linked list, with associated rows in a linked list as an attribute of the EXDisplay object.
 * 
 */
class EXDisplay {
public:
  EXDisplay(uint8_t displayNumber, uint8_t maxRows, uint8_t maxColumns, uint16_t maxRowWidth, bool autoTicker,
            EXDisplay *copyOf = nullptr);

  /// @brief Get the display's number
  /// @return 0 - 255
  uint8_t getDisplayNumber();

  /// @brief Get the maximum number of rows for this display
  /// @return 0 - 255
  uint8_t getMaxRows();

  /// @brief Get the maximum number of columns - used to determine ticker attribute if text is wider than this
  /// @return 0 - 255
  uint8_t getMaxColumns();

  /// @brief Get the maximum text width - determines max row width
  /// @return 0 - 65535
  uint16_t getMaxRowWidth();

  /// @brief Check if rows should automatically ticker horizontally if greater than max columns
  /// @return True to automatically ticker, false to use the row's ticker attribute
  bool isAutoTicker();

  /// @brief Check if this display should be a direct copy of another display
  /// @return Pointer to an EXDisplay object it should use the rows from, or nullptr
  EXDisplay *getCopyOf();

  /// @brief Get an EXDisplayRow object for this display by the specified row number
  /// @param rowNumber Row number to retrieve, 0 - 255
  /// @return Pointer to an EXDisplayRow object, or nullptr if not exists
  EXDisplayRow *getRowByNumber(uint8_t rowNumber);

  /// @brief Update text and ticker for the specified row number, will add if it doesn't exist
  /// @param rowNumber Row number to display text on, 0 - 255
  /// @param rowText Char array of text for the row, max length is the EXDisplay object's maxRowWidth attribute
  /// @param ticker True for horizontal scroll (ticker), false not to scroll even if wider than screen width
  void updateRow(uint8_t rowNumber, char *rowText, bool ticker = false);

  /// @brief Delete the object at the specified row number
  /// @param rowNumber Row number to delete, 0 - 255
  void deleteRowNumber(uint8_t rowNumber);

  /// @brief Check if there is already a display created at the specified number
  /// @param displayNumber True|False
  /// @return
  static bool displayNumberExists(uint8_t displayNumber);

  /// @brief Get the display and associated row linked list for the specified display number
  /// @param displayNumber Display number to get, 0 - 255
  /// @return EXDisplay object, or nullptr if not exists
  static EXDisplay *getDisplayByNumber(uint8_t displayNumber);

private:
  uint8_t _displayNumber;
  uint8_t _maxRows;
  uint8_t _maxColumns;
  uint16_t _maxRowWidth;
  bool _autoTicker;
  EXDisplay *_copyOf;
  EXDisplayRow *_firstRow;
  static EXDisplay *_first;
  EXDisplay *_next;
};

#endif
