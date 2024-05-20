#include "Defines.h"
#ifdef NEEDS_MCU

#include <MCUFriendTouch.h>

MCUFriendTouch::MCUFriendTouch(TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300))

void MCUFriendTouch::setupTouch(){

  // Define the operating buttons
  Adafruit_GFX_Button key[5];

  _tft = MCUFriendScreen::returnTFT();
  _screenHeight = MCUFriendScreen::return::returnHeight();
  _screenWidth = MCUFriendScreen::return::returnWidth();
  _buttonPressed = 0;

}

void MCUFriendTouch::drawButtons(byte option, uint16_t fontColour, uint16_t backgroundColour) {

  switch (option) {

    case 2:
      // add code here for paramater screen buttons
      break;
    
    default:

      //Serial.println("Defining Buttons");
      key[0].initButton(_tft,  _screenWidth/8, _screenHeight/2, _screenWidth/4, _screenHeight, WHITE, GREEN, WHITE, "Left", 1);   
      key[1].initButton(_tft,  (_screenWidth/8)*7, _screenHeight/2, _screenWidth/4, _screenHeight, WHITE, RED, WHITE, "Right", 1);   
      key[1].initButton(_tft,  _screenWidth/2, (_screenHeight/4)-10, _screenWidth/2, (_screenHeight/2)-20, WHITE, CYAN, BLACK, "Top", 1);   
      key[3].initButton(_tft,  _screenWidth/2, ((_screenHeight/4)*3)+10, _screenWidth/2, ((_screenHeight/2)+20), WHITE, CYAN, BLACK, "Bottom", 1);    
      key[4].initButton(_tft,  _screenWidth/2, _screenHeight/2, _screenWidth/2, 40, WHITE, CYAN, BLACK, "Centre", 1);   
          
          // draw buttons - not needed for this application but included just for testing
          for (byte x = 0; x < 5; x++) {
            key[x].drawButton(false);
            delay(10);    // Seem to need a slight pause
          }
    break;
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
