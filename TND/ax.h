#pragma once
#include <stdio.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#define LIMITE 0.5

/*Alex*/
double exponentielle(int nbIterationsTaylor, double argument);
double intPower(double argument, int nbIterations);
double resultat(double reste, int nbLimites, int nbIterations);

/*Sam*/
void vider(void);
int degre(int nbDecimales, int nbLimites);
double expressionDuReste(int nbDecimales, int nbLimites);
int factorielle(int nbIteration);
