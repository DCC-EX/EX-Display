#ifndef AtFinder_h
#define AtFinder_h
#include <Arduino.h>
typedef void (*DISPLAY_CALLBACK)(uint8_t screenId, uint8_t row, char *text);

class AtFinder {
public:
  /// @brief Setup the AtFinder parser
  /// @param _maxTextLength Maximum length of text the parser will accept
  /// @param _callback Parser will call this function and provide display ID, row number, and a char array of text
  static void setup(uint8_t _maxTextLength, DISPLAY_CALLBACK _callback);

  /// @brief Call this as often as possible with a streaming input (eg. Serial.read())
  /// @param hot The next character to process in the stream
  static void processInputChar(char hot);

private:
  static DISPLAY_CALLBACK callback;
  static uint8_t maxTextLength;
  static char *text;
};
#endif