#include "projetS1.h"

void global()
{
	/* Comme cela, à chaque fois que le programme se lancera, il chargera automatiquement les fichiers en mémoire */
	
	//chargeAdherent();
	//chargeJeu();
	//chargeEmprunt();
	//chargeReservation();
	menu();
}

void fget(char *str , int max_saisie, FILE *flot, char char_arret)
{
	/*
		Nom:		fget
		Finalité: 	Retourne par adresse un str contenant un maximum de caractères définit pris d'un fichier, ou jusqu'à ce qu'il rencontre un certain caractère d'arrêt.
		Description générale:
			initialise le str passé en paramètre à '\0', pour éviter d'y avoir n'importe quoi
			tant que le nombre d'itérations est strictement inférieur au nombre max_saisie - 1 ( -1 pour garder une place pour le \0) il est fait:
				stocke dans l'index de str, correspondant au nombre d'itération, un charactère pris depuis le fichier pointé par flot
				teste si jamais le charactère pris équivaut à celui qui doit arrêter la fonction
					si oui la boucle while se brise
				on incrémente i de 1, pour converger vers max_saisie - 1 dans le test, et stocker le prochain caractère
			on ajoute à la fin du str complété un '\0'


		Variables:
		str			chaine de caractères qui servira de conteneur pour la fonction
		max_saisie	nombre entier maximal de charactères lu par la fonction
		flot		pointeur vers le fichier d'où est pris les informations de l'adhérent
		char_arret	charactère obligeant l'arrêt de la lecture par la fonction lors de son encontre
		i			variable d'incrémentation pour le test de la boucle for
	*/

	int i = 0;
	str[0] = '\0';
	for(i = 0; i < max_saisie - 1; i++) // le choix est fait ici de mettre a -1, pour que à l'appel de la fonction, on appelle directement avec le nombre de place de str
	{
		str[i] = (char)fgetc(flot);
		if(str[i] == char_arret)
		{
			break;
		}
	}
	str[i] = '\0';
}

Adherent chargeAdherent(FILE *flot)
{
	/*
		Nom:		chargeAdherent
		Finalité:	Charger une ligne du fichier pointé par *flot dans une structure Adherent.

		Description générale:
			prends les informations d'une ligne du fichier sur lequel pointe le flot, et le met dans les champs correspondant de a
			retourne la variable contenant l'adherent

		Variables:
			flot	pointeur sur un fichier de données
			a		variable rendu par la fonction, de type Adherent et servant de conteneur pour les informations du fichier
	*/

	Adherent a;
	fscanf(flot, "%d%*c%s%*c", &a.idAdherent, a.civilite);
	fget(a.nom , 22, flot, '\t');
	fget(a.prenom , 22, flot, '\t');
	fscanf(flot, "%d/%d/%d", &a.date_inscrip.jour, &a.date_inscrip.mois, &a.date_inscrip.annee);
	return a;
}

int chargTAdherent( Adherent* tAdherent[], int *taille_physique)
{
	/*
		Nom:		chargTAdherent
		Finalité:	charger entièrement le fichier adherent.don dans le tableau de pointeurs tAdherent, ligne par ligne. Retourne la taille logique de tAdherent,
					et par adresse tAdherent.

		Description générale:
			renvoit par adresse la taille logique du tableau

		Variables:
			tAdherent			tableau de pointeurs d'Adherent
			taille_physique		taille maximale physique du tableau tAdherent
			adherent_fichier	pointeur ouvrant le fichier adherent.don
			nouv_adhe			variable intermédiaire pour charger les données du fichier don , et les transmettre ensuite vers le tableau
			tNouvAdherent		tableau de pointeur, servant au realloc du tableau principal, pour augmenter sa taille
			taille_logique		nombre d'élément dans le tableau tAdherent, renvoyé par return
	*/

	FILE *adherent_fichier;
	Adherent nouv_adhe, **tNouvAdherent;
	int taille_logique = 0;
	adherent_fichier = fopen("adherent.don", "r");
	if(adherent_fichier == NULL)
	{
		printf("Erreur lors de l'ouverture du fichier\n");
		return -1;
	}
	nouv_adhe = chargeAdherent(adherent_fichier);
	while(!feof(adherent_fichier))
	{
		if(taille_logique == *taille_physique)
		{
			printf("Le tableau est trop petit, ajout de 5 espaces");
			tNouvAdherent = (Adherent**) realloc (tAdherent, (*taille_physique + 5) * sizeof(Adherent*));
			if(tNouvAdherent == NULL)
			{
				printf("Problème lors du realloc, la mémoire n'a pû être allouée.\n");
				return -1;
			}
			else
			{
				tAdherent = tNouvAdherent;
				*taille_physique += 5; // on ne prends en compte le changement de taille physique que si le realloc à marché, pour garder une taille physique réelle
			}
		}
		tAdherent[taille_logique] = (Adherent*) calloc (1, sizeof(Adherent));
		if(tAdherent[taille_logique] == NULL)
		{
			printf("Problème de calloc, la mémoire n'a pas été allouée.\n");
			return -1;
		}
		*tAdherent[taille_logique] = nouv_adhe;
		taille_logique ++;
		nouv_adhe = chargeAdherent(adherent_fichier);
	}
	tAdherent[taille_logique] = (Adherent*) calloc (1, sizeof(Adherent));
	*tAdherent[taille_logique] = nouv_adhe;
	fclose(adherent_fichier);
	return taille_logique;
}

void afficheTAdherent(Adherent* tAdherent[], int taille_logique)
{
	/*
		Nom:		afficheTAdherent
		Finalité:	afficher le contenu des pointeurs du tableau tAdherent

		Description générale:
			renvoit par adresse la taille logique du tableau

		Variables:
			tAdherent			tableau de pointeurs d'Adherent
			taille_logique		nombre d'éléments du tableau tAdherent
			i					variable d'incrémentation pour le test de la boucle for
	*/

	int i;
	printf("idAdherent\tcivilité\tnom\tprénom\tdate d'inscription (JJ/MM/YYYY)\n");
	for(i = 0; i <= taille_logique; i++)
	{
		printf("%03d\t%s\t", tAdherent[i]->idAdherent, tAdherent[i]->civilite);
		printf("%s\t%s\t", tAdherent[i]->nom, tAdherent[i]->prenom);
		printf("%02d/%02d/%02d\n", tAdherent[i]->date_inscrip.jour, tAdherent[i]->date_inscrip.mois, tAdherent[i]->date_inscrip.annee);
	}
}

void menu()
{
	/*
		Nom:		menu
		Finalité:	Accéder aux fonctions nécéssaire au bon fonctionnement de la gestion d'une ludothèque facilement.

		Description générale:
			Choisir une fonction en tapant un nombre.

		Variables:
			rep					Réponse de l'utilisateur
			bug					Retour d'une fonction si il y a
			get					Variable utilisé pour appuyer sur une touche pour continuer
	*/

	/* Note temporaire : Pour les noms des variables j'étais à court d'inspiration, je fixerais plus tard, ou alors si vous avez des idées vous pouvez fixe aussi */
	/* Note temporaire : Je vais trouver un autre moyen de rendre le menu un peu plus "pro" */
	
	system("@cls||clear"); //Clean de la console (fonctionne sur Windows/Linux/Mac)
	int rep, bug;
	char get;
	printf("1. Jeux disponibles\n");
	printf("2. Emprunts en cours\n");
	printf("3. Réservation d'un jeu\n");
	printf("4. Nouvel emprunt/réservation\n");
	printf("5. Retour d'un jeu\n");
	printf("6. Annuler une réservation\n");
	scanf("%d",& rep);
	if (rep==1)
	{
		system("@cls||clear");
		printf("Jeu(x) disponible(s) :\n");
		// Fonction affichage jeu
		printf("\nAppuyez sur une touche pour continuer...\n");
		scanf("%c%*c", &get);
	}
	if (rep==2)
	{
		system("@cls||clear");
		printf("Emprunt(s) en cours :\n");
		// Fonction affichage emprunt
		printf("\nAppuyez sur une touche pour continuer...\n");
		scanf("%c%*c", &get);
	}
	if (rep==3)
	{
		system("@cls||clear");
		// Fonction affichage emprunt
		printf("\nAppuyez sur une touche pour continuer...\n");
		scanf("%c%*c", &get);
	}
	if (rep==4)
	{
		system("@cls||clear");
		// Fonction affichage emprunt
		printf("\nAppuyez sur une touche pour continuer...\n");
		scanf("%c%*c", &get);
	} 
	if (rep==5)
	{
		system("@cls||clear");
		// Fonction affichage emprunt
		printf("\nAppuyez sur une touche pour continuer...\n");
		scanf("%c%*c", &get);
	}
	if (rep==6)
	{
		system("@cls||clear");
		// Fonction affichage emprunt
		printf("\nAppuyez sur une touche pour continuer...\n");
		scanf("%c%*c", &get);
	}
	menu();
}