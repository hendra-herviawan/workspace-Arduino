/*
 * displayClock.h
 *
 *  Created on: Jan 17, 2014
 *      Author: M Hendra Herviawan
 */

#ifndef DISPLAYCLOCK_H_
#define DISPLAYCLOCK_H_

#include <arduino.h>

//namespace Display {

const static uint8_t segDisp[10] = { 0b11111100, 0b01100000, 0b11011010,
		0b11110010, 0b01100110, 0b10110110, 0b10111110, 0b11100000, 0b11111110,
		0b11100110 };

class displayClock {
public:
	volatile uint8_t Pulse;

	displayClock(uint8_t _clockpin, uint8_t _latchpin, uint8_t _datapin);
	void setup(uint8_t _clockpin, uint8_t _latchpin, uint8_t _datapin);
	void updateDisplay(uint8_t _ssdType, uint8_t &_Multiplex, uint8_t &hours, uint8_t &minutes);
	void latchLow() {digitalWrite(latchpin, LOW);}
	void latchHigh() {digitalWrite(latchpin, HIGH);}

private:
	uint8_t clockpin;//  connect to pin 11 on the '595
	uint8_t latchpin;// connect to pin 12 on the '595
	uint8_t datapin;// connect to pin 14 on the '595

	void charlyplex595AnodeClock7Segment(uint8_t &_Multiplex, uint8_t &hh, uint8_t &h, uint8_t &mm, uint8_t &m);
	void charlyplex595CathodeClock7Segment(uint8_t &_Multiplex, uint8_t &hh, uint8_t &h, uint8_t &mm, uint8_t &m);

};

//} /* namespace Display */

//extern displayClock DisplayClock;

#endif /* DISPLAYCLOCK_H_ */
