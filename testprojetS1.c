#include "projetS1.h"

void testFlorian(void) {
	Emprunt *e;
	Jeux * j;
	Jeux tJ[100];
	int nbJeux,tMax,taille_logique;
	int taille_physique_A=100, taille_logique_A=0;
	Adherent* tAdherent[100];
	Adherent** tA;
	Reservation *r;
	j=chargeTJeux(tJ,&nbJeux,&tMax);
	afficheTJeux(j,nbJeux);
	taille_logique=nbJeux;
	tA=chargTAdherent(tAdherent,&taille_logique_A,&taille_physique_A);
	afficheTAdherent(tAdherent,taille_logique_A);
	e=chargeListeEmprunts();
	afficherListeEmprunts(e,j,taille_logique,taille_logique_A,tAdherent);
	r=chargeListeResa();
	afficherListeResa(r,tAdherent,taille_logique_A,j,taille_logique);
}

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

void testAdherent(void)
{
	Adherent **tAdherent;
	int taille_physique = 9, taille_logique = 0;
	char choix;
	tAdherent = (Adherent**) malloc (taille_physique * sizeof(Adherent*));
	tAdherent = chargTAdherent( tAdherent, &taille_logique, &taille_physique);
	afficheTAdherent(tAdherent, taille_logique);
	printf("Voulez-vous ajouter un adhérent? (o/n)\n");
	scanf("%c%*c", &choix);
	if(choix == 'o')
	{
		printf("%d\t%d\n", taille_logique, taille_physique);
		tAdherent = ajoutAdherent(tAdherent, &taille_logique, &taille_physique);
		printf("%d\t%d\n", taille_logique, taille_physique);
		afficheTAdherent(tAdherent, taille_logique);
		printf("Enregistrement\n");
		EnregistrerTAdherent(tAdherent, taille_logique);
	}
	printf("Voulez-vous modifier un adhérent? (o/n)\n");
	scanf("%c%*c", &choix);
	if(choix == 'o')
	{
		printf("%d\t%d\n", taille_logique, taille_physique);
		tAdherent = modifAdherent(tAdherent, taille_logique);
		printf("%d\t%d\n", taille_logique, taille_physique);
		afficheTAdherent(tAdherent, taille_logique);
		printf("Enregistrement\n");
		EnregistrerTAdherent(tAdherent, taille_logique);
	}
	printf("Voulez-vous supprimer un adhérent? (o/n)\n");
	scanf("%c%*c", &choix);
	if(choix == 'o')
	{
		printf("%d\t%d\n", taille_logique, taille_physique);
		tAdherent = supressAdherent(tAdherent, &taille_logique);
		printf("%d\t%d\n", taille_logique, taille_physique);
		afficheTAdherent(tAdherent, taille_logique);
		printf("Enregistrement\n");
		EnregistrerTAdherent(tAdherent, taille_logique);
	}
	Jeux *tJeux;
	int tMax = 100, nbJeux = 0, i;
	tJeux = chargeTJeux(tJeux, &nbJeux, &tMax);
	Emprunt *e;
	e = chargeListeEmprunts();
	afficherListeEmprunts(e, tJeux, nbJeux, taille_logique, tAdherent);
}

void test(void)
{
	/*
	Adherent **tAdherent;
	int taille_physique = 9, taille_logique = 0;
	char choix;
	tAdherent = (Adherent**) malloc (taille_physique * sizeof(Adherent*));
	tAdherent = chargTAdherent( tAdherent, &taille_logique, &taille_physique);
	afficheTAdherent(tAdherent, taille_logique);
	Jeux *tJeux;
	int tMax = 100, nbJeux = 0, i;
	tJeux = chargeTJeux(tJeux, &nbJeux, &tMax);
	Emprunt *e;
	Reservation *r;
	e = chargeListeEmprunts();
	r = chargeListeResa();
	retourJeux(r, e, tJeux, nbJeux);
	*/
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

void test_saisie_date(void)
{
	Date date;
	date = saisie_date();
	printf("%02d/%02d/%04d", date.jour, date.mois, date.annee);
}

int main(void)
{
	//test_current_date();
	//test_fget();
	//testchargeAdherent();
	//testchargeTAdherent();
	//global();
	//testAdherent();
	//global();
	//testchargeJeux();
	//testchargeTJeux();
	test();
	//test_saisie_date();
	return 0;
}
