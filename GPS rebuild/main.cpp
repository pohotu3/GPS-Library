#pragma once
#include "GPS.h"
#include <iostream>


int main()
{
	gps g1;
	gps g2;
	
	g1.enterCoordinates(true);
	g2.enterCoordinates(true);

	cout << g1.distance(g1, g2, true) << endl;
	return 1;

}