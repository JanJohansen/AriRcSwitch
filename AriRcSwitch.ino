/*
Simple example for receiving

https://github.com/sui77/rc-switch
*/

#include "RCSwitch.h"
//#include <Arduino.h>


RCSwitch mySwitch = RCSwitch();
u16 ledTime = 0;

void setup() {
	Serial.begin(115200);

	pinMode(13, OUTPUT);	// For LED.

	mySwitch.enableTransmit(10);

	mySwitch.enableReceive(0);  // Receiver on inerrupt 0 => that is pin #2
	Serial.print("Receiving...");

	//  pinMode(6, OUTPUT);
}

void loop() {
	handleLed();
	handleRcSwitch();
}

void handleRcSwitch(){
	if (mySwitch.available()) {

		digitalWrite(13, HIGH);
		ledTime = 1100;

		int value = mySwitch.getReceivedValue();

		if (value == 0) {
			Serial.print("Unknown encoding");
		}
		else {
			Serial.print("{\"prt\":\"");
			Serial.print(mySwitch.getReceivedProtocol());
			Serial.print("\",\"bits\":\"");
			Serial.print(mySwitch.getReceivedBitlength());
			Serial.print("\",\"delay\":\"");
			Serial.print(mySwitch.getReceivedDelay());
			Serial.print("\",\"val\":\"");
			long long unsigned int x = mySwitch.getReceivedValue();
			//bitCount /= 4;
			for (int i = 0; i<16; i++)
			{
				u8 y = (x >> 60) & 0x0F;
				if (y<10) Serial.print((char)('0' + y));
				else Serial.print((char)('A' + y - 10));
				x <<= 4;
			}
			Serial.print("\"}\n");
		}
		mySwitch.resetAvailable();
	}

}

void handleLed(void){
	if(ledTime > 2000) digitalWrite(13, LOW);
	else digitalWrite(13, HIGH);
	
	if (ledTime == 0) {
		digitalWrite(13, LOW);
		ledTime = 30000;
	}
	ledTime--;
}
