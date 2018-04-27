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
		printf("Pour la precision, veuillez entre un nombre naturel de decimales : ");
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
	if (a != 0)
		argument = (x * log(a));
	else
		argument = 0;

	nbLimites = ((int)argument )/ LIMITE;
	if (argument < 0)
	{
		nbLimites *= -1;
		reste = argument + nbLimites*LIMITE;
	}
	else reste = argument - nbLimites * LIMITE;

	nbIterations = degre(nbDecimales, nbLimites,reste);
	res = resultat(reste, nbLimites, nbIterations);

	if (negatif)
		res = 1 / res;

	printf_s("Le resultat de ");
	afficheDecimales(a, nbDecimales);
	printf_s("^");
	afficheDecimales(x, nbDecimales);
	printf_s(" est : ");
	afficheDecimales(res, nbDecimales);
	printf_s("\n");
}

int degre(int nbDecimales, int nbLimites,double reste) {
	int nbIteration = 1;
	int niveauPrecision = LIMITE;
	for (int i = 0; i < expressionDuReste(nbDecimales,nbLimites,reste); i++)
	{
		niveauPrecision /= 10;
	}
	int diviseur = 1;
	int i = 0;
	double numerateur = LIMITE;
	while (numerateur/diviseur>niveauPrecision)
	{
		nbIteration++;
		numerateur = intPower(LIMITE,i);
		diviseur = factorielle(i+1);
		i++;
	}
	return nbIteration;
}

int expressionDuReste(int nbDecimales, int nbLimites,double reste) {
	if (reste != 0)
	{
	  nbLimites ++;
	}
	double argModif = nbLimites * LIMITE;
	return (int)(nbDecimales + (argModif-0.5)*0.5 + argModif / 5 + 0.31);
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
	
	if (reste == 0 && nbLimites == 0)
		return 0;

	for (i = 0; i < nbLimites; i++) {
		double limite = (reste < 0) ? limite = -LIMITE : LIMITE;
		double resultat = exponentielle(nbIterations, limite);
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
