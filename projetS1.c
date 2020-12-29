#include "projetS1.h"

void global()
{
	/* Comme cela, à chaque fois que le programme se lancera, il chargera automatiquement les fichiers en mémoire */
	
	//chargeAdherent();
	//chargeJeux();
	//chargeEmprunt();
	//chargeReservation();
	//menu();
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

Jeux chargeJeux(FILE *flot)
{
	/*
		Nom:		chargeJeux
		Finalité:	Charger une ligne du fichier pointé par *flot dans une structure Jeux.

		Description générale:
			prends les informations d'une ligne du fichier sur lequel pointe le flot, et le met dans les champs correspondant de j
			retourne la variable contenant le jeu

		Variables:
			flot	pointeur sur un fichier de données
			j		variable rendu par la fonction, de type Jeux et servant de conteneur pour les informations du fichier
	*/

	Jeux j;
	fscanf(flot, "%d%*c", &j.idJeux);
	fget(j.nom , 20, flot, '\t');
	fget(j.type , 15, flot, '\t');
	fscanf(flot, "%d", &j.quantite);
	return j;
}

Jeux *chargeTJeux(Jeux tJeux[], int *nbJeux, int *tMax)
{
	/*
		Nom:		chargeTJeux
		Finalité:	charger entièrement le fichier jeu.don dans le tableau tJeux, ligne par ligne. Retourne le tableau tJeux.

		Description générale:
			Renvoit le tableau tJeux alloué dynamiquement en mémoire.

		Variables:
			tJeux				tableau des Jeux disponibles.
			tMax				taille maximale physique du tableau tJeux
			jeu_fichier			pointeur ouvrant le fichier jeu.don
			j					variable intermédiaire pour charger les données du fichier don , et les transmettre ensuite vers le tableau
			tNouvJeux			tableau temporaire servant au realloc du tableau principal, pour augmenter sa taille
			nbJeux				nombre d'élément dans le tableau tJeux
	*/
	Jeux *tNouvJeux, j;
	FILE *jeu_fichier;
	jeu_fichier = fopen("jeu.don", "r");
	if (jeu_fichier == NULL)
	{
		printf("Problème lors de l'ouverture du fichier\n");
		return NULL;
	}
	*tMax = 5;
	tJeux = (Jeux *) malloc(*tMax * sizeof(Jeux));
	if (tJeux == NULL)
	{
		printf("Problème malloc\n");
		return NULL;
	}
	j = chargeJeux(jeu_fichier);
	while (!feof(jeu_fichier))
	{
		if (*nbJeux == *tMax)
		{
			*tMax = *tMax + 5;
			tNouvJeux = ((Jeux*) realloc (tJeux, *tMax *sizeof(Jeux)));
			if (tNouvJeux == NULL)
			{
				printf("Problème lors du realloc\n");
				return NULL;
			}
			tJeux = tNouvJeux;
		}
		tJeux[*nbJeux] = j;
		*nbJeux = *nbJeux + 1;
		j = chargeJeux(jeu_fichier);
	}
	fclose(jeu_fichier);
	return tJeux;
}

void afficheTJeux(Jeux tJeux[], int nbJeux)
{
	/*
		Nom:		afficheTJeux
		Finalité:	afficher le contenu du tableau tJeux triée par type de Jeux, puis par ordre alphabétique de leur nom

		Description générale:
			Affiche le contenu du tableau tJeux

		Variables:
			tJeux				tableau tJeux
			nbJeux				nombre d'éléments du tableau tJeux
			i					variable d'incrémentation pour le test de la boucle for
			cmp					Variable résultat d'une comparaison entre deux chaînes.
			pge					Plus grand nom alphabétiquement du tableau
			i					variable d'incrémentation pour le test de la boucle for
	*/

	//Tri du tableau par ordre alphabétique
	int pge, i, cmp;
	int n = nbJeux;
	while (n > 1)
	{
		pge = plusGrand(tJeux, n);
		echange(tJeux, pge, n-1);
		n = n-1;
	}

	//Logique
	printf("\nJeux de logique :\n\n");
	for(i = 0; i <= nbJeux-1; i++)
	{
		cmp = strcmp(tJeux[i].type, "Logique");
		if (cmp==0)
			printf("%03d\t%s\t%d restant(s)\n", tJeux[i].idJeux, tJeux[i].nom, tJeux[i].quantite);
	}

	//Plateau
	printf("\nJeux de plateau :\n\n");
	for(i = 0; i <= nbJeux-1; i++)
	{
		cmp = strcmp(tJeux[i].type, "Plateau");
		if (cmp==0)
			printf("%03d\t%s\t%d restant(s)\n", tJeux[i].idJeux, tJeux[i].nom, tJeux[i].quantite);
	}

	//Cartes
	printf("\nJeux de cartes :\n\n");
	for(i = 0; i <= nbJeux-1; i++)
	{
		cmp = strcmp(tJeux[i].type, "Cartes");
		if (cmp==0)
			printf("%03d\t%s\t%d restant(s)\n", tJeux[i].idJeux, tJeux[i].nom, tJeux[i].quantite);
	}

	//Construction
	printf("\nJeux de construction :\n\n");
	for(i = 0; i <= nbJeux-1; i++)
	{
		cmp = strcmp(tJeux[i].type, "Construction");
		if (cmp==0)
			printf("%03d\t%s\t%d restant(s)\n", tJeux[i].idJeux, tJeux[i].nom, tJeux[i].quantite);
	}

	//Tuiles
	printf("\nJeux de tuiles :\n\n");
	for(i = 0; i <= nbJeux-1; i++)
	{
		cmp = strcmp(tJeux[i].type, "Tuiles");
		if (cmp==0)
			printf("%03d\t%s\t%d restant(s)\n", tJeux[i].idJeux, tJeux[i].nom, tJeux[i].quantite);
	}
	
}

int plusGrand(Jeux tJeux[], int n)
{
	/*
		Nom:		plusGrand
		Finalité:	Compare  les noms des jeux entre-eux pour obtenir le plus grand alphabétiquement

		Description générale:
			Renvoie le plus grand nom alphabétiquement

		Variables:
			cmp					Variable résultat d'une comparaison entre deux chaînes.
			pge					Plus grand nom alphabétiquement du tableau
			i					variable d'incrémentation pour le test de la boucle for
	*/

	int i, pge = 0, cmp;
	for (i=1;i<n;i++)
	{
		cmp = strcmp (tJeux[i].nom, tJeux[pge].nom);
		if (cmp > 0)
			pge = i;
	}
	return pge;
}

void echange(Jeux tJeux[], int i, int j)
{
	/*
		Nom:		echange
		Finalité:	Echange les lignes du tableau pour les triées.

		Description générale:
			Echange les lignes du tableau pour les triées.

		Variables:
			auxID, auxQT		Variables int temporaires de l'ID et de la quantité
			auxNOM, auxTYPE		Variables char temporaires du nom et du type
	*/
	int auxID, auxQT;
	char auxNOM[20], auxTYPE[15];
	auxID = tJeux[i].idJeux;
	strcpy(auxNOM, tJeux[i].nom);
	strcpy(auxTYPE, tJeux[i].type);
	auxQT = tJeux[i].quantite;
	tJeux[i].idJeux = tJeux[j].idJeux;
	strcpy(tJeux[i].nom, tJeux[j].nom);
	strcpy(tJeux[i].type, tJeux[j].type);
	tJeux[i].quantite = tJeux[j].quantite;
	tJeux[j].idJeux = auxID;
	strcpy(tJeux[j].nom, auxNOM);
	strcpy(tJeux[j].type, auxTYPE);
	tJeux[j].quantite = auxQT;
}

Jeux *ajouterJeux(Jeux tJeux[], int *nbJeux, int *tMax)
{
	/*
		Nom:		ajouterJeux
		Finalité:	 Ajoute un jeu à tJeux et à la mémoire

		Description générale:
			Ajoute un jeu à tJeux et à la mémoire
			
		Variables:


	*/
	Jeux *tNouvJeux, j;
	int rep, i, cmp;
	printf("Nom du jeu :\n ");
	fgets(j.nom,20,stdin);
	j.nom[strlen(j.nom)-1] = '\0';
	printf("Nom lu : %s\n", j.nom);
	for(i = 0; i <= *nbJeux; i++)
	{
		cmp = strcmp(tJeux[i].nom, j.nom);
		if (cmp==0)
		{
			printf("Ce jeu existe déjà.\n");
			return NULL;
		}
	}
	printf("Nom lu : %s\n", j.nom);
	printf("Type :\n ");
	fgets(j.type,20,stdin);
	j.type[strlen(j.type)-1] = '\0';
	for(i = 0; i <= *nbJeux; i++)
	{
		cmp = strcmp(tJeux[i].type, j.type);
		if (cmp == 5)
		{
			printf("Cette catégorie n'existe pas.\n");
			return NULL;
		}
	}
	printf("Type lu : %s\n", j.type);
	printf("ID du jeu :\n");
	scanf(" %d%*c",&j.idJeux);
	for(i = 0; i <= *nbJeux; i++)
	{
		if (tJeux[i].idJeux == j.idJeux)
		{
			printf("Cet ID existe déjà.\n");
			return NULL;
		}
	}
	printf("Quantité :\n");
	scanf(" %d%*c",&j.quantite);
	if (tJeux == NULL)
	{
		printf("Problème malloc\n");
		return NULL;
	}
	if (*nbJeux == *tMax)
	{
		*tMax = *tMax + 5;
		tNouvJeux = ((Jeux*) realloc (tJeux, *tMax *sizeof(Jeux)));
		if (tNouvJeux == NULL)
		{
			printf("Problème lors du realloc\n");
			return NULL;
		}
		tJeux = tNouvJeux;
	}
	tJeux[*nbJeux] = j;
	*nbJeux = *nbJeux + 1;
	FILE *jeu_fichier;
	jeu_fichier = fopen("jeu.don","w");

	for(i = 0; i <= *nbJeux-1; i++)
	{
		fprintf(jeu_fichier, "%d\t%s\t%s\t%d\n", tJeux[i].idJeux, tJeux[i].nom, tJeux[i].type, tJeux[i].quantite);
	}
	fclose(jeu_fichier);

	return tJeux;

}

Jeux *supprimerJeux(Jeux tJeux[], int *nbJeux, int *tMax)
{
	/*
		Nom:		supprimerJeux
		Finalité:	 Supprime un jeu du tableau tJeux et de la mémoire

		Description générale:
			Supprime un jeu du tableau tJeux et de la mémoire

		Variables:


	*/
	Jeux *tNouvJeux, j;
	int rep, i, cmp;
	printf("ID du jeu à supprimer :\n ");
	scanf(" %d%*c",&j.idJeux);
	for(i = 0; i <= *nbJeux; i++)
	{
		if (tJeux[i].idJeux == j.idJeux)
		{
			printf("Trouve.\n");
			rep = 1;
			break;
		}
		rep = -1;
	}
	if (rep == -1)
	{
		printf("Ce jeu n'existe pas\n");
		return NULL;
	}
	rep = i;
	if (tJeux == NULL)
	{
		printf("Problème malloc\n");
		return NULL;
	}
	FILE *jeu_fichier;
	jeu_fichier = fopen("jeu.don","w");
	for(i = 0; i <= *nbJeux-1; i++)
	{
		if (i != rep)
			fprintf(jeu_fichier, "%d\t%s\t%s\t%d\n", tJeux[i].idJeux, tJeux[i].nom, tJeux[i].type, tJeux[i].quantite);
	}
	fclose(jeu_fichier);
	printf("Position : %d\nNombre de jeux : %d", rep, *nbJeux);
	if (rep >= *nbJeux+1)
		printf("Suppression impossible.");
	else
	{
		free(&tJeux[rep]);
		*nbJeux = *nbJeux - 1;
    	for (i = rep; i < *nbJeux; i++)
         	tJeux[i] = tJeux[i+1];
	}
	return tJeux;
}

void retourJeux(void)
{
	/*
		Nom:		retourJeux
		Finalité:	 Le retour déclenche l’examen des réservations pour peut être transformer une réservation en emprunt et faire parvenir le jeu à l’adhérent l’ayant réservé. 

		Description générale:
			Modifie la quantité d'un jeu, enlève un emprunt, et transforme (si possible) une réservation en emprunt.

		Variables:


	*/
	printf("Saisir l'ID de l'adhérent : ");
	//Saisie de l'ID de l'adhérent
	//Check quel jeu est emprunté par l'adhérent dans la liste emprunts.
	//Si aucun jeu n'est emprunté par l'adhérent -> Stop.
	//Si un jeu est emprunté par l'adhérent :
	//Suppresion de l'emprunt.
	//+1 dans la quantité du jeu en question dans tJeux.
	//Check si l'adhérent à d'autre réservation dans la liste réservations.
	//Si l'adhérent n'a aucune autre réservation -> Stop. 
	//Si l'adhérent a une autre réservation :
	//Prendre la réservation de l'adhérent la plus haute dans la liste réservation
	//Transformer la réservation en emprunt
	//-1 dans la quantité du jeu en question dans tJeux.
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
	int rep, bug;
	char get = '\n';
	Jeux *tJeux;
	int tMax = 100, nbJeux = 0;
	tJeux = chargeTJeux(tJeux, &nbJeux, &tMax);
	if(tJeux == NULL)
		return;
	while( get == '\n' )
	{
		system("@cls||clear"); //Clean de la console (fonctionne sur Windows/Linux/Mac)
		printf("Gestion d'une Ludothèque\n\n");
		printf("1. Jeux\n");
		printf("2. Adhérents\n");
		printf("3. Emprunts\n");
		printf("4. Réservation\n");
		scanf("%d%*c", &rep);
		switch(rep)
		{
			case 1:
				system("@cls||clear");
				printf("1. Afficher jeux disponibles\n2. Ajouter un jeu\n");
				printf("3. Retour d'un jeu\n4. Supprimer un jeu\n");
				printf("\n\n5. Retour au menu\n\n");
				scanf("%d%*c", &rep);
				switch(rep)
				{
					case 1:
						system("@cls||clear");
						afficheTJeux(tJeux, nbJeux);
						printf("\nAppuyez sur entrer pour continuer...\n");
						scanf("%c%*c", &get);
						break;
					case 2:
						system("@cls||clear");
						if(tJeux == NULL)
							return;
						tJeux = ajouterJeux(tJeux, &nbJeux, &tMax);
						printf("%d", &tJeux[1].idJeux);
						printf("\nAppuyez sur entrer pour continuer...\n");
						scanf("%c%*c", &get);
						break;
					case 3:
						system("@cls||clear");
						printf("C'est fonction n'est pas encore disponible.\n");
						printf("\nAppuyez sur entrer pour continuer...\n");
						scanf("%c%*c", &get);
						break;
					case 4:
						system("@cls||clear");
						if(tJeux == NULL)
							return;
						tJeux = supprimerJeux(tJeux, &nbJeux, &tMax);
						printf("\nAppuyez sur entrer pour continuer...\n");
						scanf("%c%*c", &get);
						break;
					case 5:
						break;
				}
				break;
			case 2:
				system("@cls||clear");
				// Fonction affichage emprunt
				printf("\nAppuyez sur entrer pour continuer...\n");
				scanf("%c%*c", &get);
				break;
			case 3:
				system("@cls||clear");
				// Fonction affichage emprunt
				printf("\nAppuyez sur entrer pour continuer...\n");
				scanf("%c%*c", &get);
				break;
			case 4:
				system("@cls||clear");
				// Fonction affichage emprunt
				printf("\nAppuyez sur entrer pour continuer...\n");
				scanf("%c%*c", &get);
				break;
			case 5:
				system("@cls||clear");
				// Fonction affichage emprunt
				printf("\nAppuyez sur entrer pour continuer...\n");
				scanf("%c%*c", &get);
				break;
			case 6:
				system("@cls||clear");
				// Fonction affichage emprunt
				printf("\nAppuyez sur entrer pour continuer...\n");
				scanf("%c%*c", &get);
				break;
			default:
				printf("\nErreur\n");
				break;
		}

	}	
}