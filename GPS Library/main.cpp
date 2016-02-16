#include "trip.h"


int main()
{
	gps g1;
	gps g2;
	trip t;
	
	g1.enterCoordinates(true);
	g2.enterCoordinates(true);

	t.newCoordinates(g1, g2);

	cout << t.getDistanceM() << endl;
	return 0;

}