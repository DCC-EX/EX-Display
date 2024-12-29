/*
 *  © 2024 Peter Cole
 *
 *  This is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  It is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this code.  If not, see <https://www.gnu.org/licenses/>.
 */

/**
 * @brief Mock Arduino.h to ensure source files requiring this still function
 */

#ifndef ARDUINO_H
#define ARDUINO_H

#include "Stream.h"
#include <cstdarg>
#include <gmock/gmock.h>
#include <stdint.h>

// Define states
#define HIGH 0x1
#define LOW 0x0

// Define pin modes
#define INPUT 0x0
#define OUTPUT 0x1
#define INPUT_PULLUP 0x2

// Define common Arduino types
typedef uint8_t byte;

// Declare millis so it can be mocked/returned
static unsigned long _currentMillis = 0;

// Define a mock class to enable EXPECT_CALL tests against these
class MockArduino {
public:
  MOCK_METHOD(void, mockPinMode, (int pin, int mode), ());
  MOCK_METHOD(void, mockDigitalWrite, (int pin, int value), ());

  // Set up a singleton instance for this class to work with gmock
  static MockArduino &getInstance() {
    static MockArduino instance;
    return instance;
  }
};

// Mock Arduino functions
inline void pinMode(int pin, int mode) { MockArduino::getInstance().mockPinMode(pin, mode); }
inline void digitalWrite(int pin, int value) { MockArduino::getInstance().mockDigitalWrite(pin, value); }
inline int digitalRead(int pin) { return 0; }
inline void delay(unsigned long ms) {}
inline unsigned long millis() { return _currentMillis; }
inline void analogWrite(int pin, int value) {}
inline int analogRead(int pin) { return 0; }

inline void advanceMillis(unsigned long ms) { _currentMillis += ms; }

#endif // ARDUINO_H
