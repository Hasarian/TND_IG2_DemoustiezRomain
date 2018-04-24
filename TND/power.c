﻿#include "ax.h"

/*
void main(void) {
	// test de factorielle
	int valeurTest;
	int valeurRetour;

	printf(" test factorielle -> veuillez entrer une valeur : ");
	scanf_s("%d", &valeurTest);		// a ne peut pas être négatif
	vider();

	valeurRetour = factorielle(valeurTest);

	printf(" test factorielle -> valeur de retour : %d", valeurRetour);
	getchar();

}
*/

//void main(void) {
//	bool negatif = false;
//	double a;	
//	double x;
//	int nbDecimales;
//	double argument;
//	int nbLimites;
//	double reste;
<<<<<<< HEAD
=======
//	int nbIterations;
//	double res;
>>>>>>> 9f61685b938f9d360309e4426ba3fca37474ccac
//
//	do {
//		printf("Pour a^x -> veuillez entrer le a : ");
//		scanf_s("%ld", &a);		// a ne peut pas être négatif
//		vider();
//	} while (a < 0);
//
//	printf("Pour a^x -> veuillez entrer le x : ");
//	scanf_s("%ld", &x);
//	vider();
//
//	if (x < 0) {
<<<<<<< HEAD
//		x *= 1;
=======
//		x *= -1;
>>>>>>> 9f61685b938f9d360309e4426ba3fca37474ccac
//		negatif = true;
//	}
//
//	do {
//		printf("Pour la précision, veuillez entre un nombre positif de décimales : ");
//		scanf_s("%d", &nbDecimales);
//		vider();
//	} while (nbDecimales < 0);
//
//	argument = x * log(a);
//
//	nbLimites = (int)argument / LIMITE;
//	reste = argument - nbLimites * LIMITE;
//
<<<<<<< HEAD
//	int nbIterations = degre(nbDecimales, nbLimites);
//	double res = resultat(reste, nbLimites, nbIterations);
=======
//	nbIterations = degre(nbDecimales, nbLimites);
//	res = resultat(reste, nbLimites, nbIterations);
>>>>>>> 9f61685b938f9d360309e4426ba3fca37474ccac
//
//	if (negatif)
//		res = 1 / res;
//
//	printf("Resultat : %.5lf", res);
//
//}

int degre(int nbDecimales, int nbLimites) {
	double limiteAugmentée;
	int nbIteration = 1;
	int diviseur = 1; 
	int nbIterationTaylor;
	bool limiteAcceptable;
	
	limiteAugmentée = 2 * (0, 5 ^ (nbIteration + 1));
	limiteAcceptable = limiteAugmentée / diviseur > LIMITE * intPower(10, -nbDecimales);
	while (!limiteAcceptable) {
		limiteAugmentée = 1;
		int iExposant;
		for (iExposant = 0; iExposant < nbIteration; iExposant++) {
			limiteAugmentée *= LIMITE;
		}
		nbIterationTaylor = (int)expressionDuReste(nbDecimales, nbLimites);
		diviseur = factorielle(nbIteration);
		limiteAcceptable = limiteAugmentée / diviseur > LIMITE * intPower(10, -(nbIterationTaylor+1));
		if (!limiteAcceptable) {
			nbIteration++;
		}
	}
	return nbIteration;
}

double expressionDuReste(int nbDecimales, int nbLimites) {

	return nbDecimales + nbLimites*LIMITE*0.5 + (nbLimites + 1)*LIMITE / 5 + 0.31;
}

int factorielle(int nbIteration) {
	if (nbIteration < 1)
		return 1;
	return nbIteration * factorielle(nbIteration - 1);
}

void vider(void) {
	int c;
	do {
		c = getchar();
	} while (c != '\n' && c != EOF);
}