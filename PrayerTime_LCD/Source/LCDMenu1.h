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
	void DisplayMenu(LiquidCrystal &lcd,  int8_t &key_Right);
	void DisplayClear(LiquidCrystal &lcd);
};

extern LCDMenu1 Menu1;
LCDMenu1 Menu1 = LCDMenu1();

inline void LCDMenu1::DisplayMenu(LiquidCrystal& lcd, int8_t& key_Right) {
	lcd.home();
	lcd.print("Setting");
	Serial.println("Setting");
}

inline void LCDMenu1::DisplayClear(LiquidCrystal &lcd) {
	lcd.clear();
}

#endif /* LCDMENU1_H_ */
