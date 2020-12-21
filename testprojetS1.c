#include "projetS1.h"

void testgets_like(void)
{
	FILE *test_fichier;
	char str[11];
	test_fichier = fopen("../test.txt", "r");
	if(test_fichier == NULL)
	{
		printf("Erreur lors de l'ouverture du fichier test.txt");
		return;
	}
	fget(str , 11, test_fichier, 'r');
	fclose(test_fichier);
	printf("%s\n", str);
}

void testchargeAdherent(void)
{
	Adherent nouv_adhe;
	FILE *adherent_fichier;
	adherent_fichier = fopen("adherent.don", "r");
	if(adherent_fichier == NULL)
	{
		printf("Erreur lors de l'ouverture du fichier test.txt");
		return;
	}
	nouv_adhe = chargeAdherent(adherent_fichier);
	fclose(adherent_fichier);
	printf("%03d\t%s\t%s\t%s\t%02d/%02d/%02d", nouv_adhe.idAdherent, nouv_adhe.civilite, nouv_adhe.nom, nouv_adhe.prenom, nouv_adhe.date_inscrip.jour, nouv_adhe.date_inscrip.mois,
		nouv_adhe.date_inscrip.annee);
}

int main(void)
{
	//testgets_like();
	testchargeAdherent();
	return 0;
}
