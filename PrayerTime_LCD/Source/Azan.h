/*
 * Azan.h
 *
 *  Created on: Jan 2, 2014
 *      Author: M Hendra Herviawan
 */

#ifndef AZAN_H_
#define AZAN_H_

#include "main.h"
#include <Wire/Wire.h>
#include "DS1307RTC.h"

typedef uint8_t prayer_t;

#define Fajr	0
#define SunRise	1
#define Zuhr	2
#define Asr		3
#define Maghrib	4
#define Isha	5

const char PrayerString0 [] = "Fajr";
const char PrayerString1 [] = "SunRise";
const char PrayerString2 [] = "Zuhr";
const char PrayerString3 [] = "Asr";
const char PrayerString4 [] = "Mhrib";
const char PrayerString5 [] = "Isha";

const double ihtiyati = 0.034;
const time_t tommorow = 86400;
const double lintang = -6.91;
const double bujur = 107.61;
const int timezone = 7;
const double fajrTwilight = -20;
const double ishaTwilight = -18;

boolean alarm_status = false; //volatile
prayer_t nextPrayer = Fajr;

void globalAzanSetup();
void setsunRiseAlarm(time_t value);
void sunRiseAlarm();
void setFajrAlarm(time_t value);
void FajrAlarm();
void setZuhrAlarm(time_t value);
void ZuhrAlarm();
void setAsrAlarm(time_t value);
void AsrAlarm();
void setMaghribAlarm(time_t value);
void MaghribAlarm();
void setIshaAlarm(time_t value);
void IshaAlarm();
double getNextPrayer(time_t value);

void BUZZ();

/////////////////////////////////////////////////////////////////
void globalAzanSetup() {

	setTime(0,0,0,19,2,2014);
/*	setSyncProvider(RTC.get);   // the function to get the time from the RTC
	if (timeStatus() != timeSet)
		Serial.println(F("Unable to sync with the RTC"));
	else
		Serial.println(F("RTC has set the system time"));*/

	Alarm.freeAll();
	Alarm.alarmRepeat(0, 0, 0, globalAzanSetup);

	Serial.print(F("sunRise Time: "));
	setsunRiseAlarm(now());

	Serial.print(F("Fajar Time: "));
	setFajrAlarm(now());

	Serial.print(F("Zuhr Time: "));
	setZuhrAlarm(now());

	Serial.print(F("Asr Time: "));
	setAsrAlarm(now());

	Serial.print(F("Magrib Time: "));
	setMaghribAlarm(now());

	Serial.print(F("Isha Time: "));
	setIshaAlarm(now());

	nextPrayer = getNextPrayer(now());
}

void setsunRiseAlarm(time_t value) {
	double fajr, sunRise, zuhr, asr, maghrib, isha;
	//digitalDateDisplay(year(value), month(value), day(value));
	calcPrayerTimes(year(value), month(value), day(value), bujur, lintang,
			timezone, fajrTwilight, ishaTwilight, fajr, sunRise, zuhr, asr,
			maghrib, isha);

	uint8_t hours = 0, minutes = 0;
	fajr += ihtiyati;
	doubleToHrMin(sunRise, hours, minutes);
	Alarm.alarmOnce(hours, minutes, 0, sunRiseAlarm);
	serialClockDisplay(hours, minutes);
}

void sunRiseAlarm() {
	alarm_status = true;
	Serial.println(F("Waktu Sun Rise"));
	time_t Tommorow = now() + tommorow;
	setsunRiseAlarm(Tommorow);
	BUZZ();
	alarm_status = false;
	nextPrayer = Fajr;
}

void setFajrAlarm(time_t value) {
	double fajr, sunRise, zuhr, asr, maghrib, isha;
	//digitalDateDisplay(year(value), month(value), day(value));
	calcPrayerTimes(year(value), month(value), day(value), bujur, lintang,
			timezone, fajrTwilight, ishaTwilight, fajr, sunRise, zuhr, asr,
			maghrib, isha);

	uint8_t hours = 0, minutes = 0;
	fajr += ihtiyati;
	doubleToHrMin(fajr, hours, minutes);
	Alarm.alarmOnce(hours, minutes, 0, FajrAlarm);
	serialClockDisplay(hours, minutes);
}

void FajrAlarm() {
	alarm_status = true;
	Serial.println(F("Waktu Fajar"));
	time_t Tommorow = now() + tommorow;
	setFajrAlarm(Tommorow);
	BUZZ();
	alarm_status = false;
	nextPrayer = Zuhr;
}

void setZuhrAlarm(time_t value) {
	double fajr, sunRise, zuhr, asr, maghrib, isha;
	//digitalDateDisplay(year(value), month(value), day(value));
	calcPrayerTimes(year(value), month(value), day(value), bujur, lintang,
			timezone, fajrTwilight, ishaTwilight, fajr, sunRise, zuhr, asr,
			maghrib, isha);

	uint8_t hours, minutes;
	zuhr += ihtiyati;
	doubleToHrMin(zuhr, hours, minutes);
	Alarm.alarmOnce(hours, minutes, 0, ZuhrAlarm);
	serialClockDisplay(hours, minutes);
}

void ZuhrAlarm() {
	alarm_status = true;
	Serial.println(F("Waktu Zuhr"));
	time_t Tommorow = now() + tommorow;
	setZuhrAlarm(Tommorow);
	BUZZ();
	alarm_status = false;
	nextPrayer = Asr;
}

void setAsrAlarm(time_t value) {
	double fajr, sunRise, zuhr, asr, maghrib, isha;
	//digitalDateDisplay(year(value), month(value), day(value));
	calcPrayerTimes(year(value), month(value), day(value), bujur, lintang,
			timezone, fajrTwilight, ishaTwilight, fajr, sunRise, zuhr, asr,
			maghrib, isha);

	uint8_t hours, minutes;
	asr += ihtiyati;
	doubleToHrMin(asr, hours, minutes);
	Alarm.alarmOnce(hours, minutes, 0, AsrAlarm);
	serialClockDisplay(hours, minutes);
}

void AsrAlarm() {
	alarm_status = true;
	Serial.println(F("Waktu Asr"));
	time_t Tommorow = now() + tommorow;
	setAsrAlarm(Tommorow);
	BUZZ();
	alarm_status = false;
	nextPrayer = Maghrib;
}

void setMaghribAlarm(time_t value) {
	double fajr, sunRise, zuhr, asr, maghrib, isha;
	//digitalDateDisplay(year(value), month(value), day(value));
	calcPrayerTimes(year(value), month(value), day(value), bujur, lintang,
			timezone, fajrTwilight, ishaTwilight, fajr, sunRise, zuhr, asr,
			maghrib, isha);

	uint8_t hours, minutes;
	maghrib += ihtiyati;
	doubleToHrMin(maghrib, hours, minutes);
	Alarm.alarmOnce(hours, minutes, 0, MaghribAlarm);
	serialClockDisplay(hours, minutes);
}

void MaghribAlarm() {
	alarm_status = true;
	Serial.println(F("Waktu Maghrib"));
	time_t Tommorow = now() + tommorow;
	setMaghribAlarm(Tommorow);
	BUZZ();
	alarm_status = false;
	nextPrayer = Isha;
}

//Magrib
void setIshaAlarm(time_t value) {
	double fajr, sunRise, zuhr, asr, maghrib, isha;
	//digitalDateDisplay(year(value), month(value), day(value));
	calcPrayerTimes(year(value), month(value), day(value), bujur, lintang,
			timezone, fajrTwilight, ishaTwilight, fajr, sunRise, zuhr, asr,
			maghrib, isha);

	uint8_t hours = 0, minutes = 0;
	isha += ihtiyati;
	doubleToHrMin(isha, hours, minutes);
	Alarm.alarmOnce(hours, minutes, 0, IshaAlarm);
	serialClockDisplay(hours, minutes);
}

void IshaAlarm() {
	alarm_status = true;
	Serial.println(F("Waktu Isha"));
	time_t Tommorow = now() + tommorow;
	setIshaAlarm(Tommorow);
	BUZZ();
	alarm_status = false;
	nextPrayer = Fajr;
}

double getNextPrayer(time_t value){
	double hours = (double)(hour(value));
	hours += (double)((double)(minute(value)) * 0.0167);

	double fajr, sunRise, zuhr, asr, maghrib, isha;
	//digitalDateDisplay(year(value), month(value), day(value));
	calcPrayerTimes(year(value), month(value), day(value), bujur, lintang,
			timezone, fajrTwilight, ishaTwilight, fajr, sunRise, zuhr, asr,
			maghrib, isha);

	if (hours >= isha)
		return Fajr;

	//if (hours <= Fajr)
		//return SunRise;

	if (hours <= sunRise)
		return SunRise;

	if (hours <= zuhr)
		return Zuhr;

	if (hours <= asr)
		return Asr;

	if (hours <= maghrib)
		return Maghrib;

	if (hours <= isha)
		return Isha;

	return -1;
}

double getPrayerTime(prayer_t prayer, time_t value) {
	double fajr, sunRise, zuhr, asr, maghrib, isha;
	//digitalDateDisplay(year(value), month(value), day(value));
	calcPrayerTimes(year(value), month(value), day(value), bujur, lintang,
			timezone, fajrTwilight, ishaTwilight, fajr, sunRise, zuhr, asr,
			maghrib, isha);

	switch (prayer) {
	case Fajr:
		return fajr+ihtiyati;
	case SunRise:
		return sunRise+ihtiyati;
	case Zuhr:
		return zuhr+ihtiyati;
	case Asr:
		return asr+ihtiyati;
	case Maghrib:
		return maghrib+ihtiyati;
	case Isha:
		return isha+ihtiyati;
	}

	return 0.0; // prayer not defined
}

const char* getPrayerName(prayer_t prayer){

	switch (prayer) {
	case Fajr:
		return PrayerString0;
	case SunRise:
		return PrayerString1;
	case Zuhr:
		return PrayerString2;
	case Asr:
		return PrayerString3;
	case Maghrib:
		return PrayerString4;
	case Isha:
		return PrayerString5;
	}

	return "err";
}
#endif /* AZAN_H_ */
