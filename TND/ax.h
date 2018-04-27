#pragma once
#define LIMITE 0.5

double obtenirA();
double obtenirX();
/*Alex*/
double exponentielle(int nbIterationsTaylor, double argument);
double intPower(double argument, int nbIterations);
double resultat(double reste, int nbLimites, int nbIterations);

/*Sam*/
void vider(void);
int degre(int nbDecimales, int nbLimites,double reste);
int expressionDuReste(int nbDecimales, int nbLimites,double reste);
int factorielle(int nbIteration);
void calculeExpBaseA(void);