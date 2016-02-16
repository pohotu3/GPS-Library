#include <iostream>

#ifndef _BEARING_H_
#define _BEARING_H_

class bearing
{
public:
	bearing();
	bearing(bearing &b);
	~bearing();
	void setBearing(int degrees, int minutes, float seconds);
	void print();
	int getDegrees();
	int getMinutes();
	float getSeconds();
private:
	int degrees;
	int minutes;
	float seconds;
};

bearing::bearing()
{
	degrees = 0;
	minutes = 0;
	seconds = 0.0;
	return;
}



bearing::bearing(bearing &b)
{
	degrees = b.degrees;
	minutes = b.minutes;
	seconds = b.seconds;
	return;
}



bearing::~bearing()
{}



void bearing::setBearing(int deg, int min, float sec)
{
	degrees = deg;
	minutes = min;
	seconds = sec;
	return;
}



void bearing::print()
{
	std::cout << degrees << " degrees\t" << minutes << "minutes\t" << seconds
		<< "seconds\n";
	return;
}



int bearing::getDegrees()
{
	return degrees;
}



int bearing::getMinutes()
{
	return minutes;
}



float bearing::getSeconds()
{
	return seconds;
}
#endif