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
 * @mainpage EX-Display - a project for extending EX-CommandStation displays and screens
 *
 * @section intro_sec Introduction
 * EX-Display enables one or more physical displays to be connected to EX-CommandStation via a serial connection to take
 * advantage of the EXRAIL SCREEN() command to display various user-generated information.
 *
 * This can also be used to remotely display the EX-CommandStation serial logs.
 *
 * @section details Details
 * This software has been written to be extensible in order to work with various different types of microcontrollers,
 * display libraries, and input devices.
 *
 * One important note is that EXRAIL SCREEN() commands are only published to the EX-CommandStation serial console, and
 * therefore you will need to connect the appropriate EX-Display device UART's Rx pin to the first EX-CommandStation
 * UART's Tx pin. These commands cannot be received on additional serial ports, nor over WiFi.
 *
 * Sensible defaults have been chosen for different platforms, for example, by default Serial2 on Espressif ESP32
 * platforms will be used for the connection to EX-CommandStation, whereas on a Nucleo F411RE, this will be Serial6.
 *
 * EX-Display looks for serial input in this format:
 * @code {.cpp}
 * <@ screen row "text">
 * @endcode
 *
 * For general user configuration options, refer to @ref myConfig.example.h, and for configuring devices, refer to @ref
 * myDevices.example.h.
 *
 * The sensible defaults for the different platforms and so forth are in @ref Defines.h, with sensible defaults for each
 * device being located in the appropriate header file, for example @ref TFT_eSPIDisplay.h.
 *
 * @section application_architecture Application Architecture
 * The application has been written in a way that all configuration of user devices and preferences, and all instance
 * instantiation is performed by what is called the Configurator, see @ref Configurator.h.
 *
 * Once all user configuration, devices, and the various instances are instantiated, the Controller takes care of
 * initialising those. It is then responsible for reading input from EX-CommandStation and the user input device, and
 * directing these to the ScreenManager or DisplayManager as appropriate, see @ref Controller.h.
 *
 * All Screen input is directed to the ScreenManager to manage the content including interpretation of the various
 * attributes affecting what the Screen is expected to look like, see @ref ScreenManager.h. Each Screen is
 * representative of the output from EX-CommandStation only, and has no involvement on what is physically displayed.
 *
 * The DisplayManager (see @ref DisplayManager.h) is responsible for creating user display instances and directing which
 * Screen a Display should be displaying, with physical displays implemented by a class deriving from the
 * DisplayInterface class (see @ref DisplayInterface.h). This enables support for various different display libraries
 * and associated devices and keeps those abstracted from the DisplayManager to prevent conflicts.
 *
 * Likewise, the InputManager (see @ref InputManager.h) is responsible for creating the user input instance, with this
 * instance using a callback to the Controller to action user input. The user input classes are derived from the
 * InputInterface class (see @ref InputInterface.h) to abstract to support various different input types without
 * conflicts.
 *
 * @subsection testing Testing
 *
 * Where possible, unit and integration tests have been written using PlatformIO and GoogleTest to validate that the
 * various methods and classes continue to do what they're supposed to do, and also to prevent causing memory leaks and
 * calls to undefined objects and so forth.
 *
 * The various display and input device libraries typically are not compatible with the native environment the
 * PlatformIO tests run in, so there are no tests written for the implemented display and input classes, but these are
 * mocked instead. See @ref MockDisplay, @ref MockSPIDisplay, @ref MockInput, and @ref MockButtonInput for examples of
 * these. Also note the mention of needing include guards for this as per @ref adding_types.
 *
 * All tests are run when pushing or merging to both the main and devel branches, and can be run locally with PlatformIO
 * also using the following commands. The verbose output is recommended to review the test output.
 *
 * @code
 * pio test -e native_test -v
 * pio test -e native_test_windows -v
 * @endcode
 *
 * Note that due to issues with the sanitizers that check from memory leaks and undefined references not being available
 * on Windows, you must use the second option for local testing, and there is no way to validate that memory leaks have
 * been introduce, or undefined references are being called. It is best to run these tests on Linux, and on Windows this
 * can be accomplished by using Windows Subsystem for Linux.
 *
 * The best approach when adding new functionality is to write the test first, and then ensure the code to support the
 * feature makes the test succeed.
 *
 * When writing and running tests, cleaning up between test runs is often required, and is recommended to be done prior
 * to pushing to the main or devel branches just to ensure all is good. This can be done with this command:
 *
 * @code
 * pio run -t clean -e native_test
 * pio run -t clean -e native_test_windows
 * @endcode
 *
 * @section adding_types Adding Display and Input Types
 * As mentioned in the @ref application_architecture, both displays and inputs are derived from the appropriate
 * interface class to enable multiple different types to be made available for users to configure and use.
 *
 * When adding either display or input classes, be sure to add include guards around the derived class to prevent
 * causing errors when running PlatformIO tests, as these are typically not compatible with the native environment that
 * the tests run in.
 *
 * @code {.cpp}
 * #ifndef NEWDISPLAYTYPE_H
 * #define NEWDISPLAYTYPE_H
 *
 * #ifndef PIO_UNIT_TESTING // Do not compile when testing, likely to cause test failures
 *
 * class MyNewDisplay : public DisplayInterface {
 * ...
 * };
 *
 * #endif // PIO_UNIT_TESTING
 *
 * #endif // NEWDISPLAYTYPE_H
 * @endcode
 *
 * Further to this, all display and input classes must define one or more public static methods to call the constructor
 * to enable the device creation to be added to either the DisplayManager or InputManager creation methods during
 * compilation. If there are overloaded constructors, each must be matched by an equivalent static create method. Refer
 * to @ref TFT_eSPIDisplay.h for an example of this. This create method must return a pointer to the new instance to
 * support this.
 *
 * @code {.cpp}
 * class MyNewDisplay : public DisplayInterface {
 * public:
 * MyNewDisplay(uint16_t textColour, uint16_t backgroundColour) {...}
 *
 * MyNewDisplay(uint16_t textColour, uint16_t backgroundColour, int param) {...}
 *
 * static MyNewDisplay *create(uint16_t textColour, uint16_t backgroundColour) {...}
 *
 * static MyNewDisplay *create(uint16_t textColour, uint16_t backgroundColour, int param) {...}
 * };
 * @endcode
 *
 * @subsection adding_displays Adding Displays
 *
 * The purpose of the display classes is to implement the DisplayInterface using display libraries to work with user
 * display devices, with the first of these being TFT_eSPIDisplay to implement using the TFT_eSPI library.
 *
 * Each additional display class must implement all virtual methods of the DisplayInterface class, and is responsible
 * for all visual display of the Screen instance that is to be displayed.
 *
 * As mentioned in the above section, be sure to add static create methods to allow these to be defined in the user's
 * myDevices.h file.
 *
 * Further to this, any font or colour definitions related to the specific display class or library must be defined in
 * that device's header file only, do not add these to Defines.h to ensure there are no possible conflicts with other
 * display classes or libraries.
 *
 * @subsection adding_inputs Adding Inputs
 *
 * Similar to the display classes, the input classes are also to implement the InputInterface class to work with various
 * user input methods. The first of these is the TFT_eSPITouch class to implement touch screen support with the TFT_eSPI
 * library.
 *
 * In this instance, this input method must share the same TFT_eSPI instance as the display, and the InputInterface has
 * the _needsDisplay parameter available to allow specifying the display instance to retrieve the TFT_eSPI
 * instance from. The method public getTFT_eSPInstance() has been added to allow the TFT_eSPIInput class to retrieve
 * this instance within the begin() method. See @ref TFT_eSPITouch to see how this is implemented.
 *
 * Each input class must implement the virtual methods of the InputInterface class, and the check() method will callback
 * to the Controller class to provide the appropriate InputAction type that the user has selected.
 */

#ifndef PIO_UNIT_TESTING

#include "Configurator.h"

/// @brief Create the Configurator instance to configure EX-Display
/// @param console Pointer to the console stream - defaults to Serial, customise in myConfig.h
/// @param commandStation Pointer to the CommandStation connection stream - default depends on platform, customise in
/// myConfig.h
/// @param logLevel Sets the log level for the application - defaults to WARN, customise in myConfig.h
Configurator *configurator = new Configurator(&CONSOLE_STREAM, &COMMANDSTATION_STREAM, LOG_LEVEL);

/// @brief Main setup method, initialise Configurator here
void setup() {
  CONSOLE_STREAM.begin(115200);
  COMMANDSTATION_STREAM.begin(115200);
  configurator->initialise();
  Controller *controller = configurator->getController();
  controller->begin();
}

/// @brief Main loop, simply calls controller->update() to manage all interactions
void loop() {
  Controller *controller = configurator->getController();
  controller->update();
}

#endif // PIO_UNIT_TEST
