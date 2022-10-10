# Installation

* If not done already, install [Teensyduino](https://www.pjrc.com/teensy/teensyduino.html)
* Copy the folder "usb_icp" to */hardware/teensy/avr/cores* in the Arduino installation directory (on Windows, that's mostly *C:\Program Files (x86)\Arduino*)
* Copy *boards.txt* to */hardware/teensy/avr/cores* or add the following lines to the boards.txt for the Teensy++ 2.0 section, after the last occurence of "teensypp2.menu.usb":
  >teensypp2.menu.usb.icp=F-16 ICP  
  >teensypp2.menu.usb.icp.build.usbtype=USB_ICP  
  >teensypp2.menu.usb.icp.upload_port.usbtype=USB_ICP  
  >teensypp2.menu.usb.icp.fake_serial=teensy_gateway
* Copy the files of the folder *teensy* to */hardware/teensy/avr/cores/teensy* in the Arduino installation directory or add the according lines to the same files in the directory right before the "#endif", like
  >#elif defined(USB_ICP)  
  >#include "../usb_icp/usb_private.h"  
  
  The last part - here "usb_private.h" - should always correspond with the edited file itself.
* Write the program to the Teensy using the ArduinoIDE (Check, if your version is supported by Teensyduino)
