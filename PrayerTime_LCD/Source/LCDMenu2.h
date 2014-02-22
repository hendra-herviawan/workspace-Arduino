/*
 * LCDMenu1.h
 *
 *  Created on: Feb 20, 2014
 *      Author: M Hendra Herviawan
 */

#ifndef LCDMENU2_H_
#define LCDMENU2_H_

#include "main.h"
#include <LiquidCrystal/LiquidCrystal.h>

class LCDMenu2 {
private:
	int8_t dd, mm;
	int16_t yy;
	int8_t s, m, h;
	int8_t active_form; // Penanda field mana (dd, mm, yy, etc) yg sedang aktiv
	uint8_t confirmation; // Penanda apakah confirmasi atau bukan
public:
	LCDMenu2();
	void setDate(int8_t p_dd, int8_t p_mm, int16_t p_yy);
	void DisplayChangeDate(LiquidCrystal &p_lcd, int8_t &p_UpDown,
			int8_t &p_RightLeft);
	void DisplayConfirmation(LiquidCrystal &p_lcd, int8_t &p_UpDown);

	uint8_t getConfirmation() {
		return confirmation;
	}

	void setConfirmation(uint8_t p_confirmation) {
		confirmation = p_confirmation;
	}

	int8_t getDd() {
		return dd;
	}

	int8_t getMm() {
		return mm;
	}

	int16_t getYy() {
		return yy;
	}
};

extern LCDMenu2 Menu2;
LCDMenu2 Menu2 = LCDMenu2();

LCDMenu2::LCDMenu2() {
	dd = 0;
	mm = 0;
	yy = 0;
	s = 0;
	m = 0;
	h = 0;
	active_form = -1;
	confirmation = false;
}

inline void LCDMenu2::setDate(int8_t p_dd, int8_t p_mm, int16_t p_yy) {
	dd = p_dd;
	mm = p_mm;
	yy = p_yy;
	active_form = -1;
	setConfirmation(false);
}

inline void LCDMenu2::DisplayChangeDate(LiquidCrystal &p_lcd, int8_t &p_UpDown,
		int8_t &p_RightLeft) {

	char date[10];
	static  const uint8_t monthDays[]={31,28,31,30,31,30,31,31,30,31,30,31}; // API starts months from 1, this array starts from 0

	if (p_RightLeft > 2)
		p_RightLeft = 2;
	else if (p_RightLeft < 0)
		p_RightLeft = 0;

	if (p_RightLeft == 0) {
		if (active_form != p_RightLeft) {
			p_UpDown = dd;
			Serial.println(1);
		} else {
			uint8_t maxdd = monthDays[mm-1]; // mm start from 1
			if (p_UpDown > maxdd)
				p_UpDown = maxdd;
			else if (p_UpDown < 0)
				p_UpDown = 1;

			dd = p_UpDown;
		}
		active_form = 0;
	} else 	if (p_RightLeft == 1) {
		if (active_form != p_RightLeft) {
			p_UpDown = mm;
		} else {
			if (p_UpDown > 12)
				p_UpDown = 12;
			else if (p_UpDown < 0)
				p_UpDown = 1;

			mm = p_UpDown;

			uint8_t maxdd = monthDays[mm-1]; // mm start from 1
			if (dd > maxdd)
				dd = maxdd;

		}
		active_form = 1;
	} else 	if (p_RightLeft == 2) {
		if (active_form != p_RightLeft) {
			p_UpDown = yy-2000;
		} else {
			if (p_UpDown > 99)
				p_UpDown = 99;
			else if (p_UpDown < 0)
				p_UpDown = 0;

			yy = p_UpDown+2000;

		}
		active_form = 2;
	}

	p_lcd.home();
	p_lcd.print("Tgl ...");
	//p_lcd.setCursor(0, 2);
	//p_lcd.print("                ");

	p_lcd.setCursor(0, 2);
	sprintf(date, "%d/%d/%d", dd, mm, yy);
	p_lcd.print(date);

	//Serial.println("Setting");
}

inline void LCDMenu2::DisplayConfirmation(LiquidCrystal& p_lcd,
		int8_t& p_UpDown) {
	char date[10];

	if (p_UpDown > 1)
		p_UpDown = 1;
	else if (p_UpDown < 0)
		p_UpDown = 0;

	p_lcd.home();
	p_lcd.print("Tgl:");
	sprintf(date, "%d/%d/%d", dd, mm, yy);
	p_lcd.print(date);

	p_lcd.setCursor(0, 2);
	if (p_UpDown == 1)
		p_lcd.print("Ya   ");
	else if (p_UpDown == 0)
		p_lcd.print("Tidak");

}

#endif /* LCDMENU1_H_ */
