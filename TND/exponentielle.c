#include "ax.h"

float exponentielle(int nbIterationsTaylor, float argument)
{
	float termeTotal = 1;
	int degreIteration;

	for (degreIteration = 1; degreIteration < nbIterationsTaylor; degreIteration++) {
		float terme = 1;
		int iteration = 0;

		for (int i = 0; i < iteration; i++)
		{
			terme *= argument;
		}

		float diviseur = factorielle(nbIterationsTaylor);
		termeTotal += terme / diviseur;
	}
	return termeTotal;
}
