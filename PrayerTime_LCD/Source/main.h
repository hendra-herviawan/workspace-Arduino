/*
 * main.h
 *
 *  Created on: Jan 2, 2014
 *      Author: M Hendra Herviawan
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <avr/power.h>

#include <arduino.h>
#include "DebugHelp.h"

#include "Time.h"
#include "TimeAlarms.h"
#include "PrayerTime.h"
#include "Azan.h"

#include "DisplayLCD_Shield.h"
#include "LCDMenu0.h"
#include "LCDMenu1.h"
#include "LCDMenu2.h"

#define LED_pin 12
#define BUZZ_pin 13
#define interrupt_pin 2
#define BUZZ_Duration 1


volatile boolean toggle = false;

uint8_t y;
int8_t menu_state = 0, key_state = 0;
int8_t RightLeft=0,left=0,UpDown=0,down=0;
int8_t sel=0;
unsigned long up_time_1,up_time_2,up_time;
double time_1,time_2,time;
int8_t last_st=0,st=0;

//LCD Menu State
#define Menu0_MainMenu 0
#define Menu1_SettingMenu 1

/////////////////////////////////////////////////////////////////////////////

void pin2Interrupt(void);
void BUZZ();

void implement_power_saving_hacks() {

	power_adc_disable();
	power_spi_disable();
	//power_twi_disable();       // I2C
	// power_timer0_disable(); // PWM 5 & 6, millis(), do not disable
	power_timer1_disable();    // PWM 9 & 10
	//power_timer2_disable();    // PWM 3 & 11
	//DDRD  &= B0000011;         // 0 and 1 are serial comms
	//PORTD |= B1111100;
	//DDRB  &= B1100000;         // 6 and 7 are crystal
	//PORTB |= B0011111;

	}

void get_up_time(){

  up_time_2 = millis();
  up_time = up_time_2 - up_time_1;
  up_time = up_time/1000;        //time in seconds
}

void resetKeyState(){
	menu_state = 0;
	key_state = 0;
	RightLeft = 0;
	UpDown = 0;
	sel = 0;
}
#endif /* MAIN_H_ */
