 #include <stdio.h>
 #include <stdlib.h>
#define NBMAXPOINTS 30

typedef struct coordonneePoint CoordonneePoint;
struct coordonneePoint
{
	double x;
	double y;
	CoordonneePoint*pSuiv;
};

double fi(double x, int nbPoints, int i, CoordonneePoint coordonneesPoint, CoordonneePoint*pCoordonnées);