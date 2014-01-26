/*
 * displayClock.cpp
 *
 *  Created on: Jan 17, 2014
 *      Author: M Hendra Herviawan
 */

#include <displayClock.h>

//namespace Display {

displayClock::displayClock(uint8_t _clockpin,
		uint8_t _latchpin, uint8_t _datapin) {
	Pulse = 0;

	clockpin = _clockpin; // = 6; // connect to pin 11 on the '595
	latchpin = _latchpin; // = 7; // connect to pin 12 on the '595
	datapin = _datapin; // = 8; // connect to pin 14 on the '595

	pinMode(latchpin, OUTPUT);
	pinMode(clockpin, OUTPUT);
	pinMode(datapin, OUTPUT);
}

void displayClock::updateDisplay(uint8_t _ssdType, uint8_t &_Multiplex, uint8_t &hours,
		uint8_t &minutes) {
	uint8_t m = 0, mm = 0;
	uint8_t h = 0, hh = 0;

	if (minutes < 10) {
		m = segDisp[minutes];
		mm = segDisp[0];
	} else {
		m = segDisp[minutes % 10];
		mm = segDisp[minutes / 10];
	}

	if (hours < 10) {
		h = segDisp[hours];
		hh = 0;
	} else {
		h = segDisp[hours % 10] | 0b00000001;
		hh = segDisp[hours / 10];
	}

	if (_ssdType == 0) { //Anode
		charlyplex595AnodeClock7Segment(_Multiplex, hh, h, mm, m);
	} else {
		charlyplex595CathodeClock7Segment(_Multiplex, hh, h, mm, m);
	}

	if (Pulse == 1) {
		h |= 0b00000001;
		mm |= 0b00000001;
	}

	latchLow();
	shiftOut(datapin, clockpin, LSBFIRST, m); // clears the right display
	shiftOut(datapin, clockpin, LSBFIRST, mm); // clears the left display
	shiftOut(datapin, clockpin, LSBFIRST, h); // clears the right display
	shiftOut(datapin, clockpin, LSBFIRST, hh); // clears the left display
	latchHigh();
}

void displayClock::charlyplex595AnodeClock7Segment(uint8_t &_Multiplex,
		uint8_t &hh, uint8_t &h, uint8_t &mm, uint8_t &m) {

	m = ~(m & ~(0b10000000 >> _Multiplex));
	mm = ~(mm & ~(0b10000000 >> _Multiplex));
	h = ~(h & ~(0b10000000 >> _Multiplex));
	hh = ~(hh & ~(0b10000000 >> _Multiplex));
	//shiftOut(datapin, clockpin, LSBFIRST, ~(m & ~(0b10000000 >> _Multiplex))); // clears the right display
	//shiftOut(datapin, clockpin, LSBFIRST, ~(mm & ~(0b10000000 >> _Multiplex))); // clears the left display
	//shiftOut(datapin, clockpin, LSBFIRST, ~(h & ~(0b10000000 >> _Multiplex))); // clears the right display
	//shiftOut(datapin, clockpin, LSBFIRST, ~(hh & ~(0b10000000 >> _Multiplex))); // clears the left display

	//delay(1000);
}

void displayClock::setup(uint8_t _clockpin, uint8_t _latchpin,
		uint8_t _datapin) {

}

void displayClock::charlyplex595CathodeClock7Segment(uint8_t &_Multiplex,
		uint8_t &hh, uint8_t &h, uint8_t &mm, uint8_t &m) {

	m = (m & (0b10000000 >> _Multiplex));
	mm = (mm & (0b10000000 >> _Multiplex));
	h = (h & (0b10000000 >> _Multiplex));
	hh = (hh & (0b10000000 >> _Multiplex));

//	shiftOut(datapin, clockpin, LSBFIRST, (m & (0b10000000 >> _Multiplex))); // clears the right display
//	shiftOut(datapin, clockpin, LSBFIRST, (mm & (0b10000000 >> _Multiplex))); // clears the left display
//	shiftOut(datapin, clockpin, LSBFIRST, (h & (0b10000000 >> _Multiplex))); // clears the right display
//	shiftOut(datapin, clockpin, LSBFIRST, (hh & (0b10000000 >> _Multiplex))); // clears the left display

	//delay(1000);
}

//displayClock DisplayClock = displayClock();

//} /* namespace Display */
