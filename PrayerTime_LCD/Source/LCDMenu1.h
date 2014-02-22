/*
 * LCDMenu1.h
 *
 *  Created on: Feb 20, 2014
 *      Author: M Hendra Herviawan
 */

#ifndef LCDMENU1_H_
#define LCDMENU1_H_

#include "main.h"
#include <LiquidCrystal/LiquidCrystal.h>

class LCDMenu1 {
private:
public:
	void DisplayMenu(LiquidCrystal &lcd,  int8_t &key_UpDown);
	void DisplayClear(LiquidCrystal &lcd);
};

extern LCDMenu1 Menu1;
LCDMenu1 Menu1 = LCDMenu1();

inline void LCDMenu1::DisplayMenu(LiquidCrystal& lcd, int8_t& key_UpDown) {
	if (key_UpDown > 2 )
		key_UpDown = 2;
	else if (key_UpDown < 1 )
		key_UpDown = 1;

	lcd.home();
	lcd.print("Setting");
	lcd.setCursor(0, 2);
	lcd.print("                ");

	lcd.setCursor(0, 2);
	switch (key_UpDown) {
	case 1: //right
		lcd.print("1.Tgl dan Waktu");
		break;
	case 2: //up
		lcd.print("2.Lokasi");
		break;
	}

	//Serial.println("Setting");
}

inline void LCDMenu1::DisplayClear(LiquidCrystal &lcd) {
	lcd.clear();
}

#endif /* LCDMENU1_H_ */
