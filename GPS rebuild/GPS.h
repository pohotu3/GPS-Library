#pragma once
#include "Tokenizer.h"
#include <iostream>
#include <algorithm>


#ifndef _GPS_H_
#define _GPS_H_

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

static const short int EARTH_RADIUS_MILES = 3959;
static const short int EARTH_RADIUS_KILOMETERS = 6371;
static const bool DEBUG_MESSAGES = true;

class gps
{
public:
	gps();
	gps(gps &g);
	~gps();
	double distance(const gps g1, const gps g2, bool metric);
	void enterCoordinates(bool default_Prompts);
	void parseCoordinates(string s);
	void rad();


private:
	double point_LAT;
	double point_LONG;
	double rad_LAT;
	double rad_LONG;
};



gps::gps()
{
	point_LAT = 0.0;
	point_LONG = 0.0;
	rad_LAT = 0.0;
	rad_LONG = 0.0;
}



gps::gps(gps &g)
{
	point_LAT = g.point_LAT;
	point_LONG = g.point_LONG;
	rad_LAT = g.rad_LAT;
	rad_LONG = g.rad_LONG;
}



gps::~gps()
{

}



double gps::distance(const gps g1, const gps g2, bool metric)
{
	double a;
	double c;
	double delta_LAT;
	double delta_LONG;

	delta_LAT = (g2.point_LAT - g1.point_LAT) * M_PI / 360;
	delta_LONG = (g2.point_LONG + g1.point_LONG) * M_PI / 360;

	a = sin(delta_LAT)*sin(delta_LAT) + cos(g1.rad_LAT)*cos(g2.rad_LAT)*
		sin(delta_LONG)*sin(delta_LONG);

	c = 2 * atan2(sqrt(a), sqrt(1 - a));

	if (metric)
		return c * EARTH_RADIUS_KILOMETERS;
	else
		return c * EARTH_RADIUS_MILES;
}



void gps::enterCoordinates(bool default_Prompts)
{
	string parse;

	if (default_Prompts)
	{
		cout << "Enter a pair of lateral and longitudinal coordinates" << endl;
		cout << "Format: " << endl << endl;
		cout << "xx.xxxx xx.xxxx\n\t\tOR\nxx xx xxD xx xx xxD" << endl;
	}

	getline(cin, parse);

	parseCoordinates(parse);

	rad();

	return;
}



void gps::parseCoordinates(string s)
{
	bool neg_LAT = false;
	bool neg_LONG = false;
	int deg_LAT = 0;
	int deg_LONG = 0;
	int min_LAT = 0;
	int min_LONG = 0;
	float sec_LAT = 0.0;
	float sec_LONG = 0.0;
	string temp;
	Tokenizer t(s, ' ');


	transform(s.begin(), s.end(), s.begin(), toupper);

	temp = t.next();

	if (temp.find(".") == string::npos)
	{
		//format xx xx xxD xx xx xxD
		deg_LAT = stoi(temp);
		min_LAT = stoi(t.next());
		temp = t.next();
		if (temp.back() == 'S')
			neg_LAT = true;
		temp.pop_back();
		sec_LAT = stof(temp);
		deg_LONG = stoi(t.next());
		min_LONG = stoi(t.next());
		temp = t.next();
		if (temp.back() == 'W')
			neg_LONG = true;
		temp.pop_back();
		sec_LONG = stof(temp);

		if (DEBUG_MESSAGES)
		{
			cout << deg_LAT << '\t' << min_LAT << '\t' << sec_LAT << '\t';
			if (neg_LAT)
				cout << 'S' << endl;
			else
				cout << 'N' << endl;
			cout << deg_LONG << '\t' << min_LONG << '\t' << sec_LONG << '\t';
			if (neg_LONG)
				cout << 'W' << endl;
			else
				cout << 'E' << endl;
		}
		point_LAT = (double)deg_LAT + (double)min_LAT / 60
			+ (double)sec_LAT / 3600;
		point_LONG = (double)deg_LONG + (double)min_LONG / 60
			+ (double)sec_LONG / 3600;

		if (neg_LAT)
			point_LAT = point_LAT*-1;
		if (neg_LONG)
			point_LONG = point_LONG*-1;

		cout << point_LAT << '\t' << point_LONG << endl;
	}
	else
	{
		//format xx.xxxx xx.xxxx
		point_LAT = stoi(temp);
		point_LONG = stoi(t.next());
	}

	return;
}



void gps::rad()
{
	rad_LAT = point_LAT* M_PI / 180;
	rad_LONG = point_LONG* M_PI / 180;
	return;
}
#endif

