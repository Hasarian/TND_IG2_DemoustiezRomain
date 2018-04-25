#include "header.h"

double fLoiNormale(double x) {
	return (pow(exp(x), 2) / 2) / (sqrt(2 * M_PI));
}

void detecteAnomalies(void){
	int tailleEchantillon;
	int n;
	double alphaControl = 0.05;
	double coefficientAlphaControl;
	double alphaWarning = 0.01;
	double coefficientAlphaWarning;
	double xi;
	double sommeXi = 0;
	double sommeXiCarre = 0;
	double moyenne;
	double variance;
	double lowerControlLimit;
	double upperControlLimit;
	double lowerWarningLimit;
	double upperWarningLimit;
	TypeTable * tableNormale;

	FILE* dataFile;

	do {
		printf("Entrez la taille de l'échantillon : ");
		scanf_s("%d", &tailleEchantillon);
	} while (tailleEchantillon < 1);

	n = 0;

	tableNormale = table_cstr(fLoiNormale);
	fopen_s(&dataFile, "fiSam.csv","r");
	if (dataFile != NULL) {
		fscanf_s(dataFile, "%lf", &xi);
		while (!feof(dataFile)) {
			char buffer;
			fscanf_s(dataFile, "%c", &buffer);
			sommeXi += xi;
			sommeXiCarre += xi * xi;
			fscanf_s(dataFile, "%lf", &xi);
			n++;
		}
		fclose(dataFile);

		moyenne = sommeXi / n;
		variance = sommeXiCarre / n - (moyenne * moyenne);
		coefficientAlphaControl = valeurAlpha(alphaControl, tableNormale);
		coefficientAlphaWarning = valeurAlpha(alphaWarning, tableNormale);
		lowerControlLimit = calculIntervalle(moyenne, variance, n, coefficientAlphaControl, &upperControlLimit);
		lowerWarningLimit = calculIntervalle(moyenne, variance, n, coefficientAlphaWarning, &upperWarningLimit);
		traitementBaseModele(tailleEchantillon, lowerControlLimit, upperControlLimit, lowerWarningLimit, upperWarningLimit);
	}
	else {
		puts("Impossible d\'ouvrir le fichier !");
	}
}

double calculIntervalle(double moyenne, double variance, int n, double coefficiantAlpha, double *upperLimit)
{
	float margeErreur = coefficiantAlpha * (float)sqrt(variance / n);
	float intervalleInf = moyenne - margeErreur;
	float intervalleSup = moyenne + margeErreur;
	*upperLimit = intervalleSup;
	return intervalleInf;
}

void traitementBaseModele(int tailleEchantillon, double lowerControlLimit, double upperControlLimit, double lowerWarningLimit, double upperWarningLimit)
{
	int numEchantillon;
	int tailleReelleEchantillon;
	double sommeEchantillon;
	FILE* ficsv;
	fopen_s(&ficsv, "fiSam.csv", "r");
	if (ficsv != NULL) {
		numEchantillon = 1;
		double xi;
		fscanf_s(ficsv, "%lf", &xi);
		while (!feof(ficsv)) {
			tailleReelleEchantillon = 0;
			sommeEchantillon = 0;
			while (tailleReelleEchantillon < tailleEchantillon && !feof(ficsv)) {
				char buffer;
				fscanf_s(ficsv, "%c", &buffer);
				sommeEchantillon += xi;
				tailleReelleEchantillon++;
				fscanf_s(ficsv, "%lf", &xi);
			}
			double xBarre = sommeEchantillon / (double)tailleReelleEchantillon;
			char * str;
			if (xBarre < lowerWarningLimit || xBarre > upperWarningLimit) {
				str = "nous sommes endehors de l intervalle de surveillance";
				if (xBarre < lowerControlLimit || xBarre > upperControlLimit) {
					str = "valeurs erronees";
				}
			}
			else {
				str = "ok";
			}

			printf_s("Echantillon %d composé de %d valeur (xBarre : %lf) : %s\n", numEchantillon, tailleReelleEchantillon, xBarre, str);
			numEchantillon++;
		}
		fclose(ficsv);
	}
	else {
		puts("Le fichier n\'existe pas !");
	}
}

double* table_cstr(Fonction f)
{
	int nbPoints = 3;
	double dernierResultat = 0.5;
	TypeTable tabNormale[LIGNEMAX][COLONNEMAX];
	tabNormale[0][0] = dernierResultat;
	double bInf = 0;
	double bSup, resultat;
	for (int iLigne = 0; iLigne < LIGNEMAX; iLigne++)
	{
		for (int iColonne = 0; iColonne < COLONNEMAX; iColonne++)
		{
			bSup = iLigne / 10 + iColonne / 100;
			resultat = calculSimpson(nbPoints, bInf, bSup, f);
			dernierResultat += resultat;
			tabNormale[iLigne][iColonne] = resultat*DOUBLETOINT;
			bInf = bSup;
		}
	}
	return tabNormale;
}


double traitementBaseModeles(double alpha, TypeTable* tableNormale[])
{
	int interpolation = 0;
	int zoneNormalisee = (1 - alpha / 200) * DOUBLETOINT;
	int iLigne = 0;
	while (iLigne<LIGNEMAX - 1 && tableNormale[iLigne + 1][0] <= zoneNormalisee)
	{
		iLigne++;
	}
	int iColonne = 0;
	while (iColonne<COLONNEMAX - 1 && tableNormale[iLigne][iColonne + 1] <= zoneNormalisee)
	{
		iColonne++;
	}
	if (tableNormale[iLigne][iColonne] != zoneNormalisee)
	{
		int iLigneBord = iLigne;
		int iColonneBord = iColonne + 1;
		if (iColonne == COLONNEMAX - 1 && tableNormale[iLigne][iColonne] < zoneNormalisee)
		{
			iLigneBord++;
			iColonneBord = 0;
		}

		double interpolation = (zoneNormalisee - tableNormale[iLigne][iColonne]);
		interpolation /= (tableNormale[iLigneBord][iColonneBord]) - tableNormale[iLigne][iColonne];

		return iLigne / 10 + iColonne / 100 + interpolation / 100;
	}
}

double valeurAlpha(double alpha, TypeTable* tableNormale[])
{
	int interpolation = 0;
	int zoneNormalisee = (1 - alpha / 200) * DOUBLETOINT;
	int iLigne = 0;
	while (iLigne < LIGNEMAX - 1 && tableNormale[iLigne+1][0] <= zoneNormalisee)
	{
		iLigne++;
	}
	int iColonne = 0;
	while (iColonne<COLONNEMAX-1&&tableNormale[iLigne][iColonne+1]<=zoneNormalisee)
	{
		iColonne++;
	}
	if (tableNormale[iLigne][iColonne] != zoneNormalisee)
	{
		int iLigneBord = iLigne;
		int iColonneBord = iColonne + 1;
		if (iColonne == COLONNEMAX-1&&tableNormale[iLigne][iColonne] < zoneNormalisee)
		{
			iLigneBord++;
			iColonneBord = 0;
		}

		double interpolation = (zoneNormalisee - tableNormale[iLigne][iColonne]);
		interpolation /= (tableNormale[iLigneBord][iColonneBord]) - tableNormale[iLigne][iColonne];
		
		return iLigne / 10 + iColonne / 100 + interpolation / 100;
	}
}