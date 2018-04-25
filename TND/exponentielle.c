#include "header.h"

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
