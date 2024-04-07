/*
 *  © 2024, Matt Bidwell, Paul Antoine, Colin Murdoch, Chris Harlow
 *  All rights reserved.
 *
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
 *  along with CommandStation.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "MCUFRIEND_kbv.h"
#include "Adafruit_GFX.h"

MCUFRIEND_kbv tft;

#if defined(ARDUINO_AVR_MEGA2560)
  #define RX_PIN 19 // Define the RX pin for Serial1
  #elif defined(ARDUINO_AVR_UNO)
  #define RX_PIN 0
  #define Serial1 Serial
  #endif



#define DISPLAY_WIDTH 320
#define DISPLAY_HEIGHT 240

#define FONT_SIZE 2.5 // Adjust font size as needed
#define CHAR_WIDTH (6 * FONT_SIZE) // Width of a single character in pixels

int16_t currentXPos = 0; // Track the current x-position for printing text
int16_t currentYPos = 0; // Track the current y-position for printing text

void setup() {
  Serial.begin(115200); // Start the serial communication
  Serial1.begin(115200); // Start Serial1 for listening to messages

  tft.begin(); // Initialize the display
  tft.setRotation(3); // Set rotation if needed

  tft.fillScreen(0); // Fill the screen with black color
  tft.setTextSize(FONT_SIZE);
  tft.setTextColor(0xFFFF); // White color
}

void loop() {
  if (Serial1.available()) { // Check if data is available on Serial1
    String message = Serial1.readStringUntil('\n'); // Read the incoming message
    message.trim(); // Remove leading and trailing whitespaces
    displayMessage(message); // Display the message
    currentYPos += FONT_SIZE * 8; // Move to the next line for the next message
    currentXPos = 0; // Reset X position for the new line
  }
}

void displayMessage(String message) {
  // Iterate through each character in the message
  for (size_t i = 0; i < message.length(); i++) {
    char character = message.charAt(i); // Get the current character

    // Check if adding the character will exceed the display width
    if (currentXPos + CHAR_WIDTH > DISPLAY_WIDTH) {
      // Move to the next line
      currentXPos = 0;
      currentYPos += FONT_SIZE * 8; // Move down by one font height

      // Check if adding the character will exceed the display height
      if (currentYPos + FONT_SIZE * 8 > DISPLAY_HEIGHT) {
        // Clear the screen if all lines are used
        tft.fillScreen(0);
        currentXPos = 0;
        currentYPos = 0;
      }
    }

    // Handle newline character
    if (character == '\n') {
      // Move to the next line
      currentXPos = 0;
      currentYPos += FONT_SIZE * 8; // Move down by one font height
    } else {
      // Print the character at the current position
      tft.setCursor(currentXPos, currentYPos);
      tft.write(character);

      // Update x-position for the next character
      currentXPos += CHAR_WIDTH;
    }
  }
}
