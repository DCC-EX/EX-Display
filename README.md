# EX-Display

A project for multiple displays connected to EX-CommandStation.

The aim is to extend the current JMRI type virtual screen functionality to be displayed on additional microcontrollers with attached screens by using the `SCREEN(screen, row, "Message")` EXRAIL command.

## Terminology - Display vs. Screen

In the context of this project, the term "screen" is used when referring to a physical screen connected to a microcontroller to display information. This aligns with the use of the `SCREEN()` EXRAIL command, as it is designed to display information on a screen.

The term "display" refers to a logical representation of a physical screen, enabling one physical screen to be used to dislay information from one or more EXRAIL defined screens.

## Configuration

Copy "config.example.h" to "config.h".

The key parameters to set are...

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

```
SCREEN(0, 0, "#0xFFE0#0x0000#")
SCREEN(0, 0, "__This is now yellow and underlined")

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

*Not implemented yet*

Simply set the row message to zero length to delete it, noting that this doesn't just blank the text out, but deletes the row in its entirety, including all formatting attributes.

`SCREEN(0, 1, "")`

## Serial Connections

- MEGA: GND-GND and RX pin 19 on mega to serial tx pin on EX-CS
- UNO: GND-GND and RX pin 0 (used testprobes to access both pins under display shield, needs a better physical solution) 
