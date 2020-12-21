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


/*
	programme:	fgets_like
	auteur:		FOUCRAS Baptiste
	date:		20/12/20
	finalité:	Prends un nombre de caractères, avec un maximum de caractère définit en second argument, ou jusqu'à ce qu'il rencontre un certain caractère,
				définit en dernier argument
*/
void fget(char str[] , int max_saisie, FILE *flot, char char_arret);

Adherent chargeAdherent(FILE *flot);

/*
	programme:	chargTAdherent
	auteur:		FOUCRAS Baptiste
	date:		??/12/20
	finalité:	Prends un nombre de caractères, avec un maximum de caractère définit en second argument, ou jusqu'à ce qu'il rencontre un certain caractère,
				définit en dernier argument
*/
int chargTAdherent( Adherent* tAdherent[], int taille_physique);