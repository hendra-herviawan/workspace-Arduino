/*
 * DebugHelp.h
 *
 *  Created on: Jan 2, 2014
 *      Author: M Hendra Herviawan
 */

#ifndef DEBUGHELP_H_
#define DEBUGHELP_H_

#include "main.h"

int freeRam();
void serialDateDisplay(uint8_t year, uint8_t month, uint8_t day);
void serialClockDisplay(uint8_t hour, uint8_t minute);
void serialPrintDigits(uint8_t digits);

/////////////////////////////////////////////////////////////////
int freeRam() {
	extern int __heap_start, *__brkval;
	int v;
	return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}

void serialDateDisplayX(int16_t year, uint8_t month, uint8_t day) {
	// digital clock display of the time

	Serial.print(year);
	serialPrintDigits(month);
	serialPrintDigits(day);

	Serial.println();
}

void serialClockDisplay(uint8_t hour, uint8_t minute) {
	// digital clock display of the time
	Serial.print(hour);
	serialPrintDigits(minute);
	serialPrintDigits(0);
	Serial.println();
}

void serialPrintDigits(uint8_t digits) {
	Serial.print(":");
	if (digits < 10)
		Serial.print('0');
	Serial.print(digits);
}

#endif /* DEBUGHELP_H_ */
