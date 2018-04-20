#include "Shamir.h"


double fi(double x, int nbPoints,int i,CoordonneePoint coordonneesPoint[])
{
	double num = 1;
	double denum = 1;
	for(int i=0;i<nbPoints;i++)
	{
		if (i!=j)
		{
			num *= (x-coordonneesPoint[j].x));
			denum *= coordonneesPoint[i].x -coordonneesPoint[j].x);
		}
	}
	return num / denum;
}