#include "ax.h"

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
	double termeTotal = 1;
	int degreIteration;

	for (degreIteration = 1; degreIteration < nbIterationsTaylor; degreIteration++) {
		double terme;
		int iteration = 0;

		terme = intPower(argument, degreIteration);

		float diviseur = factorielle(nbIterationsTaylor);
		termeTotal += terme / diviseur;
	}
	return termeTotal;
}
