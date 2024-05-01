#ifndef EXSCREEN_H
#define EXSCREEN_H

#include <Arduino.h>

class EXScreen {
public:
  /// @brief Constructor for a new EXScreen object
  EXScreen() {}

  /// @brief Virtual function to override to write a row of text to the physical screen
  virtual void writeRow(uint8_t row, uint8_t column, char *message);

};

#endif
