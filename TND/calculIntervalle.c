#include "detectionAnomalie.h"
#include <fenv.h>

int main(int argc, char *argv[]) { 
	//float moyenne = 44.21053;
	//float variance = 277.00831;
	//float alphaControl = 0.01;
	//float alphaWarning = 0.05;
	//float coefficiantAlplha = 1.64500;
	//int n = 38;
	//float lowerLimit;
	//float upperLimit;

	//lowerLimit = calculIntervalle(moyenne, variance, n, coefficiantAlplha, &upperLimit);
	//printf("[%.5f, %.5f]\n", lowerLimit, upperLimit);
	//system("pause");

	system("pause");
}

float calculIntervalle(float moyenne, float variance, int n, float coefficiantAlpha, float *upperLimit)
{
	float margeErreur = coefficiantAlpha * (float)sqrt(variance / n);
	float intervalleInf = moyenne - margeErreur;
	float intervalleSup = moyenne + margeErreur;
	*upperLimit = intervalleSup;
	return intervalleInf;
}

float traitementBaseModele(int n, float lowerControlLimit, float upperControlLimit, float lowerWarningLimit, float upperWarningLimit, float dataAEvaluer)
{
	float sommeEchantillion = 0;
	FILE* ficsv;
	fopen_s(&ficsv, "fiModele.csv", "r");
	if (ficsv != NULL) {
		int i = 0;
		while (!feof(ficsv)) {
			while (i < n && !feof(ficsv)) {
				double xi;
				char poubelle;
				fscanf_s(ficsv, "%lf", &xi);
				fscanf_s(ficsv, "%c", &poubelle);
				sommeEchantillion += xi;
			}

			double xBarre = sommeEchantillion / n;
			char * str;
			if (xBarre < lowerWarningLimit || xBarre > upperWarningLimit) {
				str = "nous sommes endehors de l'intervalle de surveillance";
				if (xBarre < lowerControlLimit || xBarre > upperControlLimit) {
					str = "valeur érronée";
				}

				puts(str);
			}
		}
		fclose(ficsv);
	}
	else {
		puts("Le fichier n\'existe pas !");
	}

	
	return 0.0f;
}

