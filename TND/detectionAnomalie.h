#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "../biblioInteg/simpson.h"

#define LIGNEMAX 40
#define COLONNEMAX 10

#define DOUBLETOINT 10000
typedef int TypeTable;

float calculIntervalle(float moyenne, float variance, int n, float coefficiantAlpha, float *upperLimit);
float traitementBaseModele(int n, float lowerControlLimit, float upperControlLimit, float lowerWarningLimit, float upperWarningLimit, float dataAEvaluer);
double* table_cstr(Fonction f);
double valeurAlpha(double alpha, TypeTable* tableNormale[]);