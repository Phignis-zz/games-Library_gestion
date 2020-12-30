#include "projetS1.h"

void test_current_date(void)
{
	Date jour_actuel;
	jour_actuel = current_date();
	printf("%02d-%02d-%d\n", jour_actuel.jour, jour_actuel.mois, jour_actuel.annee);
}

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
	int taille_physique = 9, taille_logique = 0;
	char choix;
	tAdherent = (Adherent**) malloc (taille_physique * sizeof(Adherent*));
	tAdherent = chargTAdherent( tAdherent, &taille_logique, &taille_physique);
	afficheTAdherent(tAdherent, taille_logique);
	printf("Voulez-vous ajouter un adhérent? (y/n)\n");
	scanf("%c%*c", &choix);
	if(choix == 'o')
	{
		printf("%d\t%d\n", taille_logique, taille_physique);
		tAdherent = ajoutAdherent(tAdherent, &taille_logique, &taille_physique);
		printf("%d\t%d\n", taille_logique, taille_physique);
		afficheTAdherent(tAdherent, taille_logique);
	}
	printf("%d\t%d\n", taille_logique, taille_physique);

}

void test(void)
{
	menu();
}

void testchargeJeux(void)
{
	Jeux nouv_jeu;
	FILE *jeu_fichier;
	jeu_fichier = fopen("jeu.don", "r");
	if(jeu_fichier == NULL)
	{
		printf("Erreur lors de l'ouverture du fichier jeu.don\n");
		return;
	}
	nouv_jeu = chargeJeux(jeu_fichier);
	fclose(jeu_fichier);
	printf("%03d\t%s\t%s\t%d\n", nouv_jeu.idJeux, nouv_jeu.nom, nouv_jeu.type, nouv_jeu.quantite);
}

void testchargeTJeux(void)
{
	Jeux *tJeux;
	int tMax = 100, nbJeux = 0;
	tJeux = chargeTJeux(tJeux, &nbJeux, &tMax);
	if(tJeux == NULL)
		return;
	afficheTJeux(tJeux, nbJeux);
}


int main(void)
{
	//test_current_date();
	//test_fget();
	//testchargeAdherent();
	//testchargeTAdherent();
	//global();
	testchargeTAdherent();
	//global();
	//testchargeJeux();
	//testchargeTJeux();
	return 0;
}
