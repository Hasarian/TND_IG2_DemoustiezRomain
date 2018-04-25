#define NBMAXPOINTS 30
#define INTERVALLE_RECHERCHE_MAX 0.00001

typedef struct coordonneePoint CoordonneePoint;
struct coordonneePoint
{
	double x;
	double y;
};

double fi(double x, int nbPoints, int i, CoordonneePoint coordonneesPoint[]);
void decrypteCleShamir();

// Samy
int obtentionDesPoints(CoordonneePoint coordonneesPoint[]);
double P(double x, int nbPoints, CoordonneePoint coordonneesPoint[]);
void calculeMaxPuissance(void);