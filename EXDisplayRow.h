#ifndef EXDisplayRow_H
#define EXDisplayRow_H

#include <Arduino.h>

/**
 * @brief Class for each row associated with a display.
 * Each row is a member of a linked list which is an attribute of an EXDisplay object.
 *
 */
class EXDisplayRow {

  /// @brief Struct for row attributes, which allows for 8 in total
  struct RowAttributes {
    bool line : 1;
    bool neverTicker : 1;
    bool alwaysTicker : 1;
  };

public:
  /// @brief Constructor for the EXDisplayRow object
  /// @param rowNumber Row number on the display, 0 - 255
  EXDisplayRow(uint8_t rowNumber);

  /// @brief Get the row number this should be displayed on
  /// @return 0 - 255
  uint8_t getRowNumber();

  /// @brief Get the maximum length this row has been set to
  /// @return 0 - 255
  uint8_t getMaxRowLength();

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

  /// @brief Set the text/foreground and background colour for this row
  /// @param textColour Hex value of the text/foreground colour
  /// @param backgroundColour Hex value of the background colour
  void setRowColours(uint16_t textColour, uint16_t backgroundColour);

  /// @brief Get the text/foreground colour for this row
  /// @return Colour code
  uint16_t getTextColour();

  /// @brief Get the background colour for this row
  /// @return Colour code
  uint16_t getBackgroundColour();

  /// @brief Set if this row is a line or not, if it is, will clear any text
  /// @param line true|false
  void setLine(bool line);

  /// @brief Check if this row is a line
  /// @return true|false
  bool isLine();

private:
  uint8_t _rowNumber;  // This is the row number received from the parser
  uint8_t _maxMalloc;  // This is the calculated maximum length of the text received from the parser
  char *_rowText;      // This is the text received from the parser
  bool _changed;       // Flag set when text received from the parser is different to rowText
  uint8_t _displayRow; // This is the calculated physical row on a display that this line belongs on
  bool _needsRender;   // Flag that is set when row belongs on a physical display, false when off-screen
  EXDisplayRow *_next;
  uint16_t _textColour;                       // Text/foreground colour for this row
  uint16_t _backgroundColour;                 // Background colour for this row
  EXDisplayRow::RowAttributes _rowAttributes; // One bit per attribute to allow 8 total
};
#endif