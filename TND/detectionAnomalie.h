#define LIGNEMAX 40
#define COLONNEMAX 10

#define DOUBLETOINT 10000
typedef int TypeTable;

double calculIntervalle(double moyenne, double variance, double n, double coefficiantAlpha, double *upperLimit);
void detecteAnomalies(int tailleEchantillon, double lowerControlLimit, double upperControlLimit, double lowerWarningLimit, double upperWarningLimit);
double* table_cstr(Fonction f);
double valeurAlpha(double alpha, TypeTable* tableNormale[]);