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
	Adherent **tAdherent;
	int idEmprunt;
	Reservation *r_parcours;
	Emprunt *e_parcours;
	int taille_physique = 9, taille_logique = 0;
	char choix;
	tAdherent = chargTAdherent( tAdherent, &taille_logique, &taille_physique);
	afficheTAdherent(tAdherent, taille_logique);
	Jeux *tJeux;
	int tMax = 100, nbJeux = 0, i;
	tJeux = chargeTJeux(tJeux, &nbJeux, &tMax);
	Emprunt *e;
	Reservation *r;
	e = chargeListeEmprunts();
	r = chargeListeResa();
	/*
	r_parcours = r;
    e_parcours = e;
    while(e_parcours->suiv != NULL)
    {
        e_parcours = e_parcours->suiv;
    }
	idEmprunt = e_parcours->idEmprunt + 1;
	while (r_parcours != NULL)
	{
		printf("dddddddddddddddddddddddddddddd");
		if(r_parcours->idRes == 7)
		{
			printf("%d", e->idEmprunt);
			e = inserer(e, idEmprunt, r_parcours->idAdherent, r_parcours->idJeu, r_parcours->dateR);
		}
		r_parcours = r_parcours->suiv;
	}
	printf("dddddddddddddddddddddddddddddd");
	saveEmp(e);
	//retourJeux(r, e, tJeux, nbJeux);
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

void test_ajout_Reserv_Emp(void)
{
	Adherent* *tAdherent;
	Jeux* tJeux;
	Emprunt *e;
	Reservation *r;
	int taille_logique_tAdh = 0, taille_logique_tJeux = 0, taille_physique_tAdh = 9, taille_physique_tJeux = 10;
	int idAdh = 99, idJeu = 45;
	Date date_emprunt;
	date_emprunt.jour = 27;
	date_emprunt.mois = 10;
	date_emprunt.annee = 2002;

	// chargement en mémoire des divers fichiers, ainsi que leur affichage
	tAdherent = chargTAdherent(tAdherent, &taille_logique_tAdh, &taille_physique_tAdh);
	afficheTAdherent(tAdherent, taille_logique_tAdh);

	tJeux = chargeTJeux(tJeux, &taille_logique_tJeux, &taille_physique_tJeux);
	afficheTJeux(tJeux, taille_logique_tJeux);

	e = chargeListeEmprunts();

	r = chargeListeResa();


	// r = ajoutReservation(tAdherent, taille_logique_tAdh, tJeux, taille_logique_tJeux, r);
	// saveRes(r);

	e = ajoutEmprunt(e, tJeux, taille_logique_tJeux, idAdh, &idJeu, date_emprunt);
	saveEmp(e);

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
	//test();
	//test_saisie_date();
	test_ajout_Reserv_Emp();
	return 0;
}
