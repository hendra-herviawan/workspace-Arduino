#ifndef LCDMenu0_H_
#define LCDMenu0_H_

#include "main.h"
#include <LiquidCrystal/LiquidCrystal.h>

class LCDMenu0 {
private:

public:
	void DisplayMenu(LiquidCrystal &lcd,  int8_t &key_State);
	void ValidateKeyState(int8_t &key_State);
};

inline void LCDMenu0::DisplayMenu(LiquidCrystal& lcd, int8_t &key_State) {

	if ((nextPrayer+key_State) > 5) {
		key_State = 0;
	} 	else if ((nextPrayer+key_State) < 0) {
		key_State = -5;
	}

	lcd.home();
	double prayerTime = getPrayerTime(key_State+nextPrayer, now());
	uint8_t hours, minutes;
	doubleToHrMin(prayerTime, hours, minutes);
	lcd.print(getPrayerName(key_State+nextPrayer));
	lcd.print(" ");
	digitalClockDisplay(hours, minutes, 0);

	lcd.setCursor(0, 2);
	digitalClockDisplay(hour(), minute(), second());
}

extern LCDMenu0 Menu0;

inline void LCDMenu0::ValidateKeyState(int8_t &key_State) {
	if ((nextPrayer+key_State) > 5) {
		key_State = 0;
	} 	else if ((nextPrayer+key_State) < 0) {
		key_State = -5;
	}
}

#endif /*LCDMenu0_H_ */
