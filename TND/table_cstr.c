#include "detectionAnomalie.h"

double* table_cstr(Fonction f)
{
	int nbPoints = 3;
	double dernierResultat = 0.5;
	double tabNormale[LIGNEMAX][COLONNEMAX];
	tabNormale[0][0] = dernierResultat;
	double bInf = 0;
	double bSup,resultat;
	for (int iLigne = 0; iLigne < LIGNEMAX; iLigne++)
	{
		for (int iColonne = 0; iColonne < COLONNEMAX; iColonne++)
		{
			bSup = iLigne / 10 + iColonne / 100;
			resultat = calculSimpson(nbPoints,bInf,bSup,f);
			dernierResultat += resultat;
			tabNormale[iLigne][iColonne] = resultat*DOUBLETOINT;
			bInf = bSup;
		}
	}
	return tabNormale;
}