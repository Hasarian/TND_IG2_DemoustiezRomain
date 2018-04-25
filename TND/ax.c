#include "header.h"


void calculeExpBaseA(void) {
	bool negatif = false;
	double a;
	double x;
	int nbDecimales;
	double argument;
	int nbLimites;
	double reste;
	int nbIterations;
	double res;

	do {
		printf("Pour a^x -> veuillez entrer le a (positif) : ");
		scanf_s("%lf", &a);		// a ne peut pas �tre n�gatif
		vider();
	} while (a < 0);

	printf("Pour a^x -> veuillez entrer le x : ");
	scanf_s("%lf", &x);
	vider();

	if (x < 0) {
		x *= -1;
		negatif = true;
	}

	do {
		printf("Pour la pr�cision, veuillez entre un nombre positif de d�cimales : ");
		scanf_s("%d", &nbDecimales);
		vider();
	} while (nbDecimales < 0);

	argument = (x * log(a));

	nbLimites = (int)(argument / LIMITE);
	reste = argument - nbLimites * LIMITE;

	nbIterations = degre(nbDecimales, nbLimites);
	res = resultat(reste, nbLimites, nbIterations);

	if (negatif)
		res = 1 / res;

	afficheDecimales(res, nbDecimales);
	printf("\n");
}

int degre(int nbDecimales, int nbLimites) {
	double limiteAugment�e;
	int nbIteration = 1;
	int diviseur = 1;
	int nbIterationTaylor;
	bool limiteAcceptable;

	limiteAcceptable = false;
	while (!limiteAcceptable) {
		limiteAugment�e = 1;
		int iExposant;
		for (iExposant = 0; iExposant < nbIteration; iExposant++) {
			limiteAugment�e *= LIMITE;
		}
		nbIterationTaylor = (int)expressionDuReste(nbDecimales, nbLimites);
		diviseur = factorielle(nbIteration);
		limiteAcceptable = limiteAugment�e / diviseur > LIMITE * intPower(10, -(nbIterationTaylor + 1));
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
