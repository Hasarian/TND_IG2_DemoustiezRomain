#include "Shamir.h"

int obtentionDesPoints(CoordonneePoint coordonneesPoint[]) {

	int nbPoints;

	do {
		printf("nombre de points necessaires au decryptage de la cle : ");
		scanf_s("%d", &nbPoints);
		getchar();
	} while (nbPoints < 0);

	for (int i = 0; i < nbPoints; i++) {
		printf("Entrez la coordonnee de X pour le point %d : ", i + 1);
		scanf_s("%lf", &coordonneesPoint[i].x);
		getchar();

		printf("Entrez la coordonnee de Y pour le point %d : ", i + 1);
		scanf_s("%lf", &coordonneesPoint[i].y);
		getchar();
	}
	return nbPoints;
}

//double P(double x, int nbPoints, CoordonneePoint coordonneesPoint[]) {
//	double res = 0;
//	for (int i = 0; i < nbPoints; i++)
//		res += coordonneesPoint[i].y * fi(x, nbPoints, i, coordonneesPoint);
//	return res;
//}


void main(void) {
// test obtention des points
	int nbPoints;
	double x = 0;
	CoordonneePoint coordonneesPoints[10]; // max ??
	
	nbPoints = obtentionDesPoints(coordonneesPoints);

	for (int i = 0; i < nbPoints; i++) {

		printf("la coordonnee de X pour le point %d : %.lf\n", i + 1, coordonneesPoints[i].x);
		printf("la coordonnee de Y pour le point %d : %.lf\n", i + 1, coordonneesPoints[i].y);

		getchar();
	}

}
