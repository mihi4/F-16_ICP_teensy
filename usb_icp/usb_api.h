#ifndef USBserial_h_
#define USBserial_h_

#include <inttypes.h>

#include "keylayouts.h"
#include "Print.h"
#include "Stream.h"

extern uint8_t gamepad_report_data[10];

class usb_gamepad_class
{
	public:
	usb_gamepad_class() { manual_mode = 0; }
	inline void button(uint8_t button, bool val) {
		button--;
		uint8_t mask = (1 << (button & 7)); // create button mask
		if (val)
		{
			// set bit with logical or
			if (button < 8) gamepad_report_data[0] |= mask; // buttons 0 to 7
			else if (button < 16) gamepad_report_data[1] |= mask; // buttons 8 - 15
			else if (button < 24) gamepad_report_data[2] |= mask; // buttons 16 - 23
			else if (button < 32) gamepad_report_data[3] |= mask; // buttons 24 - 31
			else if (button < 40) gamepad_report_data[4] |= mask; // buttons 32 - 38
		}
		else
		{
			// reset bit with  logical and
			mask = ~mask; // invert button mask
			if (button < 8) gamepad_report_data[0] &= mask; // buttons 0 to 7
			else if (button < 16) gamepad_report_data[1] &= mask; // buttons 8 to 15
			else if (button < 24) gamepad_report_data[2] &= mask; // buttons 16 to 23
			else if (button < 32) gamepad_report_data[3] &= mask; // buttons 24 to 31
			else if (button < 40) gamepad_report_data[4] &= mask; // buttons 32 to 38			
		}
		if (!manual_mode) send_now();
	}
	inline void X(uint16_t val) {
		if (val > 1023) val = 1023;
		gamepad_report_data[5] = val; // use bottom 8 bit of x axis in byte 2
		gamepad_report_data[6] = (gamepad_report_data[6] & 0xFC) | (val >> 8); // move top 2 bits of x axis into byte 3
		if (!manual_mode) send_now();
	}
	inline void Y(uint16_t val) {
		if (val > 1023) val = 1023;
		gamepad_report_data[6] = (gamepad_report_data[6] & 0x3F) | (val << 2); // move bottom 6 bits of y axis into byte 3
		gamepad_report_data[7] = (gamepad_report_data[7] & 0xF0) | (val >> 6); // move top 4 bytes of y axis into byte 4
		if (!manual_mode) send_now();
	}
	inline void RX(uint16_t val) {
		gamepad_report_data[7] = (gamepad_report_data[7] & 0x0F) | (val << 4); // move bottom 4 buyes of rx axis into byte 4
		gamepad_report_data[8] = (gamepad_report_data[8] & 0xC0) | (val >> 4); // move top 6 bits of ry rx axis into byte 5
			if (!manual_mode) send_now();
	}
	inline void RY(uint16_t val) {
		if (val > 1023) val = 1023;
		gamepad_report_data[8] = (gamepad_report_data[8] & 0x3F ) | (val << 8); // move bottom 2 bytes of ry axis into byte 5
		gamepad_report_data[9] =   (val >> 2); // move top 8 bits of ry axis into byte 6
		if (!manual_mode) send_now();
	}

	inline void useManualSend(bool mode) {
		manual_mode = mode;
	}
	
	void send_now(void);
	
	private:
	uint8_t manual_mode;
};

extern usb_gamepad_class Gamepad;

#endif
