#include "ax.h"

//int main(int argc, char *argv[]) {
//	
//}

double degré() {
	int nbIteration = 1;
	double limiteAugmentée = 2 * intPower(0.5, nbIteration + 1);
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
