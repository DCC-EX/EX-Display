#ifndef AtFinder_h
#define AtFinder_h
#include <Arduino.h>
typedef void (*DISPLAY_CALLBACK)(uint8_t screenId, uint8_t row, char *text);

class AtFinder {
public:
  static void setup(uint8_t _maxTextLength, DISPLAY_CALLBACK _callback);
  static void processInputChar(char hot);

private:
  static DISPLAY_CALLBACK callback;
  static uint8_t maxTextLength;
  static char *text;
};
#endif