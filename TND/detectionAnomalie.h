#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

float calculIntervalle(float moyenne, float variance, int n, float coefficiantAlpha, float *upperLimit);
float traitementBaseModele(int n, float lowerControlLimit, float upperControlLimit, float lowerWarningLimit, float upperWarningLimit, float dataAEvaluer);
