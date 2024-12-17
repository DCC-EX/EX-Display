#include "Defines.h"

#if defined(NEEDS_TFT) && defined(USE_TOUCH)

#include "TFT_eSPITouch.h"

#ifdef USE_SPIFFS
const char _calibrationFileBase[] = "/calibrationData";
#endif

TFT_eSPITouch::TFT_eSPITouch(TFT_eSPI &tft) : InputMethod(), _tft(tft) {
#ifdef USE_SPIFFS
  sprintf(_calibrationFile, "%s%d", _calibrationFileBase, _inputNumber);
#endif
}

void TFT_eSPITouch::begin() {
  if (!_screen) {
    return;
  }
#ifdef USE_SPIFFS
  if (!SPIFFS.begin()) {
    CONSOLE.println(F("Formatting file system"));
    SPIFFS.format();
    SPIFFS.begin();
  }
#endif
  if (!_setCalibration()) {
    CONSOLE.println(F("Calibration data not valid"));
    if (!_doCalibration()) {
      _screen->clearScreen(TFT_BLACK);
      _screen->writeRow(0, 0, TFT_WHITE, TFT_RED, _screen->getMaxRowLength(), "ERROR", true);
      _screen->writeRow(1, 0, TFT_WHITE, TFT_BLACK, _screen->getMaxRowLength(), "Could not save calibration data",
                        false);
      CONSOLE.println(F("ERROR: Could not save calibration data"));
      delay(3000);
      _screen->clearScreen(TFT_BLACK);
    } else {
      _screen->clearScreen(TFT_BLACK);
    }
  } else {
    CONSOLE.println(F("Calibration data valid"));
    _screen->clearScreen(TFT_BLACK);
  }
  _calculateButtons();
}

bool TFT_eSPITouch::_setCalibration() {
#ifdef FORCE_CALIBRATION
  return false;
#endif
  uint16_t calibrationData[5];
#ifdef USE_SPIFFS
  File f = SPIFFS.open(_calibrationFile, "r");
  if (!f)
    return false;
  bool dataValid = false;
  if ((f.readBytes((char *)calibrationData, 14)) == 14) {
    dataValid = true;
    f.close();
  }
  if (!dataValid)
    return false;
#elif USE_EEPROM
  return false;
#elif USE_FLASH
  return false;
#endif
  _tft.setTouch(calibrationData);
  return true;
}

bool TFT_eSPITouch::_doCalibration() {
  uint16_t calibrationData[5];
  _tft.calibrateTouch(calibrationData, TFT_WHITE, TFT_RED, 15);
  File f = SPIFFS.open(_calibrationFile, "w");
  if (f) {
    f.write((const unsigned char *)calibrationData, 14);
    f.close();
    return true;
  }
  return false;
}

bool TFT_eSPITouch::_readRawInput(ButtonName button) {
  uint16_t touchX, touchY;
  if (_tft.getTouch(&touchX, &touchY)) {
    if (touchX >= _buttons[button].xStart && touchX <= _buttons[button].xEnd && touchY >= _buttons[button].yStart &&
        touchY <= _buttons[button].yEnd) {
      return true;
    }
  }
  return false;
}

#endif
