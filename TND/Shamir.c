#include "header.h"

int obtentionDesPoints(CoordonneePoint coordonneesPoint[]){
	int nbPoints;

	do {
		printf("nombre de points necessaires au decryptage de la cle : ");
		scanf_s("%d", &nbPoints);
		getchar();
	} while (nbPoints < 0);

	for (int i = 0; i < nbPoints; i++) {
		printf("Entrez la coordonnee de x%d : ", i + 1);
		scanf_s("%lf", &coordonneesPoint[i].x);
		getchar();

		printf("Entrez la coordonnee de y%d : ", i + 1);
		scanf_s("%lf", &coordonneesPoint[i].y);
		getchar();
	}
	return nbPoints;
}

double fi(double x, int nbPoints, int i, CoordonneePoint coordonneesPoint[])
{
	double num = 1;
	double denum = 1;
	for (int j = 0; j<nbPoints; j++)
	{
		if (i != j)
		{
			num *= (x - coordonneesPoint[j].x);
			denum *= coordonneesPoint[i].x - coordonneesPoint[j].x;
		}
	}
	return num / denum;
}

void decrypteCleShamir()
{
	CoordonneePoint coordonnees[NBMAXPOINTS];
	int nbPoints = obtentionDesPoints(coordonnees);
	double res = P(0, nbPoints, coordonnees);
	printf("La cle de shamir est : ");
	afficheDecimales(res, 5);
	printf("\n");
}

double P(double x, int nbPoints, CoordonneePoint coordonneesPoint[]) {
	double res = 0;
	for (int i = 0; i < nbPoints; i++)
		res += coordonneesPoint[i].y * fi(x, nbPoints, i, coordonneesPoint);
	return res;
}

void calculeMaxPuissance(void) {
	CoordonneePoint coordonneesPoint[NBMAXPOINTS];
	int nbPoints = obtentionDesPoints(coordonneesPoint);
	double x;
	double Ymax = LONG_MIN;
	double Xmax = LONG_MIN;

	for (x = coordonneesPoint[0].x; x < coordonneesPoint[nbPoints - 1].x; x += INTERVALLE_RECHERCHE_MAX) {
		double res = P(x, nbPoints, coordonneesPoint);
		if (res > Ymax) {
			Ymax = res;
			Xmax = x;
		}
	}

	printf_s("Le maximum du polynome est : X = ");
	afficheDecimales(Xmax, 5);
	printf_s(", Y = ");
	afficheDecimales(Ymax, 5);
	printf_s("\n");
}
