#include "Tokenizer.h"
#include <iostream>
#include <algorithm>


#ifndef _GPS_H_
#define _GPS_H_

class gps
{
public: 
	gps();
	gps(const gps &g);
	~gps();
	double midpoint(const gps g1, const gps g2, gps &g3);
	void print();
	void enterCoordinates(bool default_Prompts);
	void parseCoordinates(string s);
	double getLat();
	double getLong();

private:
	double point_LAT;
	double point_LONG;
};



gps::gps()
{
	point_LAT = 0.0;
	point_LONG = 0.0;
}



gps::gps(const gps &g)
{
	point_LAT = g.point_LAT;
	point_LONG = g.point_LONG;
}



gps::~gps()
{

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
	Tokenizer t(s, ' ');		//initializing this tokenizes


	transform(s.begin(), s.end(), s.begin(), toupper);

	temp = t.next();

	if (temp.find(".") == string::npos)
	{
		//translates lateral coordinate inputs to integers and floats
		deg_LAT = stoi(temp);
		min_LAT = stoi(t.next());
		temp = t.next();
		if (temp.back() == 'S')
			neg_LAT = true;
		temp.pop_back();
		sec_LAT = stof(temp);

		//translates longitudinal coordinate inputs to integers and floats
		deg_LONG = stoi(t.next());
		min_LONG = stoi(t.next());
		temp = t.next();
		if (temp.back() == 'W')
			neg_LONG = true;
		temp.pop_back();
		sec_LONG = stof(temp);

		//converts degree, minute, second coordinate to decimal degree coordinate
		point_LAT = (double)deg_LAT + (double)min_LAT / 60
			+ (double)sec_LAT / 3600;
		point_LONG = (double)deg_LONG + (double)min_LONG / 60
			+ (double)sec_LONG / 3600;

		//Changes sign of coordinates based on hemispheres
		if (neg_LAT)
			point_LAT = point_LAT*-1;
		if (neg_LONG)
			point_LONG = point_LONG*-1;

		cout << point_LAT << '\t' << point_LONG << endl;
	}
	else
	{
		//Assignes decimal degree coordinate data to variables
		point_LAT = stoi(temp);
		point_LONG = stoi(t.next());
	}

	return;
}



double gps::getLat()
{
	return point_LAT;
}



double gps::getLong()
{
	return point_LONG;
}

#endif

