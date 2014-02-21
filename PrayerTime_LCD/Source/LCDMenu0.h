#ifndef LCDMenu0_H_
#define LCDMenu0_H_

#include "main.h"
#include <LiquidCrystal/LiquidCrystal.h>

class LCDMenu0 {
private:
	int8_t t_key_Right;
public:
	LCDMenu0();
	void DisplayMenu(LiquidCrystal &lcd,  int8_t &key_Right);
	void ValidateKeyState(int8_t &key_State);
	void DisplayClear(LiquidCrystal &lcd);
};

extern LCDMenu0 Menu0;
LCDMenu0 Menu0 = LCDMenu0();

inline void LCDMenu0::DisplayMenu(LiquidCrystal& lcd, int8_t &key_Right) {

	if (t_key_Right != key_Right){
		lcd.home();
		lcd.print("                ");
		t_key_Right = key_Right;
	}

	if ((nextPrayer+key_Right) > 5)
		key_Right = 0;
	else if ((nextPrayer+key_Right) < 0)
		key_Right = -5;

	double prayerTime = getPrayerTime(key_Right+nextPrayer, now());
	uint8_t hours, minutes;
	doubleToHrMin(prayerTime, hours, minutes);

	lcd.home();
	lcd.print(getPrayerName(key_Right+nextPrayer));
	lcd.print(" ");
	digitalClockDisplay(hours, minutes, 0);

	lcd.setCursor(0, 2);
	digitalClockDisplay(hour(), minute(), second());
}

LCDMenu0::LCDMenu0() {
	t_key_Right = -1;
}

inline void LCDMenu0::DisplayClear(LiquidCrystal &lcd) {
	lcd.clear();
}

inline void LCDMenu0::ValidateKeyState(int8_t &key_State) {
	if ((nextPrayer+key_State) > 5) {
		key_State = 0;
	} 	else if ((nextPrayer+key_State) < 0) {
		key_State = -5;
	}
}

#endif /*LCDMenu0_H_ */
