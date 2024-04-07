# EX-Display

A project for multiple displays connected to EX-CommandStation via I2C

Raw proof of concept - developed on Mega2560 + mcufriend display shield, and using mcufriend_kbv library.  Tests OK on Uno, although first half-char of each line is offscreen, TBD.

Connection:
-  MEGA: GND-GND and RX pin 19 on mega to serial tx pin on EX-CS
-  UNO: GND-GND and RX pin 0 (used testprobes to access both pins under display shield, needs a better physical solution) 

Zero apologies for raw first effort here
