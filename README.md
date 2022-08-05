# F-16_ICP_teensy
## Using a Teensy++ 2.0 to simulate the inputs of an F-16 ICP

![F-16 ICP](https://www.xflight.de/original/parts/center_console/icp/icp_01.gif)  
Image (c) Martin Schmitt, https://xflight.de

This firmware is used to connect all possible buttons, switches and potentiometers of a DIY F-16 ICP to the computer and get detected by Windows as a Joystick.

The Teensy will show up in Windows' game controller settings as "F-16 ICP" with 38 Buttons and 4 analogue axes.

These inputs can be mapped to the corresponding commands in Falcon BMS or DCS World.

It's configured to send a corresponding buttonpress for all pushbuttons (including WARN RESET POSITION) but also for the toggleswitch positions.  
Each of the 2-position switches (SYM ON-OFF, BRT ON-OFF, DRIFT C/O-NORM) sends a short button press/release sequence when activated and one of another button when released.  
The 3-position GAIN switch will send 3 different button press/release actions for each position.

Pins 0-27 are used for all pushbuttons (including WARN RESET), pins 28-32 for each of the active switch positions and pins 42-45 (analog pins 4-7) for the potentiometers.

The directory "f16_icp" holds the .ino file for the ArduinoIDE.

!(myICP)[pics/myIcp.jpg]
