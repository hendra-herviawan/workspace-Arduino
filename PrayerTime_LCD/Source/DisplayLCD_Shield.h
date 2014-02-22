/*
 * LiquidCristal.h
 *
 *  Created on: Jan 2, 2014
 *      Author: M Hendra Herviawan
 */

#ifndef DisplayLCD_Shield_H_
#define DisplayLCD_Shield_H_

#include "main.h"
#include <LiquidCrystal/LiquidCrystal.h>

#define LCDBacklight_pin 10
#define CONTRAST 20
#define LCD_maxTime 1

volatile boolean DisplayLCD_State = true;
volatile time_t LCD_timer = 0;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void globalDisplayUISetup() {
	/*LCD Backlight PWM*/
	pinMode(LCDBacklight_pin, OUTPUT);
	analogWrite(LCDBacklight_pin, CONTRAST);

	// set up the LCD's number of columns and rows:
	lcd.begin(16, 2);
}

/////////////////////////////////////////////////////////////////////////////

void turnOnDisplay() {
	if (!DisplayLCD_State) {
		LCD_timer = millis();

		lcd.display();
		analogWrite(LCDBacklight_pin, CONTRAST);
		DisplayLCD_State = true;
	}
}

void turnOffDisplay() {
	if (DisplayLCD_State) {
		lcd.noDisplay();
		analogWrite(LCDBacklight_pin, 0);
		DisplayLCD_State = false;
		LCD_timer = 0;
	}
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

	//lcdTimer();
}

void ClearDisplay() {
	lcd.clear();
}

void ClearFirstLine() {
	lcd.home();
	lcd.print("                ");
}

void ClearSecondLine() {
	lcd.home();
	lcd.print("                ");
}
#endif /* DisplayLCD_Shield_H_ */
