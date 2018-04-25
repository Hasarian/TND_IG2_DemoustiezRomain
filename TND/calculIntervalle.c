#include "header.h"

//int main(int argc, char *argv[]) { 
//	//float moyenne = 44.21053;
//	//float variance = 277.00831;
//	//float alphaControl = 0.01;
//	//float alphaWarning = 0.05;
//	//float coefficiantAlplha = 1.64500;
//	//int n = 38;
//	//float lowerLimit;
//	//float upperLimit;
//
//	//lowerLimit = calculIntervalle(moyenne, variance, n, coefficiantAlplha, &upperLimit);
//	//printf("[%.5f, %.5f]\n", lowerLimit, upperLimit);
//	//system("pause");
//
//	system("pause");
//}

float calculIntervalle(float moyenne, float variance, int n, float coefficiantAlpha, float *upperLimit)
{
	float margeErreur = coefficiantAlpha * (float)sqrt(variance / n);
	float intervalleInf = moyenne - margeErreur;
	float intervalleSup = moyenne + margeErreur;
	*upperLimit = intervalleSup;
	return intervalleInf;
}

void detecteAnomalies(int tailleEchantillon, double lowerControlLimit, double upperControlLimit, double lowerWarningLimit, double upperWarningLimit)
{
	int numEchantillon;
	int tailleReelleEchantillon;
	double sommeEchantillion;
	FILE* ficsv;
	fopen_s(&ficsv, "fiSam.csv", "r");
	if (ficsv != NULL) {
		numEchantillon = 1;
		double xi;
		fscanf_s(ficsv, "%lf", &xi);
		while (!feof(ficsv)) {
			tailleReelleEchantillon = 0;
			sommeEchantillion = 0;
			while (tailleReelleEchantillon < tailleEchantillon && !feof(ficsv)) {
				char buffer;
				fscanf_s(ficsv, "%c", &buffer);
				sommeEchantillion += xi;
				tailleReelleEchantillon++;
				printf_s("échantillon %d - %c\n", numEchantillon, buffer);
				fscanf_s(ficsv, "%lf", &xi);
			}
			double xBarre = sommeEchantillion / (double) tailleReelleEchantillon;
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

