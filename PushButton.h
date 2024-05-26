#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

#include "Defines.h"

#if defined(USE_BUTTONS)
#include "InputMethod.h"
#include <Arduino.h>

class PushButton : public InputMethod {
public:
  PushButton(uint8_t leftPin, uint8_t rightPin, uint8_t centrePin, uint8_t upPin, uint8_t downPin);

  void begin() override;

private:
  bool _readRawInput(ButtonName button) override;
  
};

#endif // USE_BUTTONS

#endif
