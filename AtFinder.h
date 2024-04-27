#ifndef AtFinder_h
#define AtFinder_h
#include <Arduino.h>
typedef void (*DISPLAY_CALLBACK)(int16_t screenId, int16_t row, char* text);

class AtFinder {
    public:
     static void setup(int16_t _maxTextLength, DISPLAY_CALLBACK _callback);
     static void processInputChar(char hot);
    private:
       static DISPLAY_CALLBACK callback;
       static int16_t maxTextLength;
       static char *  text;
};
#endif