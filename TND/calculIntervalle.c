//#include "header.h"
//
//
//double calculIntervalle(double moyenne, double variance, int n, double coefficiantAlpha, double *upperLimit)
//{
//	float margeErreur = coefficiantAlpha * (float)sqrt(variance / n);
//	float intervalleInf = moyenne - margeErreur;
//	float intervalleSup = moyenne + margeErreur;
//	*upperLimit = intervalleSup;
//	return intervalleInf;
//}
//
//void detecteAnomalies(int tailleEchantillon, double lowerControlLimit, double upperControlLimit, double lowerWarningLimit, double upperWarningLimit)
//{
//	int numEchantillon;
//	int tailleReelleEchantillon;
//	double sommeEchantillon;
//	FILE* ficsv;
//	fopen_s(&ficsv, "fiSam.csv", "r");
//	if (ficsv != NULL) {
//		numEchantillon = 1;
//		double xi;
//		fscanf_s(ficsv, "%lf", &xi);
//		while (!feof(ficsv)) {
//			tailleReelleEchantillon = 0;
//			sommeEchantillon = 0;
//			while (tailleReelleEchantillon < tailleEchantillon && !feof(ficsv)) {
//				char buffer;
//				fscanf_s(ficsv, "%c", &buffer);
//				sommeEchantillon += xi;
//				tailleReelleEchantillon++;
//				fscanf_s(ficsv, "%lf", &xi);
//			}
//			double xBarre = sommeEchantillon / (double) tailleReelleEchantillon;
//			char * str;
//			if (xBarre < lowerWarningLimit || xBarre > upperWarningLimit) {
//				str = "nous sommes endehors de l intervalle de surveillance";
//				if (xBarre < lowerControlLimit || xBarre > upperControlLimit) {
//					str = "valeurs erronees";
//				}
//			}
//			else {
//				str = "ok";
//			}
//
//			printf_s("Echantillon %d composé de %d valeur (xBarre : %lf) : %s\n", numEchantillon, tailleReelleEchantillon, xBarre, str);
//			numEchantillon++;
//		}
//		fclose(ficsv);
//	}
//	else {
//		puts("Le fichier n\'existe pas !");
//	}
//}
//
