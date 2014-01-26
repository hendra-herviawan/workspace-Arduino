/*
 * main.cpp
 *
 *  Created on: Jan 1, 2014
 *      Author: M Hendra Herviawan
 */
/*
 * main.cpp

 *
 *  Created on: Dec 24, 2013
 *      Author: M Hendra Herviawan
 */

#include "main.h"

// the setup routine runs once when you press reset:
void setup() {
	implement_power_saving_hacks();

	Serial.begin(9600);

	// initialize the digital pin as an output.
	pinMode(LED_pin, OUTPUT);
	pinMode(BUZZ_pin, OUTPUT);

	/* Setup the interrupt pin */
	pinMode(interrupt_pin, INPUT);
	attachInterrupt(0, pin2Interrupt, FALLING);

	//Setup Display UI
	globalDisplayUISetup();

	//Setup Azan
	globalAzanSetup();

}

// the loop routine runs over and over again forever:
void loop() {
	//digitalClockDisplay(hour(), minute());

	if (LCD_status) {
		lcd.home();
		double prayerTime = getPrayerTime(nextPrayer, now());
		uint8_t hours, minutes;
		doubleToHrMin(prayerTime, hours, minutes);
		lcd.print(getPrayerName(nextPrayer));
		lcd.print(" ");
		digitalClockDisplay(hours, minutes, 0);


		lcd.setCursor(0, 2);
		digitalClockDisplay(hour(), minute(), second());

		//lcd.print(freeRam());
	}

	//digitalWrite(LED_pin, !digitalRead(LED_pin));   // turn the LED on (HIGH is the voltage level)
	Alarm.delay(1000); // wait one second between clock display
	//digitalWrite(LED_pin, !digitalRead(LED_pin));    // turn the LED off by making the voltage LOW
	//delay();               // wait for a second
}

int main(void) {
	init();
	setup();

	for (;;)
		loop();

	return 0; // not reached
}


void pin2Interrupt(void) {
	Serial.println(F("Interrup!!!"));

	/* This will bring us back from sleep. */
	if (alarm_status) {
		toggle = true;
		return ;
	}

	if (LCD_status){
		turnOffDisplay();
	} else {
		turnOnDisplay();
	}

}

void BUZZ() {

	uint16_t BUZZ_iteration = 0;
	uint16_t duration = BUZZ_Duration * 60;
	toggle = false;

	while (!toggle && (BUZZ_iteration++ <= duration)) {
		turnOffDisplay(); //digitalWrite(LED_pin, !digitalRead(LED_pin));
		digitalWrite(BUZZ_pin, HIGH); // turn the BUZZ on (HIGH is the voltage level)
		delay(500);               // wait for a second

		turnOnDisplay(); //digitalWrite(LED_pin, !digitalRead(LED_pin));
		digitalWrite(BUZZ_pin, LOW); // turn the BUZZ off by making the voltage LOW
		delay(500);
	}
	turnOnDisplay(); //digitalWrite(LED_pin, !digitalRead(LED_pin));
	toggle = false;

}

