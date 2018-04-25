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

double P(double x, int nbPoints, CoordonneePoint coordonneesPoint[]) {
	double res = 0;
	for (int i = 0; i < nbPoints; i++)
		res += coordonneesPoint[i].y * fi(x, nbPoints, i, coordonneesPoint);
	return res;
}

void calculeMaxPolynomeLagrange(void) {
	CoordonneePoint coordonneesPoint[NBMAXPOINTS];
	int nbPoints = obtentionDesPoints(coordonneesPoint);
	double intervalle = 0.01;
	double x = coordonneesPoint[0].x;
	double Ymax = LONG_MIN; 
	double Xmax = LONG_MIN;

	for (int i = 0; x < coordonneesPoint[nbPoints - 1].x; i++) {
		double res = P(x, nbPoints, coordonneesPoint); // x = i ???
		if (res > Ymax) {
			Ymax = res;
			Xmax = x;
		}
		x += intervalle;
	}
	printf("Xmax vaut %lf et Ymax vaut %lf", Xmax, Ymax);
}

/*void main(void) {
//// test obtention des points
//	int nbPoints;
//	double x = 1;
//	CoordonneePoint coordonneesPoints[10]; 
//	
//	nbPoints = obtentionDesPoints(coordonneesPoints);
//	double retourP;
//	
//// test obtention de P (modifier la valeur de x)
//	retourP = P(x, nbPoints, coordonneesPoints);
//	printf("retour P : %.10lf", retourP);
//	getchar();

// test calculeMaxPolynomeLagrange
	calculeMaxPolynomeLagrange();
	getchar();
}*/
