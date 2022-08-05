// #def ROTBUTTONDELAY 5   // possible delay in milliseconds between press/release commands of joystick buttons

const int numJoybuttons = 38; // due to switches, there are more joystickbuttons than inputs
const int numPushbuttons = 28;  // pushbuttons are on pins 0-27, ignoring pin 6 for led
const int lastButtonPin = 38; // Regular analogue 0 input, used for last button

const int numSwitches = 3;
const int switchPins[numSwitches] = { 28, 29, 30 };  // pins for the 2 on/off switches, SYM, BRT and DRIFT C/O
const int  switchJoypos = 29; // number of first joystick button connected to a switch, alwas 2 are used for on/off;

const int threePosPins[2] = { 31, 32 }; // pins for the 1 on/off/on GAIN switch

const int analogPins[4] = { 4, 5, 6, 7}; // pins 42,43, 44 and 45 for the potentiometers = analog "pins" 4,5,6,7


//bool switchStates[numSwitches] = { 0, 0, 0 };
bool switchStatesOld[numSwitches] = { 0, 0, 0 };
//bool threePosState[2] = { 0, 0 };
bool threePosStateOld[2] = { 0, 0 };

void setup() {
  
  // configure the joystick to manual send mode.  This gives precise
  // control over when the computer receives updates, but it does
  // require you to manually call Gamepad.send_now().
  //Gamepad.useManualSend(true);
  
  for (int i=0; i<numPushbuttons; i++) {
	pinMode(i, INPUT_PULLUP);
	Gamepad.button(i, 0);	
  }
  for (int i=0; i<numSwitches; i++) {
	pinMode(switchPins[i], INPUT_PULLUP);
  }
  for (int i=0; i<2; i++) {
	pinMode(threePosPins[i], INPUT_PULLUP);
  }
  Gamepad.X(0);
  Gamepad.Y(0);
  Gamepad.RX(0);
  Gamepad.RY(0);
  
  delay(6000);
}

void sendButtonKlick(uint8_t button) {
  Gamepad.button(button, 1);
  #ifdef ROTBUTTONDELAY
  delay(ROTBUTTONDELAY);
  #endif
  Gamepad.button(button, 0);
}

void updateSwitch(bool state, int j, int joyButton) {
	if (state != switchStatesOld[j]) {  // changed?			
		
		if (state) {
			sendButtonKlick(joyButton);  // pos 1
		} else {
			sendButtonKlick(joyButton+1); // pos 2
		}
	}
	switchStatesOld[j] = state; // store last value for next check
}

void loop() {
	 
	// easy for pushbuttons and analog axis, just a 1:1 mapping 
	// except we have to leave out pin 6 and do a single check on pin lastButtonPin
	for (int i=0; i<numPushbuttons; i++) {
		if (i != 6) { 
			Gamepad.button(i+1, !digitalRead(i)); // pin 6 is for the led, inverted
		} else {
			Gamepad.button(i+1, digitalRead(i)); //
		} 		
	}
	
	Gamepad.X(analogRead(analogPins[4]));
	Gamepad.Y(analogRead(analogPins[5]));
	Gamepad.RX(analogRead(analogPins[6])); 
	Gamepad.RY(analogRead(analogPins[7]));

	
	// more to do for the switches
	// first, the 2-position
	int joyButton;
	int j;
	for (j=0; j<numSwitches; j++) {
		joyButton = switchJoypos + (j*2); // 2 joystickbuttons per inputpin
		updateSwitch(!digitalRead(switchPins[j]), j, joyButton);		
	}
	
	for (j=0; j<2; j++) {
		if (!digitalRead(threePosPins[j]) != threePosStateOld[j]) {
			joyButton = switchJoypos + (numSwitches*2) + (j*2);
			updateSwitch(!digitalRead(threePosPins[j]), j, joyButton);		
		}
	}
	
}
