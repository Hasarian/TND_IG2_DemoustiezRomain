#include "detectionAnomalie.h"
#include <fenv.h>
void parseToConvertDouble(char * str) {
	int i = 0;
	while (str[i] != '\n' || str[i] != '\0') {
		if (str[i] == ',') str[i] = '.';
		if (str[i] == '\n') {
			str[i] = '\0';
		}
	}
}

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

	float sommeEchantillion = 0;
	double xi;
	FILE* dataAEvaluer;
	fopen_s(&dataAEvaluer, "fiModele.csv", "r");
	if(dataAEvaluer != NULL) {
		//while (dataAEvaluer != NULL) {
			char xiLu[200];
			double xi;
			char * ptr;
			int i = 0;
			fgets(xiLu,200, dataAEvaluer);
			parseToConvertDouble(xiLu);
			xi = strtod(xiLu, &ptr);
			printf("%f", xi);
		//}

		fclose(dataAEvaluer);
	}
	else {
		puts("Le fichier n\'existe pas !");
	}
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

/*float traitementBaseModele(int n, float lowerControlLimit, float upperControlLimit, float lowerWarningLimit, float upperWarningLimit, float dataAEvaluer)
{
	float sommeEchantillion = 0;
	float xi;
	char * xiLu;
	FILE* dataAEvaluer = fopen("fiModele.csv", "r");
	if (&dataAEvaluer != NULL) {
		fgets(xiLu, 1, &dataAEvaluer);
		xi = atof(xiLu);
		printf("%s - %f\n", xiLu, xi);
	}
	else {
		puts("Le fichier n\'existe pas !");
	}

	
	return 0.0f;
}*/

