#include "header.h"

void menu(void);

void main(void)
{
	int choix;
	bool choixCorrect;
	do
	{
		menu();
		scanf_s("%d", &choix);
		choixCorrect = choix >= 1 && choix <= 6;
	} while (!choixCorrect);
	while (choix != 6)
	{
		switch (choix)
		{
		case 1: decrypteCleShamir();
			break;
		case 2: calculeMaxPuissance();
			break;
		case 3: calculeExpBaseA();
			break;
		case 4://determineModeleAnomalies();
			break;
		case 5: detecteAnomalies();
			break;
		}
		do
		{
			menu();
			scanf_s("%d", &choix);
			choixCorrect = choix >= 1 && choix <= 6;
		} while (!choixCorrect);
	}
	system("pause");
}

void menu(void)
{
	printf_s("Choississez une fonctionnalité :\n ");
	printf_s("1. Decryptage de la cle de Shamir\n");
	printf_s("2. Resultats test effort\n");
	printf_s("3. Calcul de a exposant x\n");
	printf_s("4. Calcul de l'inverse de 1+x\n");
	printf_s("5. Detecter des anomalies\n");
	printf_s("6. Quitter\n");
}

