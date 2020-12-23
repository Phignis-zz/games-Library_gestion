#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
	Définition des structures nécessaires
*/

typedef struct
{
	int jour;
	int mois;
	int annee;
}Date;

typedef struct
{
	int idAdherent;
	char civilite[4];
	char nom[22];
	char prenom[22];
	Date date_inscrip;
}Adherent;

/*
	Définition des prototypes de fonctions
*/

void global();

/*
	programme:	fget
	auteur:		FOUCRAS Baptiste
	date:		21/12/20
	finalité:	Retourner par adresse un str contenant un maximum de caractères définit pris d'un fichier, ou jusqu'à ce qu'il rencontre un certain caractère d'arrêt.
*/
void fget(char str[] , int max_saisie, FILE *flot, char char_arret);

/*
	programme:	chargeAdherent
	auteur:		FOUCRAS Baptiste
	date:		20/12/20
	finalité:	Charger une ligne du fichier pointé par *flot dans une structure Adherent.
*/
Adherent chargeAdherent(FILE *flot);

/*
	programme:	chargTAdherent
	auteur:		FOUCRAS Baptiste
	date:		21/12/20
	finalité:	charger le fichier adherent.don dans le tableau de pointeurs tAdherent, ligne par ligne.
*/
Adherent** chargTAdherent( Adherent* tAdherent[], int *taille_logique, int *taille_physique);

/*
	programme:	afficheTAdherent
	auteur:		FOUCRAS Baptiste
	date:		21/12/20
	finalité:	afficher le contenu des pointeurs du tableau tAdherent.
*/
void afficheTAdherent(Adherent* tAdherent[], int taille_logique);

/*
	programme:	ajoutAdherent
	auteur:		FOUCRAS Baptiste
	date:		??/12/20
	finalité:	Insérer un adhérent dans le tableau trié tAdherent et dans le fichier adherent.don
*/
int ajoutAdherent(Adherent* tAdherent[], int taille_logique, int *taille_physique);

/*
	programme:	menu
	auteur:		POLLET Matéo
	date:		21/12/20
	finalité:	Choisir une fonction en tapant un nombre.
*/
void menu();
