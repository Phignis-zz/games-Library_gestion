#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
	Définition des structures nécessaires
*/
typedef struct
{
	int idAdherent;
	char civilite[3];
	char nom[20];
	char prenom[20];
	int jour_inscrip;
	int mois_inscrip;
	int annee_inscrip;
}Adherent;

/*
	Définition des prototypes de fonctions
*/

int chargTAdherent( Adherent* tAdherent[], int taille_physique);