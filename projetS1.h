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

typedef struct
{
	int idJeux;
	char nom[20];
	char type[15];
	int quantite;
}Jeux;

/*
	Définition des prototypes de fonctions
*/


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
int chargTAdherent( Adherent* tAdherent[], int *taille_physique);

/*
	programme:	afficheTAdherent
	auteur:		FOUCRAS Baptiste
	date:		21/12/20
	finalité:	afficher le contenu des pointeurs du tableau tAdherent.
*/
void afficheTAdherent(Adherent* tAdherent[], int taille_logique);

/*
	programme:	chargeJeux
	auteur:		POLLET Matéo
	date:		22/12/20
	finalité:	Charger une ligne du fichier pointé par *flot dans une structure Jeux.
*/

Jeux chargeJeux(FILE *flot);

/*
	programme:	chargeTJeux
	auteur:		POLLET Matéo
	date:		22/12/20
	finalité:	Charger entièrement le fichier jeu.don dans le tableau tJeux, ligne par ligne. Retourne le tableau tJeux.
*/

Jeux *chargeTJeux( Jeux tJeux[], int *nbJeux, int *tMax);

/*
	programme:	afficheTJeux
	auteur:		POLLET Matéo
	date:		22/12/20
	finalité:	Affiche le contenu du tableau tJeux triée par type de Jeux, puis par ordre alphabétique de leur nom
*/

void afficheTJeux(Jeux tJeux[], int nbJeux);

/*
	programme:	menu
	auteur:		POLLET Matéo
	date:		21/12/20
	finalité:	Choisir une fonction en tapant un nombre.
*/

void menu();

/*
	programme:	plusGrand
	auteur:		POLLET Matéo
	date:		22/12/20
	finalité:	Compare  les noms des jeux entre-eux pour obtenir le plus grand alphabétiquement.
*/

int plusGrand(Jeux tJeux[], int n);

/*
	programme:	echange
	auteur:		POLLET Matéo
	date:		22/12/20
	finalité:	Echange les lignes du tableau pour les triées.
*/

void echange(Jeux tJeux[], int i, int j);

/*
	programme:	retourJeux
	auteur:		POLLET Matéo
	date:		22/12/20
	finalité:	Le retour déclenche l’examen des réservations pour peut être transformer une réservation en emprunt et faire parvenir le jeu à l’adhérent l’ayant réservé.
*/

void retourJeux(void);

void global();
