#include "header.h"

double obtenirA() {
	double a;

	do {
		printf("Pour a^x -> veuillez entrer le a (positif) : ");
		scanf_s("%lf", &a);		// a ne peut pas être négatif
		vider();
	} while (a < 0);

	return a;
}

double obtenirX() {
	double x;

	printf("Pour a^x -> veuillez entrer le x : ");
	scanf_s("%lf", &x);
	vider();

	return x;
}

int obtenirPrecision() {
	int nbDecimales;

	do {
		printf("Pour la précision, veuillez entre un nombre positif de décimales : ");
		scanf_s("%d", &nbDecimales);
		vider();
	} while (nbDecimales < 0);

	return nbDecimales;
}

void calculeExpBaseA(void) {
	bool negatif = false;
	double a;
	double x;
	double argument;
	double reste;
	double res;
	int nbDecimales;
	int nbLimites;
	int nbIterations;

	a = obtenirA();
	x = obtenirX();

	if (x < 0) {
		x *= -1;
		negatif = true;
	}

	nbDecimales = obtenirPrecision();
	argument = (x * log(a));

	nbLimites = (int)(argument / LIMITE);
	reste = argument - nbLimites * LIMITE;

	nbIterations = degre(nbDecimales, nbLimites);
	res = resultat(reste, nbLimites, nbIterations);

	if (negatif)
		res = 1 / res;

	afficheDecimales(res, nbDecimales);
	printf_s("\n");
}

int degre(int nbDecimales, int nbLimites) {
	double limiteAugmentée;
	int nbIteration = 1;
	int diviseur = 1;
	int nbIterationTaylor;
	bool limiteAcceptable;

	limiteAcceptable = false;
	while (!limiteAcceptable) {
		limiteAugmentée = 1;
		int iExposant;
		for (iExposant = 0; iExposant < nbIteration; iExposant++) {
			limiteAugmentée *= LIMITE;
		}
		nbIterationTaylor = (int)expressionDuReste(nbDecimales, nbLimites);
		diviseur = factorielle(nbIteration);
		limiteAcceptable = limiteAugmentée / diviseur > LIMITE * intPower(10, -(nbIterationTaylor + 1));
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

double resultat(double reste, int nbLimites, int nbIterations) {
	int i;
	double terme = 1;
	for (i = 0; i < nbLimites; i++) {
		double resultat = exponentielle(nbIterations, LIMITE);
		terme *= resultat;
	}

	double resultat = exponentielle(nbIterations, reste);
	terme *= resultat;
	return terme;
}

double intPower(double argument, int nbIterations) {
	double terme = 1;
	for (int i = 0; i < nbIterations; i++)
	{
		terme *= argument;
	}

	return terme;
}

double exponentielle(int nbIterationsTaylor, double argument)
{
	double termeTotal = 0;
	for (int i = 0; i < nbIterationsTaylor; i++)
	{
		double petitTerme = intPower(argument, i);
		petitTerme /= factorielle(i);
		termeTotal += petitTerme;
	}
	return termeTotal;
}
