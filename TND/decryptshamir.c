#include "Shamir.h"

double dercyptageShamir()
{
	CoordonneePoint coordonnees[NBMAXPOINTS];
	int nbPoints=obtentionDesPoints(coordonnees);
	return P(0,nbPoints,coordonnees);
	
}