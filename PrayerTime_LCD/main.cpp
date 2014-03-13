/*
 * main.cpp
 *
 *  Created on: Jan 1, 2014
 *      Author: M Hendra Herviawan
 */
/*
 * main.cpp

 *
 *  Created on: Dec 24, 2013
 *      Author: M Hendra Herviawan
 */

#include "main.h"

void process_state() {

	switch (key_state) {
	case 1: //right
		RightLeft = RightLeft + 1;
		break;
	case 2: //up
		UpDown = UpDown + 1;
		break;
	case 3: //down
		UpDown = UpDown - 1;
		break;
	case 4: //left
		RightLeft = RightLeft - 1;
		break;
	case 5:
		break;
	}
}

void read_state() {

	key_state = 0;
	y = analogRead(0);
	//lcd.setCursor(10,1);
	if (y < 10) {
		//Serial.println ("Right ");
		key_state = 1;
	} else if (y < 100) {
		//Serial.println ("Down    ");
		key_state = 3;
	} else if (y < 150) {
		//Serial.println ("Up  ");
		key_state = 2;
	} else if (y < 215) {
		//Serial.println ("Select  ");
		key_state = 5;
		sel = 1;
	} else if (y < 225) {
		//Serial.println ("Left");
		key_state = 4;
	}
	if (key_state != 0)
		delay(45);
	//Serial.println (y);

}

//
void process_display() {

	if (DisplayLCD_State) {
		switch (menu_state) {
		case Menu0_MainMenu:
			if (sel == 0) {
// TODO BUG #1 - Setelah setting, waktu sholat (line 1) tidak update
				Menu0.DisplayMenu(lcd, UpDown);
			} else {
				resetKeyState();
				menu_state = Menu1_SettingMenu;
				ClearDisplay();
				Menu1.DisplayMenu(lcd, UpDown);
			}
			break;
		case Menu1_SettingMenu:
			if (sel == 0)
				Menu1.DisplayMenu(lcd, UpDown);
			else {
				ClearDisplay();

				if (UpDown == 1) { // Setting Tanggal & Waktu
					resetKeyState();
					menu_state = 2;
					Menu2.setDate(day(), month(), year());
					Menu2.DisplayChangeDate(lcd, UpDown, RightLeft);
				} else if (UpDown == 2) { // Kembali ke menu utama
					resetKeyState();
					//menu_state = 3;
					//Menu3.setTime(hour(), minute());
					//Menu3.DisplayChangeTime(lcd, UpDown, RightLeft);
				}
			}

			break;
		case 2:
			if (sel == 0)
				if (Menu2.getConfirmation() != true)
					Menu2.DisplayChangeDate(lcd, UpDown, RightLeft);
				else
					Menu2.DisplayConfirmation(lcd, UpDown);
			else {

				if (Menu2.getConfirmation() == false) {
					resetKeyState();
					menu_state = 2;

					ClearDisplay();
					Menu2.setConfirmation(true);
					Menu2.DisplayConfirmation(lcd, UpDown);
				} else {
					if (UpDown == 1) {
						int8_t dd = Menu2.getDd();
						int8_t mm = Menu2.getMm();
						int16_t yy = Menu2.getYy();

						serialDateDisplayX(yy, mm, dd);
						setTime(hour(), minute(), 0, dd, mm, yy);
						globalAzanSetup();

						resetKeyState();
						menu_state = 3;

						Menu3.setTime(hour(), minute());
						Menu3.DisplayChangeTime(lcd, UpDown, RightLeft);
					} else {
						resetKeyState();
					}
				}
			}
			break;
		case 3:
			if (sel == 0)
				if (Menu3.getConfirmation() == false)
					Menu3.DisplayChangeTime(lcd, UpDown, RightLeft);
				else
					Menu3.DisplayConfirmation(lcd, UpDown);
			else {

				if (Menu3.getConfirmation() == false) {
					resetKeyState();
					menu_state = 3;

					ClearDisplay();
					Menu3.setConfirmation(true);
					Menu3.DisplayConfirmation(lcd, UpDown);
				} else {
					if (UpDown == 1) {
						int8_t h = Menu3.getH();
						int8_t m = Menu3.getM();

						setTime(h, m, 0, day(), month(), year());
						globalAzanSetup();
						//menu_state = Menu0_MainMenu;
					}
					//Menu3.setConfirmation(false);
					resetKeyState();
				}
			}
			break;
		}
	}
}

/////////////////////////////////////////////////////////////////
void setArduinoTime(int hr, int min, int sec, int day, int month, int yr) {
	setTime(hr, min, sec, day, month, yr);

	/*	setSyncProvider(RTC.get);   // the function to get the time from the RTC
	 if (timeStatus() != timeSet)
	 Serial.println(F("Unable to sync with the RTC"));
	 else
	 Serial.println(F("RTC has set the system time"));
	 */
}

// the setup routine runs once when you press reset:
void setup() {
//implement_power_saving_hacks();

	Serial.begin(9600);

// initialize the digital pin as an output.
	pinMode(LED_pin, OUTPUT);
	pinMode(BUZZ_pin, OUTPUT);

	/* Setup the interrupt pin */
//pinMode(interrupt_pin, INPUT);
//attachInterrupt(0, pin2Interrupt, FALLING);
//Setup Display UI
	globalDisplayUISetup();

//Setup Azan
	setArduinoTime(18, 50, 0, 23, 2, 2014);
	globalAzanSetup();

//Setup Display Timer
	up_time_1 = millis();
	time_1 = millis();

}

// the loop routine runs over and over again forever:
void loop() {
//digitalClockDisplay(hour(), minute());
	time_2 = millis();
	last_st = key_state;
	read_state();
	st = key_state;

	if (st != last_st) {
		process_state();
		process_display();
		time_1 = millis();
	} else if (menu_state == Menu0_MainMenu) {
		process_display(); // If Menu0, update display event without key_State
	}

	time = time_2 - time_1;
	time = time / 1000;
	if (time >= 10) {
		turnOffDisplay();
		resetKeyState();

		//pinMode(LCDBacklight_pin, OUTPUT);
		//DisplayLCD_State = false;
	} else {
		turnOnDisplay();
		//pinMode(LCDBacklight_pin, INPUT);
		//DisplayLCD_State = true;
	}

	Alarm.delay(90); // wait one second between clock display
}

int main(void) {
	init();
	setup();

	for (;;)
		loop();

	return 0; // not reached
}

void BUZZ() {

	uint16_t BUZZ_iteration = 0;
	uint16_t duration = BUZZ_Duration * 60;
	toggle = false;

	while (!toggle && (BUZZ_iteration++ <= duration)) {
		turnOffDisplay(); //digitalWrite(LED_pin, !digitalRead(LED_pin));
		digitalWrite(BUZZ_pin, HIGH); // turn the BUZZ on (HIGH is the voltage level)
		delay(500);               // wait for a second

		turnOnDisplay(); //digitalWrite(LED_pin, !digitalRead(LED_pin));
		digitalWrite(BUZZ_pin, LOW); // turn the BUZZ off by making the voltage LOW
		delay(500);
	}
	turnOnDisplay(); //digitalWrite(LED_pin, !digitalRead(LED_pin));
	toggle = false;
}

/*void pin2Interrupt(void) {
 Serial.println(F("Interrup!!!"));

 This will bring us back from sleep.
 if (alarm_status) {
 toggle = true;
 return ;
 }

 if (LCD_status){
 turnOffDisplay();
 } else {
 turnOnDisplay();
 }

 }*/
