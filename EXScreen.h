#ifndef EXSCREEN_H
#define EXSCREEN_H

#include <Arduino.h>

class EXScreen {
public:
  /// @brief Constructor for a new EXScreen object
  /// @param screenId The ID for this screen, should match the SCREEN() call
  /// @param rows Number of rows valid for this screen
  /// @param columns Number of columns valid for this screen
  EXScreen(uint8_t screenId, uint8_t rows, uint8_t columns);

  /// @brief Get this screen's ID
  /// @return 
  uint8_t getId();

  /// @brief Get the row count for this screen
  /// @return 0 - 255
  uint8_t getRows();

  /// @brief Get the column count for this screen
  /// @return 0 - 255
  uint8_t getColumns();

  /// @brief Virtual function to override to write a row of text to the physical screen
  virtual void writeRow(uint8_t row, uint8_t column, char *message);

  /// @brief Get the first screen object
  /// @return Pointer to the first screen object in the list
  static EXScreen *getFirst();

  /// @brief Get the next screen object
  /// @return Pointer to the next screen object in the list
  EXScreen *getNext();

private:
  // Chaining screens
  static EXScreen *_first;
  EXScreen *_next;
  // Screen attributes
  uint8_t _id;
  uint8_t _rows;
  uint8_t _columns;

};

#endif
