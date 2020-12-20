#include "projetS1.h"

void fgets_like(char str[] , int max_saisie, FILE *flot, char char_arret)
{
	/*
		Nom:		fgets_like
		Finalité: 	Prends un nombre de caractères, avec un maximum de caractère définit en second argument, ou jusqu'à ce qu'il rencontre un certain caractère,
					définit en dernier argument
		Description générale:


		Variables:
		i	variable d'incrémentation pour le test de la boucle while
	*/
	int i;
	str[0] = '\0';
	while(i < max_saisie - 1)
	{
		str[i] = fgetc(flot);
		str[i + 1] = '\0';
		if(str[i] == char_arret)
		{
			break;
		}
		i++;
	}
}

int chargTAdherent( Adherent* tAdherent[], int taille_physique)
{
	/*
		Nom:		chargTAdherent
		Finalité:	charger le fichier adherent.don dans le tableau de pointeurs tAdherent.

		Description générale:
			renvoit par adresse la taille logique du tableau

		Variables:
			adherent_fichier	pointeur ouvrant le fichier adherent.don
			nouv_adhe			variable intermédiaire pour charger les données du fichier don , et les transmettre ensuite vers le tableau
			tNouvAdherent		tableau de pointeur, servant au realloc du tableau principal, pour augmenter sa taille
			taille_logique		variable qui permet de connaitre le nombre de pointeurs dans le tableau tAdherent, renvoyé par return
	*/

	FILE *adherent_fichier;
	Adherent nouv_adhe, **tNouvAdherent;
	int taille_logique = 0;
	adherent_fichier = fopen("adherent", "r");


	fclose(adherent_fichier);
	return taille_logique;
}