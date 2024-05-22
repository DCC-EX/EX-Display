#ifndef LOGICALDISPLAY_H
#define LOGICALDISPLAY_H

#include "Defines.h"
#include "LogicalDisplayRow.h"
#include <Arduino.h>

class LogicalDisplay {
public:
  /// @brief Constructor for the LogicalDisplay class
  /// @param displayNumber The ID of this display, 0 - 254
  /// @param textColour Valid colour code for the default text colour
  /// @param backgroundColour Valid colour code for the default background colour
  LogicalDisplay(uint8_t displayNumber, uint8_t maxRowLength, uint8_t maxRowNumber, uint16_t textColour,
                 uint16_t backgroundColour);

  /// @brief Set the next display in the linked list
  /// @param display Pointer to the next LogicalDisplay instance
  void setNext(LogicalDisplay *display);

  /// @brief Get the next LogicalDisplay object in the linked list
  /// @return Pointer to the next LogicalDisplay object
  LogicalDisplay *getNext();

  /// @brief Get the first LogicalDisplayRow object associated with this display
  /// @return Pointer to the first LogicalDisplayRow object for this display
  LogicalDisplayRow *getFirstRow();

  /// @brief Get the display's number
  /// @return 0 - 255
  uint8_t getDisplayNumber();

  /// @brief Get an LogicalDisplayRow object for this display by the specified row number
  /// @param rowNumber Row number to retrieve, 0 - 255
  /// @return Pointer to an LogicalDisplayRow object, or nullptr if not exists
  LogicalDisplayRow *getRowByNumber(uint8_t rowNumber);

  /// @brief Update text and ticker for the specified row number, will add if it doesn't exist
  /// @param rowNumber Row number to display text on, 0 - 255
  /// @param rowText Char array of text for the row
  void updateRow(uint8_t rowNumber, char *rowText);

  /// @brief Scroll up one row vertically
  void scrollUp();

  /// @brief Scroll down one row vertically
  void scrollDown();

  /// @brief Call this method as often as possible to support timed vertical scrolling
  /// @param scrollDelay Time in milliseconds between vertical scrolling updates
  void autoScroll(unsigned long scrollDelay);

  /// @brief Check if this display needs to be redrawn
  /// @return True|False
  bool needsRedraw();

  /// @brief Set the needsRedraw flag
  /// @param redraw true|false
  void setRedraw(bool redraw);

  /// @brief Get the default text colour for this display
  /// @return 16 bit colour code
  uint16_t getDefaultTextColour();

  /// @brief Get the default background colour for this display
  /// @return 16 bit colour code
  uint16_t getDefaultBackgroundColour();

  /// @brief Get the maximum number of characters that will fit on a row
  /// @return 0 - 255
  uint8_t getMaxRowLength();

private:
  LogicalDisplay *_next;            // Pointer to the next display in the list
  uint8_t _displayNumber;           // ID of this display
  LogicalDisplayRow *_firstRow;     // Pointer to the first LogicalDisplayRow instances in the linked list
  uint8_t _highestRowNumber;        // Highest row number from the associated linked list instances
  uint8_t _maxRowLength;            // Number of characters that will fit on the physical screen
  uint8_t _maxRowNumber;            // Max number of rows that will fit on the physical screen
  uint8_t _numberOfRows;            // Calculated number of rows in the linked list
  uint8_t _scrollPosition;          // Row number that is at the top of the display to support scrolling
  unsigned long _lastScrollTime;    // Last time in ms a scroll function was performed
  bool _needsRedraw;                // Flag if this display needs to be redrawn
  uint8_t _fontHeight;              // Height of the font for this display
  uint8_t _fontWidth;               // Width of the font for this display
  uint8_t _defaultTextColour;       // Default colour for text for this display
  uint8_t _defaultBackgroundColour; // Default background colour for this display

  /// @brief Private method to add a row
  /// @param rowNumber 0 - 255
  /// @param rowText Pointer to the char array containing the text for this row
  /// @return Pointer to the created LogicalDisplayRow instance
  LogicalDisplayRow *_addRow(uint8_t rowNumber, char *rowText);

  /// @brief Delete the specified row number
  /// @param row Pointer to the LogicalDisplayRow instance to delete
  void _deleteRow(LogicalDisplayRow *row);
};

#endif
