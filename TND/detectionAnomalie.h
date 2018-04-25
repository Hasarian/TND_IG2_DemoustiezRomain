#define LIGNEMAX 40
#define COLONNEMAX 10

#define DOUBLETOINT 10000
typedef int TypeTable;

void detecteAnomalies(void);
double calculIntervalle(double moyenne, double variance, int n, double coefficiantAlpha, double *upperLimit);
void  traitementBaseModele(int tailleEchantillon, double lowerControlLimit, double upperControlLimit, double lowerWarningLimit, double upperWarningLimit);
TypeTable* table_cstr(Fonction f);
double valeurAlpha(double alpha, TypeTable* tableNormale[]);
double fLoiNormale(double x);