#include "GPS.h"

#ifndef _TRIP_H_
#define _TRIP_H_

class trip : public gps
{
public:
	trip();
	trip(trip &t);
	~trip();
	void distance();
private:
	gps start;
	gps end;

};

#endif