 #include <stdio.h>
 #include <stdlib.h>
#define NBMAXPOINTS 30

typedef struct coordonneePoint CoordonneePoint;
struct coordonneePoint
{
	double x;
	double y;
};

double fi(double x, int nbPoints, int i, CoordonneePoint coordonneesPoint[]);
int obtentionDesPoints(CoordonneePoint coordonneesPoint[]);
double P(double x, int nbPoints, CoordonneePoint coordonneesPoint[]);