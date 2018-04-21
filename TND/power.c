#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define LIMITE 0.5

void vider(void);
void degre(void);
void resultat(void);


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

	degre();
	resultat();

	if (negatif)
		resultat = 1 / resultat;

	printf("Resultat : %.5lf", resultat);

}


void degré(void) {
	int nbIteration = 1;
	double limiteAcceptable;


}

void vider(void) {
	int c;
	do {
		c = getchar();
	} while (c != '\n' && c != EOF);
}