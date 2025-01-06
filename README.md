# EX-Display

A project for multiple displays connected to EX-CommandStation.

The aim is to extend the current JMRI type virtual screen functionality to be displayed on additional microcontrollers with attached screens by using the `SCREEN(screen, row, "Message")` EXRAIL command.

There will be support for displaying output for multiple logical screens on one single physical display in addition to supporting multiple physical displays.

## Terminology - Display vs. Screen

In the context of this project, the term "display" is used when referring to a physical display connected to a microcontroller to display information.

The term "screen" refers to a logical representation of what EX-CommandStation is expecting to display via the EXRAIL ``SCREEN(...)`` command.

A logical "screen" is associated with a physical "display", with EX-Display controlling that association and ensuring EXRAIL ``SCREEN(...)`` commands are displayed on the correct physical display.

## Supported Display Types

EX-Display is written in a way to allow implementation of any physical display and its associated display library by using interface classes to abstract the logic away from the required library details.

<!-- ### Device limitations

In its current form, it is only possible to configure one physical screen due to the way the config.h file has been implemented, however the classes have been written to facilitate multiple physical screens, and multiple input methods in future.

**However** there are conflicts between the MCUFRIEND_kbv and TFT_eSPI libraries that mean when we do support multiple physical screens, we will not be able to have a mix of MCUFRIEND_kbv and TFT_eSPI types. -->

## Configuration

Copy "config.example.h" to "config.h" and set the desired parameters.

The key parameters to set depend on the physical screen type in use and are commented in the example config file.

## Features and Usage

As features are added they will be outlined here, with examples on how to use them.

## Basic EXRAIL commands

The basic EXRAIL command format is `SCREEN(screen, row, "Message")`.

This example displays the text "This is row 0" on the first row of the first screen:

`SCREEN(0, 0, "This is row 0")`

## Formatting rows

It is possible to perform limited formatting of rows using the below methods.

Formatting is done once per row, and the formatting codes must be at the beginning of the text. The formatting codes are removed from the text and will not be displayed.

### Setting Colours

It is possible to set the text/foreground and background colours to any valid hex colour code when setting the colours using the "Message" field of the command.

This is done by using the format `<@ screen row "#0x<textColour>#0x<backgroundColour>#Message">`. Note that the hex values must be in the format "0xdddd", where "d" represents a four digit colour code.

If you wish to set colours for a row as well as setting another formatting option, then set the row colour first, followed by a second row that sets the text and required formatting.

This example displays the text "Yellow" on the first row of the first screen with yellow coloured text on a black background:

`SCREEN(0, 0, "#0xFFE0#0x0000#Yellow")`

If you wish to have a coloured line that is also underlined, do it like this:

``` cpp
SCREEN(0, 0, "#0xFFE0#0x0000#")
SCREEN(0, 0, "__This is now yellow and underlined")
```

### Horizontal Line

Note that setting a horizontal line will remove any text previously set for that particular row. To replace a line, simply update it without the line formatting with text, or delete it.

`SCREEN(0, 0, "--")`

### Underlined Text

`SCREEN(0, 0, "__This is underlined")`

### Always Ticker This Row

*Not implemented yet*

`SCREEN(0, 0, "~~This will always ticker")`

### Never Ticker This Row

*Not implemented yet*

`SCREEN(0, 0, "!~This will never ticker")`

### Delete Row

Simply set the row message to zero length to delete it, noting that this doesn't just blank the text out, but deletes the row in its entirety, including all formatting attributes.

`SCREEN(0, 1, "")`

## Serial Connections

- MEGA: GND-GND and RX pin 19 on mega to serial tx pin on EX-CS
- UNO: GND-GND and RX pin 0 (used testprobes to access both pins under display shield, needs a better physical solution) 
