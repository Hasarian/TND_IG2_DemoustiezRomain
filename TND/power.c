#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define LIMITE 0.5

void vider(void);
void degré(double limiteAugmentée, int nbDecimales, int nbLimites);
void resultat(void);
double expressionDuReste(int nbDecimales, int nbLimites);
int factorielle(int nbIteration);

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

void main(void) {
	bool negatif = false;
	double a;	
	double x;
	int nbDecimales;
	double argument;
	int nbLimites;
	double reste;

	do {
		printf("Pour a^x -> veuillez entrer le a : ");
		scanf_s("%.5lf", &a);		// a ne peut pas être négatif
		vider();
	} while (a < 0);

	printf("Pour a^x -> veuillez entrer le x : ");
	scanf_s("%.5lf", &x);
	vider();

	if (x < 0) {
		x *= 1;
		negatif = true;
	}

	do {
		printf("Pour la précision, veuillez entre un nombre positif de décimales : ");
		scanf_s("%d", &nbDecimales);
		vider();
	} while (nbDecimales < 0);

	argument = x * log(a);

	nbLimites = (int)argument / LIMITE;
	reste = argument - nbLimites * LIMITE;

	degre(limiteAugmentée, nbDecimales, nbLimites);
	resultat();

	if (negatif)
		resultat = 1 / resultat;

	printf("Resultat : %.5lf", resultat);

}


void degré(double limiteAugmentée, int nbDecimales, int nbLimites) {
	int nbIteration = 1;
	int diviseur = 1;  // ???
	bool limiteAcceptable;
	double nbIterationTaylor; // ??? 

	limiteAcceptable = limiteAugmentée / diviseur > LIMITE * pow(10, -nbDecimales);
	while (!limiteAcceptable) {
		limiteAugmentée = 1;
		int iExposant = 0;
		while (iExposant < nbIteration) {
			limiteAugmentée *= LIMITE;
			iExposant++;
		}
		nbIterationTaylor = expressionDuReste(nbDecimales, nbLimites);
		diviseur = factorielle(nbIteration);
		limiteAcceptable = limiteAugmentée / diviseur > LIMITE * pow(10, -nbDecimales);
		if (!limiteAcceptable) {
			nbIteration++;
		}
	}
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