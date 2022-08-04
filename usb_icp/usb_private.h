#ifndef usb_serial_h__
#define usb_serial_h__

#include <stdint.h>

#ifdef __cplusplus
extern "C"{
#endif

/**************************************************************************
 *
 *  Configurable Options
 *
 **************************************************************************/

#define VENDOR_ID               0x1209  /* 0x16C0  orig teensy */
#define PRODUCT_ID              0xF16B  /* 0x0482  */
#define TRANSMIT_FLUSH_TIMEOUT  4   /* in milliseconds */
#define TRANSMIT_TIMEOUT        25   /* in milliseconds */

/**************************************************************************
 *
 *  Endpoint Buffer Configuration
 *
 **************************************************************************/

// Some operating systems, especially Windows, may cache USB device
// info.  Changes to the device name may not update on the same
// computer unless the vendor or product ID numbers change, or the
// "bcdDevice" revision code is increased.

#define STR_PRODUCT             L"F-16 ICP"
#define ENDPOINT0_SIZE          64

#define GAMEPAD_INTERFACE	0
#define GAMEPAD_ENDPOINT	1
#define GAMEPAD_SIZE		16 // 8
#define GAMEPAD_BUFFER		EP_DOUBLE_BUFFER
#define GAMEPAD_INTERVAL	1

#define NUM_ENDPOINTS		2
#define NUM_INTERFACE		1

// setup
void usb_init(void);			// initialize everything
void usb_shutdown(void);		// shut off USB

// variables
extern volatile uint8_t usb_configuration;
extern volatile uint8_t usb_suspended;
// this holds the actual usb data sent from the controller to the pc
extern uint8_t gamepad_report_data[10];

#ifdef __cplusplus
} // extern "C"
#endif
#endif
