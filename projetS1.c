#include "projetS1.h"

void fget(char *str , int max_saisie, FILE *flot, char char_arret)
{
	/*
		Nom:		fgets_like
		Finalité: 	Retourne un str contenant un nombre de caractères, avec un maximum de caractères définit, ou jusqu'à ce qu'il rencontre un certain caractère d'arrêt.
		Description générale:


		Variables:
		str			chaine de caractères qui servira de conteneur pour la fonction
		max_saisie	nombre entier maximal de charactères lu par la fonction
		flot		pointeur vers le fichier d'où est pris les informations de l'adhérent
		char_arret	charactère obligeant l'arrêt de la lecture par la fonction lors de son encontre
		i			variable d'incrémentation pour le test de la boucle while
	*/

	int i = 0;
	str[0] = '\0';
	while(i < max_saisie - 1) // ici on a décrémenté une fois, car c'est à partir de max saisie -1 que des erreurs se produisent
	{
		str[i] = (char)fgetc(flot);
		if(str[i] == char_arret)
		{
			break;
		}
		i++;
	}
	str[i] = '\0';
}

Adherent chargeAdherent(FILE *flot)
{
	/*
		Nom:		chargeAdherent
		Finalité:	charger une ligne du fichier pointé par *flot dans une structure Adherent.

		Description générale:
			renvoit par adresse la taille logique du tableau

		Variables:
			flot	pointeur sur un fichier de données
			a		variable rendu par la fonction, de type Adherent et servant de conteneur pour les informations du fichier
	*/

	Adherent a;
	char toto[22];
	fscanf(flot, "%d%*c%s%*c", &a.idAdherent, a.civilite);
	fget(a.nom , 22, flot, '\t');
	fget(a.prenom , 22, flot, '\t');
	fscanf(flot, "%d/%d/%d", &a.date_inscrip.jour, &a.date_inscrip.mois, &a.date_inscrip.annee);
	return a;
}

int chargTAdherent( Adherent* tAdherent[], int taille_physique)
{
	/*
		Nom:		chargTAdherent
		Finalité:	charger le fichier adherent.don dans le tableau de pointeurs tAdherent.

		Description générale:
			renvoit par adresse la taille logique du tableau

		Variables:
			tAdherent			tableau de pointeurs d'Adherent
			taille_physique		taille maximale physique du tableau tAdherent
			adherent_fichier	pointeur ouvrant le fichier adherent.don
			nouv_adhe			variable intermédiaire pour charger les données du fichier don , et les transmettre ensuite vers le tableau
			tNouvAdherent		tableau de pointeur, servant au realloc du tableau principal, pour augmenter sa taille
			taille_logique		variable qui permet de connaitre le nombre de pointeurs dans le tableau tAdherent, renvoyé par return
	*/

	FILE *adherent_fichier;
	Adherent nouv_adhe, **tNouvAdherent;
	int taille_logique = 0;
	adherent_fichier = fopen("adherent", "r");
	nouv_adhe = chargeAdherent(adherent_fichier);

	fclose(adherent_fichier);
	return taille_logique;
}