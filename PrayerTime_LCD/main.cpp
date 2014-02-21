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
		right = right + 1;
		break;
	case 2: //up
		up = up + 1;
		break;
	case 3: //down
		up = up - 1;
		break;
	case 4: //left
		right = right - 1;
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

	//Serial.println (y);

}

//
void process_display() {

	if (DisplayLCD_State) {
		switch (menu_state) {
		case Menu0_MainMenu: {
			if (sel != 1) {
				Menu0.DisplayMenu(lcd, right);
			} else {
				menu_state = Menu1_SettingMenu;
				Menu1.DisplayClear(lcd);
				sel = 0;
			}
			break;
		}
		case Menu1_SettingMenu: {
			Menu1.DisplayMenu(lcd, right);
			break;
		}

		}
	}
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
		//delay(45);
		time_1 = millis();
	} else if (menu_state == Menu0_MainMenu) {
		process_display(); // If Menu0, update display event without key_State
	}

	time = time_2 - time_1;
	time = time / 1000;
	if (time >= 10) {
		turnOffDisplay();
		menu_state = 0;
		key_state = 0;
		right = 0, left = 0;
		up = 0, down = 0;
		sel = 0;
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
