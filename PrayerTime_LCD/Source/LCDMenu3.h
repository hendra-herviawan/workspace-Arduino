/*
 * LCDMenu1.h
 *
 *  Created on: Feb 20, 2014
 *      Author: M Hendra Herviawan
 */

#ifndef LCDMENU3_H_
#define LCDMENU3_H_

#include "main.h"
#include <LiquidCrystal/LiquidCrystal.h>

class LCDMenu3 {
private:
	int8_t m, h;
	int8_t active_form; // Penanda field mana (dd, mm, yy, etc) yg sedang aktiv
	uint8_t confirmation; // Penanda apakah confirmasi atau bukan
public:
	LCDMenu3();
	void setTime(int8_t p_h, int8_t p_m);
	void DisplayChangeTime(LiquidCrystal &p_lcd, int8_t &p_UpDown,
			int8_t &p_RightLeft);
	void DisplayConfirmation(LiquidCrystal &p_lcd, int8_t &p_UpDown);

	uint8_t getConfirmation() {
		return confirmation;
	}

	void setConfirmation(uint8_t p_confirmation) {
		confirmation = p_confirmation;
	}

	int8_t getH() {
		return h;
	}

	int8_t getM() {
		return m;
	}
};

extern LCDMenu3 Menu3;
LCDMenu3 Menu3 = LCDMenu3();

LCDMenu3::LCDMenu3() {
	m = 0;
	h = 0;
	active_form = -1;
	confirmation = false;
}

inline void LCDMenu3::setTime(int8_t p_h, int8_t p_m) {
	m = p_m;
	h = p_h;
	active_form = -1;
	setConfirmation(false);
}

inline void LCDMenu3::DisplayChangeTime(LiquidCrystal &p_lcd, int8_t &p_UpDown,
		int8_t &p_RightLeft) {

	char time[6];

	if (p_RightLeft > 1)
		p_RightLeft = 1;
	else if (p_RightLeft < 0)
		p_RightLeft = 0;

	if (p_RightLeft == 0) {
		if (active_form != p_RightLeft) {
			p_UpDown = h;
		} else {
			if (p_UpDown > 24)
				p_UpDown = 24;
			else if (p_UpDown < 0)
				p_UpDown = 0;

			h = p_UpDown;
		}
		active_form = 0;
	} else 	if (p_RightLeft == 1) {
		if (active_form != p_RightLeft) {
			p_UpDown = m;
		} else {
			if (p_UpDown > 59)
				p_UpDown = 59;
			else if (p_UpDown < 0)
				p_UpDown = 0;

			m = p_UpDown;

		}
		active_form = 1;
	}

	p_lcd.home();
	p_lcd.print("Waktu ...");
	//p_lcd.setCursor(0, 2);
	//p_lcd.print("                ");

	p_lcd.setCursor(0, 2);
	sprintf(time, "%d:%d", h, m);
	p_lcd.print(time);

	//Serial.println("Setting");
}

inline void LCDMenu3::DisplayConfirmation(LiquidCrystal& p_lcd,
		int8_t& p_UpDown) {
	char time[6];

	if (p_UpDown > 1)
		p_UpDown = 1;
	else if (p_UpDown < 0)
		p_UpDown = 0;

	p_lcd.home();
	p_lcd.print("Waktu: ");
	sprintf(time, "%d:%d", h, m);
	p_lcd.print(time);

	p_lcd.setCursor(0, 2);
	if (p_UpDown == 1)
		p_lcd.print("Ya   ");
	else if (p_UpDown == 0)
		p_lcd.print("Tidak");

}

#endif /* LCDMENU1_H_ */
