#include "projetS1.h"

void test_fget(void)
{
	FILE *test_fichier;
	char str[11];
	test_fichier = fopen("../test.txt", "r");
	if(test_fichier == NULL)
	{
		printf("Erreur lors de l'ouverture du fichier test.txt\n");
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
		printf("Erreur lors de l'ouverture du fichier test.txt\n");
		return;
	}
	nouv_adhe = chargeAdherent(adherent_fichier);
	fclose(adherent_fichier);
	printf("%03d\t%s\t%s\t%s\t%02d/%02d/%02d", nouv_adhe.idAdherent, nouv_adhe.civilite, nouv_adhe.nom, nouv_adhe.prenom, nouv_adhe.date_inscrip.jour, nouv_adhe.date_inscrip.mois,
		nouv_adhe.date_inscrip.annee);
}

void testchargeTAdherent(void)
{
	Adherent **tAdherent;
	int taille_physique = 7, taille_logique = 0;
	tAdherent = (Adherent**) malloc (taille_physique * sizeof(Adherent*));
	tAdherent = chargTAdherent( tAdherent, &taille_logique, &taille_physique);
	afficheTAdherent(tAdherent, taille_logique);
}

void test(void)
{
	menu();
}

int main(void)
{
	//test_fget();
	//testchargeAdherent();
	testchargeTAdherent();
	//global();
	return 0;
}
