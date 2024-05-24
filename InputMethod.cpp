#include "Defines.h"
#include "InputMethod.h"

InputMethod *InputMethod::_first = nullptr;

InputMethod::InputMethod() { _next = nullptr; }

void InputMethod::setScreen(PhysicalScreen *screen) {
  _screen = screen;
  CONSOLE.print(F("Added screen "));
  CONSOLE.println(_screen->getScreenNumber());
}
