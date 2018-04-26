#include "header.h"

double fLoiNormale(double x) {
	//double expx = exp(x);
	//return (expx * expx / 2) / (sqrt(2 * M_PI));
	return exp(-pow(x, 2) / 2) / sqrt(2 * M_PI);

}

void detecteAnomalies(void){
	int tailleEchantillon;
	int n;
	double alphaControl = 0.01;
	double coefficientAlphaControl;
	double alphaWarning = 0.05;
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
	TypeTable tableNormale[LIGNEMAX][COLONNEMAX] = { {0} };

	FILE* dataFile;

	do {
		printf("Entrez la taille de l'Úchantillon : ");
		scanf_s("%d", &tailleEchantillon);
	} while (tailleEchantillon < 1);

	n = 0;

	table_cstr(fLoiNormale, &tableNormale);

	for(int iLigne = 0; iLigne < LIGNEMAX; iLigne++) {
		for(int iCol = 0; iCol < COLONNEMAX; iCol++){
			printf("%d | ", tableNormale[iLigne][iCol]);
		}
		printf("\n");
	}

	fopen_s(&dataFile, "fiModele.csv","r");
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
	double margeErreur = coefficiantAlpha * sqrt(variance / n);
	double intervalleInf = moyenne - margeErreur;
	double intervalleSup = moyenne + margeErreur;
	*upperLimit = intervalleSup;
	return intervalleInf;
}

void traitementBaseModele(int tailleEchantillon, double lowerControlLimit, double upperControlLimit, double lowerWarningLimit, double upperWarningLimit)
{
	int numEchantillon;
	int tailleReelleEchantillon;
	double sommeEchantillon;
	FILE* ficsv;
	fopen_s(&ficsv, "fiTest.csv", "r");
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
			int xBarreInt = xBarre * DOUBLETOINT;
			int lowerWarningLimitInt = lowerWarningLimit * DOUBLETOINT;
			int upperWarningLimitInt = upperWarningLimit * DOUBLETOINT;
			int lowerControlLimitInt = lowerControlLimit * DOUBLETOINT;
			int upperControlLimitInt = upperControlLimit * DOUBLETOINT;
			if (xBarreInt < lowerWarningLimitInt || xBarreInt > upperWarningLimitInt) {
				str = "nous sommes endehors de l intervalle de surveillance";
				if (xBarreInt < lowerControlLimitInt || xBarreInt > upperControlLimitInt) {
					str = "valeurs erronees";
				}
			}
			else {
				str = "ok";
			}

			printf_s("Echantillon %d composÚ de %d valeur (xBarre : %lf) : %s\n", numEchantillon, tailleReelleEchantillon, xBarre, str);
			numEchantillon++;
		}
		fclose(ficsv);
	}
	else {
		puts("Le fichier n\'existe pas !");
	}
}

void table_cstr(Fonction f, TypeTable tabNormale[][COLONNEMAX])
{
	int nbPoints = 5;
	double dernierResultat = 0.5;
	tabNormale[0][0] = dernierResultat;
	double bInf = 0;
	double bSup, resultat;
	for (int iLigne = 0; iLigne < LIGNEMAX; iLigne++)
	{
		for (int iColonne = 0; iColonne < COLONNEMAX; iColonne++)
		{
			bSup = (iLigne / 10.) + (iColonne / 100.);
			resultat = calculSimpson(nbPoints, bInf, bSup, f);
			dernierResultat += resultat;
			tabNormale[iLigne][iColonne] = (TypeTable) (dernierResultat*DOUBLETOINT);
			bInf = bSup;
		}
	}
	return tabNormale;
}


//TypeTable* table_cstr(Fonction f)
//{
//	int nbPoints = 3;
//	double dernierResultat = 0.5;
//	TypeTable tabNormale[LIGNEMAX][COLONNEMAX];
//	tabNormale[0][0] = dernierResultat;
//	double bInf = 0;
//	double bSup, resultat;
//	for (int iLigne = 0; iLigne < LIGNEMAX; iLigne++)
//	{
//		for (int iColonne = 0; iColonne < COLONNEMAX; iColonne++)
//		{
//			bSup = iLigne / 10 + iColonne / 100;
//			resultat = calculSimpson(nbPoints, bInf, bSup, f);
//			dernierResultat += resultat;
//			tabNormale[iLigne][iColonne] = resultat*DOUBLETOINT;
//			bInf = bSup;
//		}
//	}
//	return tabNormale;
//}


double valeurAlpha(double alpha, TypeTable tableNormale[LIGNEMAX][COLONNEMAX])
{
	double interpolation = 0;
	int zoneNormalisee = (1 - alpha/2) * DOUBLETOINT;
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

		interpolation = (zoneNormalisee - tableNormale[iLigne][iColonne]);
		interpolation /= (tableNormale[iLigneBord][iColonneBord] - tableNormale[iLigne][iColonne]);
	}
	return iLigne / 10. + iColonne / 100. + interpolation / 100.;
}