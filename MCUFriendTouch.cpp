#include "Defines.h"
#ifdef NEEDS_MCU

#include <MCUFriendTouch.h>

MCUFriendTouch::MCUFriendTouch(TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300))

void MCUFriendTouch::setupTouch(){

  // Define the operating buttons
  //Adafruit_GFX_Button btn1, btn2, btn3, btn4, btn5, btn6;
  Adafruit_GFX_Button key[6];

  _buttonPressed = 0;

}

void MCUFriendTouch::drawButtons(uint16_t fontColour, uint16_t backgroundColour) {

    //Serial.println("Defining Buttons");
    key[0].initButton(&tft,  40, 220, 70, 40, WHITE, GREEN, WHITE, "Start", 2);   
    key[1].initButton(&tft,  120, 220, 70, 40, WHITE, RED, WHITE, "Save", 2);   
    key[2].initButton(&tft,  200, 220, 70, 40, WHITE, CYAN, BLACK, "Reset", 2);   
    key[3].initButton(&tft,  40, 270, 70, 40, WHITE, CYAN, BLACK, "T+", 2);    
    key[4].initButton(&tft,  120, 270, 70, 40, WHITE, CYAN, BLACK, "T-", 2);   
    key[5].initButton(&tft,  200, 270, 70, 40, WHITE, CYAN, BLACK, "Rate", 2); 
    
    // draw buttons - not needed for this application
    for (byte x = 0; x < 6; x++) {
      key[x].drawButton(false);
      delay(10);    // Seem to need a slight pause
    }
}

bool MCUFriendTouch::touchGetXY() {

    TSPoint p = ts.getPoint();
    pinMode(YP, OUTPUT);      //restore shared pins
    pinMode(XM, OUTPUT);
    digitalWrite(YP, HIGH);   //because TFT control pins
    digitalWrite(XM, HIGH);
    bool pressed = (p.z > MINPRESSURE && p.z < MAXPRESSURE);
    if (pressed) {
        pixel_x = map(p.x, TS_LEFT, TS_RT, 0, tft.width()); //.kbv makes sense to me
        pixel_y = map(p.y, TS_TOP, TS_BOT, 0, tft.height());
    }
    return pressed; 
}

void MCUFriendTouch::checkButtons() {

    bool down = Touch_getXY();

    for (uint8_t b = 0; b < 6; b++){
      key[b].press(down && key[b].contains(pixel_x, pixel_y));
      if (key[b].justReleased())
          key[b].drawButton();
      if (key[b].justPressed()) {
          key[b].drawButton(true);
          ButtonPressed = b + 1;
          delay(debounceDelay);
      }
    }

}

#endif
