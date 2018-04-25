<<<<<<< HEAD
#include "header.h"
//void main()
//{
//	//printf("intpower: %lf \n\tshould have: %lf\n",intPower(2,2),4.);
//	//printf("exponentielle: %lf \n\tshould have: %lf\n",exponentielle(6, 2),24.023);
//	//printf("factorielle: %lf\n\tshould have: %lf\n",(double)factorielle(4),24.);
//	printf("decryptage shamir: %lf\n\tshould have: %lf\n",dercyptageShamir(),13.);
//	getchar();
//}
=======
#include <stdio.h>
#include <stdlib.h>
#include "ax.h"
#include "./Shamir.h"
#include "detectionAnomalie.h"

/*void main()
{*/
	printf("ax got %lf\n",ax());
	//printf("degre got: %d\n",degre(0,4));
	//printf("degre got: %d\n",degre(3,4));
	//printf("intpower: %lf \n\tshould have: %lf\n",intPower(2,2),4.);
	/*double terme = 0;
	for (int i = 0; i < 25; i++)
	{
		double petitTerme = intPower(2,i);
		petitTerme /= factorielle(i);
		terme += petitTerme;
		printf("exponentielle: %lf \n\tshould have: %lf\n", exponentielle(i,2), terme);
	}*/
	//printf("factorielle: %lf\n\tshould have: %lf\n",(double)factorielle(4),24.);
	//printf("decryptage shamir: %lf\n\tshould have: %lf\n",dercyptageShamir(),13.);
/*	getchar();
}*/
>>>>>>> 5d423075edd3f3df57d29c26b83dfe9cdfd75275

/*Alex
double exponentielle(int nbIterationsTaylor, double argument);
double intPower(double argument, int nbIterations);
double resultat(double reste, int nbLimites, int nbIterations);

Sam
void vider(void);
int degre(int nbDecimales, int nbLimites);
double expressionDuReste(int nbDecimales, int nbLimites);
int factorielle(int nbIteration);*/