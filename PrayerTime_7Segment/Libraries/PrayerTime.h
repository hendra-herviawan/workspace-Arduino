#include <math.h>
#include <arduino.h>
//convert Degree to Radian
double degToRad(double degree) {
	double x = (3.1415926 / 180.0);
	x = x * degree;
	//Serial.println(x);
	//cout << x << endl;
	return (x);
}

//convert Radian to Degree
double radToDeg(double radian) {
	double x = (180.0 / 3.1415926);
	x = radian * x;
	//cout << x << endl;
	return (x);
}

//make sure a value is between 0 and 360
double moreLess360(double value) {
	while (value > 360.0 || value < 0.0) {
		if (value > 360.0)
			value -= 360.0;

		else if (value < 0)
			value += 360.0;
	}

	return value;
}

//make sure a value is between 0 and 24
double moreLess24(double value) {
	while (value > 24.0 || value < 0.0) {
		if (value > 24.0)
			value -= 24.0;

		else if (value < 0)
			value += 24.0;
	}

	return value;
}

//convert the double number to Hours and Minutes
void doubleToHrMin(double number, uint8_t &hours, uint8_t &minutes) {
	hours = floor(moreLess24(number));
	minutes = floor(moreLess24(number - hours) * 60);
}

void calcPrayerTimes(int year, int month, int day, double longitude,
		double latitude, int timeZone, double fajrTwilight, double ishaTwilight,
		double &fajrTime, double &sunRiseTime, double &zuhrTime,
		double &asrTime, double &maghribTime, double &ishaTime) {

	double D = (367.0 * year) - ((year + (int) ((month + 9.0) / 12.0)) * 7.0 / 4.0);
	double D1 = (((int) (275.0 * month / 9.0)) + day - 730531.5);

	D += D1;

	double L = 280.461 + 0.9856474 * D;
	L = moreLess360(L);

	double M = 357.528 + (0.9856003) * D;
	M = moreLess360(M);

	double Lambda = L + 1.915 * sin(degToRad(M)) + 0.02 * sin(degToRad(2 * M));
	Lambda = moreLess360(Lambda);

	double Obliquity = 23.439 - 0.0000004 * D;
	double Alpha = radToDeg(
			atan((cos(degToRad(Obliquity)) * tan(degToRad(Lambda)))));
	Alpha = moreLess360(Alpha);

	Alpha = Alpha - (360.0 * (int) (Alpha / 360.0));
	Alpha = Alpha + 90.0 * (floor(Lambda / 90.0) - floor(Alpha / 90.0));

	double ST = 100.46 + 0.985647352 * D;
	double Dec = radToDeg(
			asin(sin(degToRad(Obliquity)) * sin(degToRad(Lambda))));
	double Durinal_Arc = radToDeg(
			acos(
					(sin(degToRad(-0.8333))
							- sin(degToRad(Dec)) * sin(degToRad(latitude)))
							/ (cos(degToRad(Dec)) * cos(degToRad(latitude)))));

	double Noon = Alpha - ST;
	Noon = moreLess360(Noon);

	double UT_Noon = Noon - longitude;

	////////////////////////////////////////////
	// Calculating Prayer Times Arcs & Times //
	//////////////////////////////////////////

	// 2) Zuhr Time [Local noon]
	zuhrTime = UT_Noon / 15.0 + timeZone;

	// Asr Hanafi
	//double Asr_Alt =radToDeg(atan(2+tan(degToRad(latitude - Dec))));

	// Asr Shafii
	double Asr_Alt = radToDeg(atan(1 + tan(degToRad(latitude - Dec))));
	double Asr_Arc = radToDeg(
			acos(
					(sin(degToRad(90 - Asr_Alt))
							- sin(degToRad(Dec)) * sin(degToRad(latitude)))
							/ (cos(degToRad(Dec)) * cos(degToRad(latitude)))));
	Asr_Arc = Asr_Arc / 15.0;

	asrTime = zuhrTime + Asr_Arc;

	// 1) Shorouq Time
	sunRiseTime = zuhrTime - (Durinal_Arc / 15.0);

	// 4) Maghrib Time
	maghribTime = zuhrTime + (Durinal_Arc / 15.0);

	// 5) Isha Time
	double Esha_Arc = radToDeg(
			acos(
					(sin(degToRad(ishaTwilight))
							- sin(degToRad(Dec)) * sin(degToRad(latitude)))
							/ (cos(degToRad(Dec)) * cos(degToRad(latitude)))));
	ishaTime = zuhrTime + (Esha_Arc / 15.0);

	// 0) Fajr Time
	double Fajr_Arc = radToDeg(
			acos(
					(sin(degToRad(fajrTwilight))
							- sin(degToRad(Dec)) * sin(degToRad(latitude)))
							/ (cos(degToRad(Dec)) * cos(degToRad(latitude)))));
	fajrTime = zuhrTime - (Fajr_Arc / 15.0);

	return;
}
