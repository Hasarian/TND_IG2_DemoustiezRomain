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

float traitementBaseModele(int tailleEchantillon, float lowerControlLimit, float upperControlLimit, float lowerWarningLimit, float upperWarningLimit, float dataAEvaluer)
{
	float sommeEchantillion = 0;
	FILE* ficsv;
	fopen_s(&ficsv, "fiModele.csv", "r");
	if (ficsv != NULL) {
		while (!feof(ficsv)) {
			int numEchantillon = 1;
			int tailleReelleEchantillon = 0;
			while (tailleReelleEchantillon < tailleEchantillon && !feof(ficsv)) {
				double xi;
				char poubelle;
				fscanf_s(ficsv, "%lf", &xi);
				fscanf_s(ficsv, "%c", &poubelle);
				sommeEchantillion += xi;
				tailleReelleEchantillon++;
			}
			double xBarre = sommeEchantillion / tailleReelleEchantillon;
			char * libEchantillon;
			char * str;
			if (xBarre < lowerWarningLimit || xBarre > upperWarningLimit) {
				sprintf(libEchantillon, "Echantillon %d composé de %d valeur : ", numEchantillon, tailleReelleEchantillon);
				str = "nous sommes endehors de l'intervalle de surveillance";
				if (xBarre < lowerControlLimit || xBarre > upperControlLimit) {
					str = "valeurs érronées";
				}
				puts(strcat(libEchantillon, str));
			}
			numEchantillon++;
		}
		fclose(ficsv);
	}
	else {
		puts("Le fichier n\'existe pas !");
	}

	
	return 0.0f;
}

