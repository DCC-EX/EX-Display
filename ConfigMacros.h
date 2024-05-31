#ifndef CONFIGMACROS_H
#define CONFIGMACROS_H

#define DISPLAY(id, foreground, background) ->addDisplay(id, foreground, background)

#define TFT_ESPI_SCREEN(config) new TFT_eSPIScreen() config;

#define BUTTON(b1, b2, b3, b4, b5) ->setInput(new InputMethod(b1, b2, b3, b4, b5))

#define TOUCH ->setInput(new InputMethod())

#endif
