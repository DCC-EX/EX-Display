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
  // Where does this really belong, and how can we use it to query and set attributes externally?
  struct RowAttributes {
    bool line : 1;
    bool underline : 1;
    bool alwaysTicker : 1;
    bool neverTicker : 1;
  };

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
  void setColours(uint16_t textColour, uint16_t backgroundColour);

  /// @brief Get the text/foreground colour for this row
  /// @return Colour code
  uint16_t getTextColour();

  /// @brief Get the background colour for this row
  /// @return Colour code
  uint16_t getBackgroundColour();

  /// @brief Check if this row is a horizontal line
  /// @return true|false
  bool isLine();

  /// @brief Check if this row should be underlined
  /// @return true|false
  bool isUnderlined();

  /// @brief Get all current attributes for the row
  /// @return 0 - 255
  uint8_t getAttributes();

private:
  uint8_t _rowNumber;  // This is the row number received from the parser
  uint8_t _maxMalloc;  // This is the calculated maximum length of the text received from the parser
  char *_rowText;      // This is the text received from the parser
  bool _changed;       // Flag set when text received from the parser is different to rowText
  uint8_t _displayRow; // This is the calculated physical row on a display that this line belongs on
  bool _needsRender;   // Flag that is set when row belongs on a physical display, false when off-screen
  EXDisplayRow *_next;
  uint16_t _textColour;       // Text/foreground colour for this row
  uint16_t _backgroundColour; // Background colour for this row
  byte _rowAttributes;        // One bit per attribute to allow 8 total

  /// @brief Private method to format the row attributes for the specified row
  /// @param row Pointer to an EXDisplayRow object
  static void _rowFormatter(EXDisplayRow *row, char *rowText);

  /// @brief Check for "#0xdddd#0xdddd#"
  /// @param text Char array to check
  /// @return true|false
  static bool _isEmbeddedColours(const char *text);

  /// @brief Extract colour codes from text
  /// @param text Char array containing codes (see _isEmbeddedColours)
  void _extractColours(const char *text);

  /// @brief Set the line attribute for this row
  /// @param line true|false
  void _setLine();
  
  /// @brief Check for "--"
  /// @param text Char array to check
  /// @return true|false
  static bool _isLine(const char *text);

  /// @brief Set the underline attribute for this row
  /// @param underline true|false
  void _setUnderline();

  /// @brief Check for "_Underlined text_"
  /// @param text Char array to check
  /// @return true|false
  static bool _isUnderline(const char *text);

  /// @brief Check for "~~Always ticker this text"
  /// @param text Char array to check
  /// @return true|false
  static bool _alwaysTicker(const char *text);

  /// @brief Check for "!~Never ticker this text"
  /// @param text Char array to check
  /// @return true|false
  static bool _neverTicker(const char *text);
};
#endif