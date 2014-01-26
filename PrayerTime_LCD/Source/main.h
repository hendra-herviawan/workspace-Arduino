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

#include "Time.h"
#include "TimeAlarms.h"
#include "PrayerTime.h"

#include "DebugHelp.h"
#include "DisplayUI.h"
#include "Azan.h"

const uint8_t LED_pin = 12;
const uint8_t BUZZ_pin = 13;
const uint8_t interrupt_pin = 2;

volatile boolean toggle = false;

const uint8_t BUZZ_Duration = 1;
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
#endif /* MAIN_H_ */
