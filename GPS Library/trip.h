#include "GPS.h"
#include "bearing.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#ifndef _TRIP_H_
#define _TRIP_H_

static const short int EARTH_RADIUS_MILES = 3959;
static const short int EARTH_RADIUS_KILOMETERS = 6371;

class trip : public gps
{
public:
	trip();
	trip(trip &t);
	trip(gps g1, gps g2);
	~trip();
	void calcdistance();
	void newCoordinates(gps g1, gps g2);
	gps getStart();
	gps getEnd();
	double getDistanceM();		//metric
	double getDistanceI();		//imperial
	bearing getInitialBearing();
	bearing getFinalBearing();
	
private:
	gps start;
	gps end;
	bearing binitial;
	bearing bfinal;
	double distanceM;
	double distanceI;
};



trip::trip()
{

}



trip::trip(trip &t)
{
	start = t.start;
	end = t.end;
	return;
}



trip::trip(const gps begin, const gps stop)
{
	start = begin;
	end = stop;
	calcdistance();

	return;
}



trip::~trip()
{

}



void trip::calcdistance()
{
	double a;
	double c;
	double delta_LAT;
	double delta_LONG;

	delta_LAT = (end.getLat() - start.getLat()) * M_PI / 360;
	delta_LONG = (end.getLong() - start.getLong()) * M_PI / 360;

	a = sin(delta_LAT)*sin(delta_LAT) + cos(start.getLat() * M_PI / 180 )
		* cos(end.getLat() * M_PI / 180) * sin(delta_LONG) * sin(delta_LONG);

	c = 2 * atan2(sqrt(a), sqrt(1 - a));

	distanceM = c * EARTH_RADIUS_KILOMETERS;
	distanceI = c * EARTH_RADIUS_MILES;
}



void trip::newCoordinates(gps g1, gps g2)
{
	start = g1;
	end = g2; 
	calcdistance();
}



gps trip::getStart()
{
	return start;
}



gps trip::getEnd()
{
	return end;
}



double trip::getDistanceM()		//metric
{
	return distanceM;
}



double trip::getDistanceI()		//imperial
{
	return distanceI;
}



bearing trip::getInitialBearing()
{
	return binitial;
}



bearing trip::getFinalBearing()
{
	return bfinal;
}
#endif