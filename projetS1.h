#include <stdio.h>
#include<conio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

typedef struct emprunt{
	int idEmprunt;
	int idAdherent;
	int idJeu;
	Date dateEmprunt;
	struct emprunt *suiv;
} Emprunt; 

typedef struct reservation{
	int idRes;
	int idAdherent;
	int idJeu;
	Date dateR;
	struct reservation *suiv;
} Reservation;

/*
	Définition des prototypes de fonctions
*/


typedef enum {faux,vrai} Booleen;


void global();

Date current_date(void);

Date saisie_date(void);

/*
	programme:	fget
	auteur:		FOUCRAS Baptiste
	date:		21/12/20
	finalité:	Retourner par adresse un str contenant un maximum de caractères définit pris d'un fichier, ou jusqu'à ce qu'il rencontre un certain caractère d'arrêt.
*/
void fget(char str[] , int max_saisie, FILE *flot, char char_arret);

/*
	programme:	decaleADroite_Adherent
	auteur:		FOUCRAS Baptiste
	date:		28/12/20
	finalité:	
*/
Adherent** decaleADroite_Adherent(Adherent** tAdherent, int taille_logique, int pos_insert);

/*
	programme:	decaleAGauche_Adherent
	auteur:		FOUCRAS Baptiste
	date:		02/01/02
	finalité:	
*/
Adherent** decaleAGauche_Adherent(Adherent** tAdherent, int taille_logique, int pos_insert);

/*
	programme:	recherchDich_Adhe
	auteur:		FOUCRAS Baptiste
	date:		28/12/20
	finalité:	
*/
int recherchDich_Adhe(Adherent **tAdherent, int taille_logique, int *trouve, int idAdherent);

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
	date:		30/12/20
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
	date:		30/12/20
	finalité:	Insérer un adhérent dans le tableau trié tAdherent et dans le fichier adherent.don
*/
Adherent** ajoutAdherent(Adherent* tAdherent[], int *taille_logique, int *taille_physique);

/*
	programme:	EnregistrerTAdherent
	auteur:		FOUCRAS Baptiste
	date:		30/12/20
	finalité:	
*/
void EnregistrerTAdherent(Adherent** tAdherent, int taille_logique);

/*
	programme:	modifAdherent
	auteur:		FOUCRAS Baptiste
	date:		01/01/21
	finalité:	
*/
Adherent** modifAdherent(Adherent** tAdherent, int taille_logique);

/*
	programme:	supressAdherent
	auteur:		FOUCRAS Baptiste
	date:		01/01/21
	finalité:	
*/
Adherent** supressAdherent(Adherent** tAdherent, int *taille_logique);

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

void retourJeux(Reservation *r, Emprunt *e, Jeux tJeux[]);

/*
	programme:	ajouterJeux
	auteur:		POLLET Matéo
	date:		29/12/20
	finalité:	Ajoute un jeu à tJeux et à la mémoire
*/

Jeux *ajouterJeux(Jeux tJeux[], int *nbJeux, int *tMax);

/*
	programme:	supprimerJeux
	auteur:		POLLET Matéo
	date:		29/12/20
	finalité:	Supprime un jeu du tableau tJeux et de la mémoire
*/

Jeux *supprimerJeux(Jeux tJeux[], int *nbJeux, int *tMax);

void global();







Emprunt* listenouv(void);
Emprunt* insertionEnTete(Emprunt *s, int emprunt, int adherent, int jeu, Date date);
Emprunt* inserer(Emprunt *e, int emprunt, int adherent, int jeu, Date date);
void globale(void);
Date lireFichier(FILE *flot, int *emprunt, int *adherent, int *jeu);
Emprunt* chargeListeEmprunts(void);
void afficherListeEmprunts(Emprunt *e, Jeux tJeux[],int taille_logique,int taille_logique_A, Adherent* tAdherent[]);
Booleen vide(Emprunt *e);
int trouveNumJeu(int id, Jeux tJeu[], int taille_logique);
Booleen vide(Emprunt *e);



Reservation* listenouvR(void);
Reservation* insertionEnTeteR(Reservation *s, int resa, int adherent, int jeu, Date date);
Reservation* insererR(Reservation *r, int resa, int adherent, int jeu, Date date);
Date lireFichierR(FILE *flot, int *resa, int *adherent, int *jeu);
Reservation* chargeListeResa(void);
void afficherListeResa(Reservation *r, Adherent* tAdherent[], int taille_logique_A);
Booleen videR(Reservation *r);
Reservation* insererR(Reservation *r, int resa, int adherent, int jeu, Date date);


Reservation* supprimer(Reservation *a,int x);
Reservation* suppressionEnTete(Reservation *a);
Reservation* suppRes(Reservation *a);
void saveRes(Reservation *a);
