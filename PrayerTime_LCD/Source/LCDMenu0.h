#ifndef LCDMenu0_H_
#define LCDMenu0_H_

#include "main.h"
#include <LiquidCrystal/LiquidCrystal.h>

class LCDMenu0 {
private:
	int8_t t_key_UpDown;  // First initial set to -1
public:
	LCDMenu0();
	void DisplayMenu(LiquidCrystal &lcd,  int8_t &key_UpDown);
	void ValidateKeyState(int8_t &key_State);
};

extern LCDMenu0 Menu0;
LCDMenu0 Menu0 = LCDMenu0();

inline void LCDMenu0::DisplayMenu(LiquidCrystal& lcd, int8_t &key_UpDown) {

	if ((nextPrayer+key_UpDown) > 5)
		key_UpDown = 0;
	else if ((nextPrayer+key_UpDown) < 0)
		key_UpDown = 5;

	if (t_key_UpDown != key_UpDown){
		ClearFirstLine() ;
// TODO : LCDMenu harus tidak berhubungan dengan AZAN
		double prayerTime = getPrayerTime(key_UpDown+nextPrayer, now());
		uint8_t hours, minutes;
		doubleToHrMin(prayerTime, hours, minutes);

		lcd.home();
		lcd.print(getPrayerName(key_UpDown+nextPrayer));
		lcd.print(" ");
		digitalClockDisplay(hours, minutes, 0);

		t_key_UpDown = key_UpDown;
	}


	lcd.setCursor(0, 2);
	digitalClockDisplay(hour(), minute(), second());
}

LCDMenu0::LCDMenu0() {
	t_key_UpDown = -1;
}


inline void LCDMenu0::ValidateKeyState(int8_t &key_State) {
	if ((nextPrayer+key_State) > 5) {
		key_State = 0;
	} 	else if ((nextPrayer+key_State) < 0) {
		key_State = -5;
	}
}

#endif /*LCDMenu0_H_ */
