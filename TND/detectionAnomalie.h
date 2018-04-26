#define LIGNEMAX 40
#define COLONNEMAX 10

#define DOUBLETOINT 100000
#define FI_MODELE "fiSamModele.csv"
#define FI_TEST "fiSam.csv"
typedef int TypeTable;

double obtenirTailleEchantillon(void);
double obtenirAlpha(char * type);
int obtenirPrecision();
void detecteAnomalies(void);
double calculIntervalle(double moyenne, double variance, int n, double coefficiantAlpha, double *upperLimit);
void  traitementBaseModele(int tailleEchantillon, double lowerControlLimit, double upperControlLimit, double lowerWarningLimit, double upperWarningLimit);
void table_cstr(Fonction f, TypeTable tabNormale[][COLONNEMAX]);
double valeurAlpha(double alpha, TypeTable tableNormale[LIGNEMAX][COLONNEMAX]);
double fLoiNormale(double x);