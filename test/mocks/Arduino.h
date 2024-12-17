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

#ifndef ARDUINO_H
#define ARDUINO_H

/// @brief Mock Arduino.h to define required types and methods to satisfy dependencies
#include "Stream.h"
#include <cstdarg>
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

// Mock Arduino functions
inline void pinMode(int pin, int mode) {}
inline void digitalWrite(int pin, int value) {}
inline int digitalRead(int pin) { return 0; }
inline void delay(unsigned long ms) {}
inline unsigned long millis() { return 0; }
inline void analogWrite(int pin, int value) {}
inline int analogRead(int pin) { return 0; }

#endif // ARDUINO_H
