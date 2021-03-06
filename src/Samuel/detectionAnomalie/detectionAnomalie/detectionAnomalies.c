#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NBLIGNES 26
#define NBCOLONNES 10
#define NBELEMS 38.0

typedef double(*ptrFonction)(int);


void vider(void);
void constructionTableNormale(int nbPts, ptrFonction ptr);
double rechercherZ(double alpha, double tab[][NBCOLONNES]);
void intervalle(double moyenne, double variance, double n, double alpha, double *intervalleInf, double *intervalleSup);
double simpson(int nbPts);

void main(void) {
	//double (*ptrFonction) (int);
	int nbPts; // pour pr�cision lors de la cr�ation du tableau
	double alphaControle;
	double alphaSurveillance;
	int sumXi = 0;
	int sumXiSquare = 0;
	double moyenne;
	double variance;
	double coefficentAlphaControle;
	double coefficentAlphaSurveillance;
	double intervalleInfControle;
	double intervalleSupControle;
	double intervalleInfSurveillance;
	double intervalleSupSurveillance;


	constructionTableNormale(49, simpson);

	
	double tabNormal[NBLIGNES][NBCOLONNES] = {
		{ 5000, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
		{ 5396, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
		{ 5793, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
		{ 6179, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
		{ 6554, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
		{ 6815, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
		{ 7257, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
		{ 7580, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
		{ 7881, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
		{ 8159, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
		{ 8413, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
		{ 8643, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
		{ 8849, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
		{ 9032, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
		{ 9132, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
		{ 9332, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
		{ 9452, 9463, 9474, 9484, 9495, 9505, 9515, 9525, 9535, 9545 },
		{ 9554, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
		{ 9641, 9649, 9656, 9664, 9671, 9678, 9786, 9693, 9699, 9706},
		{ 9713, 9719, 9726, 9732, 9738, 9744, 9750, 9756, 9761, 9767},
		{ 9772, 9778, 9783, 9788, 9793, 9798, 9803, 9808, 9812, 9817},
		{ 9821, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
		{ 9861, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
		{ 9893, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
		{ 9918, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
		{ 9938, 9940, 9941, 9943, 9945, 9946, 9948, 9949, 9951, 9952 },
	};
	int tabData[] = {20,20,20,20,20,20,20,20,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,60,60,60,60,60,60,60,60,60,60,60,60,80,80 };
	printf("Bienvenus pour un calcule de detection d'anomalie dans un echantillon\n");
	printf("---------------------------------------------------------------------\n\n");
	
	printf("Veuillez entrer le nombre de points pour le niveau de pr�cision de la table : ");
	scanf_s("%d", &nbPts);
	vider();

	printf("Veuillez entrer un pourcentage d insertitude de controle : ");
	scanf_s("%lf", &alphaControle);
	vider();

	printf("Veuillez entrer un pourcentage d insertitude de surveillance : ");
	scanf_s("%lf", &alphaSurveillance);
	vider();

	int i = 0;
	while (i < NBELEMS) {
		sumXi += tabData[i];
		sumXiSquare += (tabData[i] * tabData[i]);
		i++;
	}

	printf("Somme xi = %d\n", sumXi);
	printf("Somme xiCarre = %d\n", sumXiSquare);

	moyenne = sumXi / NBELEMS;
	printf("Moyenne = %.5lf\n", moyenne);

	variance = sumXiSquare / NBELEMS - moyenne * moyenne;
	printf("Variance = %.5lf\n", variance);			

	coefficentAlphaControle = rechercherZ(alphaControle, tabNormal);
	printf("coefficentAlpha = %.5lf\n", coefficentAlphaControle);

	intervalle(moyenne, variance, NBELEMS, coefficentAlphaControle, &intervalleInfControle, &intervalleSupControle);

	printf("L'intervalle de controle se trouve dans la tranche %.2lf et %.2lf\n\n", intervalleInfControle, intervalleSupControle);

	coefficentAlphaSurveillance = rechercherZ(alphaSurveillance, tabNormal);
	printf("coefficentAlpha = %.5lf\n", coefficentAlphaSurveillance);

	intervalle(moyenne, variance, NBELEMS, coefficentAlphaSurveillance, &intervalleInfSurveillance, &intervalleSupSurveillance);

	printf("L'intervalle de surveillance se trouve dans la tranche %.2lf et %.2lf\n\n", intervalleInfSurveillance, intervalleSupSurveillance);

	system("pause");
}

void vider(void) {
	int c;
	do {
		c = getchar();
	} while (c != '\n' && c != EOF);
}

double rechercherZ(double alpha, double tab[][NBCOLONNES]) {
	double zoneNormaliser;
	double interpolation = 0;

	zoneNormaliser = (1. - (alpha / 200.))*10000;
	printf("\nzoneNormaliser = %.5lf", zoneNormaliser/10000);

	int iLigne = 0;
	while (iLigne < NBLIGNES -1 && tab[iLigne + 1][0] <= zoneNormaliser) {
		iLigne++;
	}
	
	int iColonne = 0;
	while (iColonne < 9 && tab[iLigne][iColonne + 1] <= zoneNormaliser)
		iColonne++;
	if (tab[iLigne][iColonne] != zoneNormaliser) {
		int iLigneBord = iLigne;
		int iColonneBord = iColonne + 1;
		if (iColonne == NBCOLONNES - 1 && tab[iLigne][iColonne] < zoneNormaliser) {
			iLigneBord = iLigne + 1;
			iColonneBord = 0;
		}
		interpolation = (zoneNormaliser - tab[iLigne][iColonne]) / (tab[iLigneBord][iColonneBord] - tab[iLigne][iColonne]);
	}
	return (iLigne / 10.) + (iColonne / 100.) + (interpolation / 100);
}

void intervalle(double moyenne, double variance, double n, double alpha, double *intervalleInf, double *intervalleSup) {
	double margeErreur = alpha * sqrt(variance / n);
	printf("Marge d erreur = %.5lf\n", margeErreur);

	*intervalleInf = moyenne - margeErreur;
	*intervalleSup = moyenne + margeErreur;
}


void constructionTableNormale(int nbPts, ptrFonction ptr) {
	double res = (*ptr)(nbPts);
	printf("res = %.4lf\n\n", res);
}

double simpson(int nbPts) {
	return nbPts / 2.;	
}
