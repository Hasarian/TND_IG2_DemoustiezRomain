#include "header.h"

double fLoiNormale(double x) {
	return exp(-pow(x, 2) / 2) / sqrt(2 * M_PI);

}

double obtenirTailleEchantillon(void) {
	int tailleEchantillon;

	do {
		printf_s("Entrez la taille de l'echantillon : ");
		scanf_s("%d", &tailleEchantillon);
	} while (tailleEchantillon < 1);
	
	return tailleEchantillon;
}

double obtenirAlpha(char * type) {
	double alpha;
	do {
		printf_s("Entrez la valeur de alpha %s (en %%) : ", type);
		scanf_s("%lf", &alpha);
	} while (alpha < 0);

	return alpha;
}

void detecteAnomalies(void){
	int tailleEchantillon;
	int n;
	double alphaControl;
	double coefficientAlphaControl;
	double alphaWarning;
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

	tailleEchantillon = obtenirTailleEchantillon();
	alphaControl = obtenirAlpha("controle");
	alphaWarning = obtenirAlpha("warning");
	n = 0;
	table_cstr(fLoiNormale, tableNormale);

	fopen_s(&dataFile, CSV_FILE,"r");
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
	fopen_s(&ficsv, CSV_FILE, "r");
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

			printf_s("Echantillon %d - composé de %d valeur(s) - (xBarre : ", numEchantillon, tailleReelleEchantillon);
			afficheDecimales(xBarre, 5);
			printf_s(") : %s\n", str);
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

double valeurAlpha(double alpha, TypeTable tableNormale[LIGNEMAX][COLONNEMAX])
{
	double interpolation = 0;
	int zoneNormalisee = (1 - alpha/200) * DOUBLETOINT;
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