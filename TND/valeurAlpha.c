#include "detectionAnomalie.h"

double valeurAlpha(double alpha,TypeTable* tableNormale[])
{
	int interpolation = 0;
	int zoneNormalisee = (1 - alpha / 200) * DOUBLETOINT;
	int iLigne = 0;
	while (iLigne<LIGNEMAX-1&&tableNormale[iLigne+1][0]<=zoneNormalisee)
	{
		iLigne++;
	}
	int iColonne = 0;
	while (iColonne<COLONNEMAX-1&&tableNormale[iLigne][iColonne+1]<=zoneNormalisee)
	{
		iColonne++;
	}
	if (tableNormale[iLigne][iColonne] != zoneNormalisee)
	{
		int iLigneBord = iLigne;
		int iColonneBord = iColonne + 1;
		if (iColonne == COLONNEMAX-1&&tableNormale[iLigne][iColonne] < zoneNormalisee)
		{
			iLigneBord++;
			iColonneBord = 0;
		}

		double interpolation = (zoneNormalisee - tableNormale[iLigne][iColonne]);
		interpolation /= (tableNormale[iLigneBord][iColonneBord]) - tableNormale[iLigne][iColonne];
		
		return iLigne / 10 + iColonne / 100 + interpolation / 100;
	}
}