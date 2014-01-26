/*
 * main.cpp
 *
 *  Created on: Jan 17, 2014
 *      Author: M Hendra Herviawan
 */

#include "main.h"

// the setup routine runs once when you press reset:
void setup() {

	Serial.begin(9600);

	pinMode(BUZZ_pin, OUTPUT); //Buzz Pin

	setSyncProvider(RTC.get);   // the function to get the time from the RTC
	if (timeStatus() != timeSet)
		Serial.println(F("Unable to sync with the RTC"));
	else
		Serial.println(F("RTC has set the system time"));
	//setTime(7,39,0,23,12,2012);

	/* Setup the interrupt pin */
	RTC.enableSQW();
	//pinMode(interrupt_pin, INPUT);
	//attachInterrupt(0, pin2Interrupt, FALLING);

	//DisplayClock.setup(6,7,8);
	//Setup Azan
	globalAzanSetup();

	Seconds = second();
	Minutes = minute();
	Hours = hour();
}

void loop() {
	uint8_t _Minutes = Minutes;
	uint8_t _Hours = Hours;

	//double ZuhurTime = getPrayerTime(nextPrayer, now());
	uint8_t _hours, _minutes;
	doubleToHrMin(NextPrayerTime, _hours, _minutes);

	for (byte Multiplex = 0; Multiplex <= 7; Multiplex++) {
		//if (Minutes != _Minutes){
		//Minutes = _Minutes;
		//updateClock7Segment (Multiplex, 12, 00); // Jam 2
		DisplayClock.updateDisplay(0, Multiplex, _Hours, _Minutes); //Jam 1
		DisplayAzan.updateDisplay(0, Multiplex, _hours, _minutes); //Jam 1
		//}
	}

	Alarm.delay(17); // wait one second between clock display

	if (Hours != _Hours) {
		Hours = _Hours;
		if (_Hours >= 4) {
			digitalWrite(BUZZ_pin, HIGH);
			delay(200);
			digitalWrite(BUZZ_pin, LOW);
		}
	}

	//Seconds = second();
	Minutes = minute();
	Hours = hour();

	//Serial.println(DisplayClock.Pulse);
	//serialClockDisplay(hour(), minute());
	//delay(500);
}

int main(void) {
	init();
	setup();

	for (;;)
		loop();

	return 0; // not reached
}

void BUZZ() {

	uint8_t BUZZ_iteration = 0;
	uint8_t duration = BUZZ_Duration * 60;

	//cli();                // disable global interrupts
	while (BUZZ_iteration <= duration) {
		//turnOffDisplay(); //digitalWrite(LED_pin, !digitalRead(LED_pin));
		digitalWrite(BUZZ_pin, HIGH); // turn the BUZZ on (HIGH is the voltage level)
		delay(500);               // wait for a second

		//turnOnDisplay(); //digitalWrite(LED_pin, !digitalRead(LED_pin));
		digitalWrite(BUZZ_pin, LOW); // turn the BUZZ off by making the voltage LOW
		delay(500);

		BUZZ_iteration += 1;
	}
	//sei();                // enable interrupts
}

void pin2Interrupt() {
	//Serial.println("Interrup!!!");
	//serialClockDisplay(hour(), minute());
	DisplayClock.Pulse = !DisplayClock.Pulse;
}
