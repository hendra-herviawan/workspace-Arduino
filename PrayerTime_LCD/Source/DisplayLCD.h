/*
 * LiquidCristal.h
 *
 *  Created on: Jan 2, 2014
 *      Author: M Hendra Herviawan
 */

#ifndef LIQUIDCRISTAL_H_
#define LIQUIDCRISTAL_H_

#include "main.h"
#include <LiquidCrystal/LiquidCrystal.h>

const uint8_t LCDBacklight_pin = 11;
volatile boolean LCD_status = true;
volatile time_t LCD_timer = 0;

const uint8_t CONTRAST = 20;
const uint8_t LCD_maxTime = 1;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(10, 9, 5, 6, 7, 8);

void globalDisplayUISetup() {
	/*LCD Backlight PWM*/
	pinMode(LCDBacklight_pin, OUTPUT);
	analogWrite(LCDBacklight_pin, CONTRAST);

	// set up the LCD's number of columns and rows:
	lcd.begin(16, 2);
}

/////////////////////////////////////////////////////////////////////////////

void turnOnDisplay() {
	LCD_timer = millis();

	lcd.display();
	analogWrite(LCDBacklight_pin, CONTRAST);
	LCD_status = true;
}

void turnOffDisplay() {
	lcd.noDisplay();
	analogWrite(LCDBacklight_pin, 0);
	LCD_status = false;
	LCD_timer = 0;
}

void lcdTimer() {
	time_t tmpMaxLCDOn, tmpTimeElapse;
	tmpMaxLCDOn = 60000;
	tmpMaxLCDOn *= (time_t) LCD_maxTime;
	tmpTimeElapse = millis() - LCD_timer;

	if (tmpTimeElapse > tmpMaxLCDOn)
		turnOffDisplay();

	//Serial.println(tmpMaxLCDOn);
	//Serial.println(tmpTimeElapse);

}

void printDigits(uint8_t digits) {
	// utility function for digital clock display: prints preceding colon and leading 0
	lcd.print(":");
	if (digits < 10)
		lcd.print('0');
	lcd.print(digits, DEC);
}

void digitalClockDisplay(uint8_t hour, uint8_t minute, uint8_t second) {

	// digital clock display of current time
	lcd.print(hour, DEC);
	printDigits(minute);
	if (second != 0)
		printDigits(second);

	lcdTimer();
}

#endif /* LIQUIDCRISTAL_H_ */
