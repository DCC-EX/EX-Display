# EX-Display

A project for multiple displays connected to EX-CommandStation.

The aim is to extend the current JMRI type virtual screen functionality to be displayed on additional microcontrollers with attached screens by using the `SCREEN(screen, row, "Message")` EXRAIL command.

## Terminology - Display vs. Screen

In the context of this project, the term "screen" is used when referring to a physical screen connected to a microcontroller to display information. This aligns with the use of the `SCREEN()` EXRAIL command, as it is designed to display information on a screen.

The term "display" refers to a logical representation of a physical screen, enabling one physical screen to be used to dislay information from one or more EXRAIL defined screens.

## Serial Connections

- MEGA: GND-GND and RX pin 19 on mega to serial tx pin on EX-CS
- UNO: GND-GND and RX pin 0 (used testprobes to access both pins under display shield, needs a better physical solution) 
