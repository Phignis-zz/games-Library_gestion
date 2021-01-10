#include <stdio.h>
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
}Emprunt; 

typedef struct reservation{
	int idRes;
	int idAdherent;
	int idJeu;
	Date dateR;
	struct reservation *suiv;
}Reservation;

/*
	Définition des prototypes de fonctions
*/


typedef enum {faux,vrai} Booleen;


void global();

/*
	programme:	current_date
	auteur:		FOUCRAS Baptiste
	date:		28/12/20
	finalité:	Retourner la date de l'ordinateur, grâce à time.h
*/
Date current_date(void);

/*
	programme:	saisie_date
	auteur:		FOUCRAS Baptiste
	date:		30/12/20
	finalité:	Saisir une date avec contrôle complet de la saisie.
*/
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
	finalité:	Décale à droite à partir de l'index pos_insert tout les éléments du tableau de pointeurs d'adhérent
*/
Adherent** decaleADroite_Adherent(Adherent** tAdherent, int taille_logique, int limite);

/*
	programme:	decaleAGauche_Adherent
	auteur:		FOUCRAS Baptiste
	date:		02/01/02
	finalité:	Décale à gauche à partir de l'index pos_insert tout les éléments du tableau de pointeurs d'adhérent
*/
Adherent** decaleAGauche_Adherent(Adherent** tAdherent, int taille_logique, int debut);

/*
	programme:	recherchDich_Adhe
	auteur:		FOUCRAS Baptiste
	date:		28/12/20
	finalité:	retourne la position d'insertion de l'id d'adhérent, et informe si il est déjà présent ou non dans le tableau tAdherent
*/
int recherchDich_Adhe(Adherent **tAdherent, int taille_logique, int *trouve, int idAdherent);

/*
	programme:	recherchDich_Jeux
	ajoutEmprunt:		POLLET Matéo
	date:		28/12/20
	finalité:	retourne la position d'insertion de l'id de jeu si ce jeu est présent, ou -1 s'il n'est pas présent dans le tableau tJeux
*/
int recherche_Jeux(Jeux *tJeux, int taille_logique, int idJeu);

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
	finalité:	Insérer un adhérent dans le tableau trié tAdherent
*/
Adherent** ajoutAdherent(Adherent* tAdherent[], int *taille_logique, int *taille_physique);

/*
	programme:	EnregistrerTAdherent
	auteur:		FOUCRAS Baptiste
	date:		30/12/20
	finalité:	Enregistre les données du tableau tAdherent dans le fichier adherent.don
*/
void EnregistrerTAdherent(Adherent** tAdherent, int taille_logique);

/*
	programme:	modifAdherent
	auteur:		FOUCRAS Baptiste
	date:		01/01/21
	finalité:	Modifier un adhérent du tableau tAdherent
*/
Adherent** modifAdherent(Adherent** tAdherent, int taille_logique);

/*
	programme:	supressAdherent
	auteur:		FOUCRAS Baptiste
	date:		01/01/21
	finalité:	Supprimer un adhérent du tableau tAdherent
*/
Adherent** supressAdherent(Adherent** tAdherent, int *taille_logique);

/*
	programme:	ajoutEmprunt
	auteur:		FOUCRAS Baptiste
	date:		07/01/21
	finalité:	Ajouter un emprunt avec contrôle de la possibilité d'emprunter à la liste d'emprunt
*/
void ajoutEmprunt(Emprunt* e, Jeux tJeux[], int taille_logique_tJeux, int idAdh, int *idJeu, Date date_emprunt);

/*
	programme:	infoReserv
	auteur:		FOUCRAS Baptiste
	date:		07/01/21
	finalité:	Permet de saisir toutes les informations d'une réservation, avec contrôle de saisie et de présence des ID dans les tableaux respectifs
*/
Date infoReserv(Adherent* tAdherent[], int taille_logique_tAdh, Jeux tJeux[], int taille_logique_tJeux, int *idAdh, int *idJeu, Date date_reserv);

/*
	programme:	ajoutReservation
	auteur:		FOUCRAS Baptiste
	date:		07/01/21
	finalité:	Ajouter une réservation à la liste de réservations
*/
void ajoutReservation(Adherent* tAdherent[], int taille_logique_tAdh, Jeux tJeux[], int taille_logique_tJeux , Reservation* r);
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

void retourJeux(Reservation *r, Emprunt *e, Jeux tJeux[], int nbJeux);

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

/*
	programme:	saveJeux
	auteur:		POLLET Matéo
	date:		07/01/21
	finalité:	Sauvegarder le tableau jeux dans le fichier jeu.don 
*/

void saveJeux(Jeux tJeux[], int nbJeux);

/*
	programme:	Fonctions pour emprunts
	auteur:		POLLET Matéo
	date:		07/01/21
	finalité:	Supprimer, et insérer un emprunt
*/

Emprunt* suppEmp(Emprunt* a);
Emprunt* suppressionEnTeteEM(Emprunt *a);
Emprunt* supprimerEM(Emprunt *a,int x);
void saveEmp(Emprunt *a);


void global();


Emprunt* listenouv(void);
/*
nom: listenouv
auteur : GAUGIRARD Florian
date : 23/12/2020
finalité : créer une nouvelle liste d'emprunts vide
*/


Emprunt* insertionEnTete(Emprunt *s, int emprunt, int adherent, int jeu, Date date);
/*
nom: insertionEnTete
auteur : GAUGIRARD Florian
date : 26/12/2020
finalité : inserer un maillon avant un autre
*/


Emprunt* inserer(Emprunt *e, int emprunt, int adherent, int jeu, Date date);
/*
nom: insérer
auteur : GAUGIRARD Florian
date : 23/12/2020
finalité : déterminer la position d'insertion d'un maillon
*/


Date lireFichier(FILE *flot, int *emprunt, int *adherent, int *jeu);
/*
nom: lireFIchier
auteur : GAUGIRARD Florian
date : 26/12/2020
finalité : lire une ligne du fichier de sauvagarde des emprunts
*/


Emprunt* chargeListeEmprunts(void);
/*
nom: chargeListeEmprunts
auteur : GAUGIRARD Florian
date : 26/12/2020
finalité : charger en mémoire les emprunts dans une liste
*/


void afficherListeEmprunts(Emprunt *e, Jeux tJeux[],int taille_logique,int taille_logique_A, Adherent* tAdherent[]);
/*
nom: afficherListeEmprunts
auteur : GAUGIRARD Florian
date : 27/12/2020
finalité : afficher la liste des emprunts en cours
*/


Booleen vide(Emprunt *e);
/*
nom: vide
auteur : GAUGIRARD Florian
date : 23/12/2020
finalité : vérifier si une liste est vide ou non
*/



Reservation* listenouvR(void);
/*
nom: listenouvR
auteur : GAUGIRARD Florian
date : 28/12/2020
finalité : créer une nouvelle liste de réservation vide
*/


Reservation* insertionEnTeteR(Reservation *s, int resa, int adherent, int jeu, Date date);
/*
nom: insertionEnTeteR
auteur : GAUGIRARD Florian
date : 28/12/2020
finalité : inserer un nouveau maillon avant un autre
*/


Reservation* insererR(Reservation *r, int resa, int adherent, int jeu, Date date);
/*
nom: insererR
auteur : GAUGIRARD Florian
date : 28/12/2020
finalité : déterminer la position d'insertion d'un maillon dans la liste des réservations
*/


Date lireFichierR(FILE *flot, int *resa, int *adherent, int *jeu);
/*
nom: lireFichierR
auteur : GAUGIRARD Florian
date : 28/12/2020
finalité : lire une ligne du fichie de sauvegarde des réservations
*/


Reservation* chargeListeResa(void);
/*
nom: listenouv
auteur : GAUGIRARD Florian
date : 02/01/2021
finalité : charger en mémoire la liste des réservations
*/


void afficherListeResa(Reservation *r, Adherent* tAdherent[], int taille_logique_A, Jeux tJeux[], int taille_logique);
/*
nom: afficherListeResa
auteur : GAUGIRARD Florian
date : 02/01/2021
finalité : affiche la liste des réservations
*/


Booleen videR(Reservation *r);
/*
nom: videR
auteur : GAUGIRARD Florian
date : 02/01/2021
finalité : vérifier si une liste de réservations est vide ou non
*/


void saveRes(Reservation *a);
/*
nom: saveRes
auteur : GAUGIRARD Florian
date : 03/01/2021
finalité : sauvegarder la liste des réservaions dans le fichier de sauvegarde
*/


Reservation* supprimer(Reservation *a,int x);
/*
nom: supprimer
auteur : GAUGIRARD Florian
date : 03/12/2020
finalité : déterminer la position d'un maillon à supprimer de la liste des réservaitons
*/


Reservation* suppressionEnTete(Reservation *a);
/*
nom: suppressionEnTete
auteur : GAUGIRARD Florian
date : 03/12/2020
finalité : supprimer un maillon de la liste des réservations
*/


Reservation* suppRes(Reservation *a);
/*
nom: suppRes
auteur : GAUGIRARD Florian
date : 03/12/2020
finalité : demander à l'utilisateur quelle réservation doit etre annulée et transmettre cette information à la bonne fonction
*/

void afficheListeCompleteEmp(Emprunt *e);
void afficheListeCompleteRes(Reservation *r);