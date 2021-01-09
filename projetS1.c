#include "projetS1.h"

/*
	Fonctions globales, utilisables partout
*/

void global(void)
{
	/* Comme cela, à chaque fois que le programme se lancera, il chargera automatiquement les fichiers en mémoire */
	
	//chargeAdherent();
	//chargeJeux();
	//chargeEmprunt();
	//chargeReservation();
	//menu();
}

Date current_date(void)
{
	/*
		Nom:		current_date
		Finalité: 	Retourner la date de l'ordinateur, grâce à time.h
		Description générale:
			déclaration d'une structure Date
			Déclaration d'une structure time_t (provenant de time.h), type retourné par la fonction time
			Déclaration d'une struct tm, qui correspond au format calendaire de la date, et qui contiendra l'heure locale grace à la fonction local_time
			concaténation dans la struct date des variables de tm contenant le jour, le mois et l'année
			retourne la date obtenue par concaténation


		Variables:
		jour_actuel			variable de type Date, servant de conteneur pour la date actuelle
		t					variable de type time_t provenant de time.h, et contenant le nombre de secondes depuis le 1er Janvier 1970
		jour_heure_actuel	variable de type tm, provenant de time.h, et contenant divers entier comme l'année, le jour, l'heure exact, le fuseau horaire...
	*/
	Date jour_actuel;
	time_t t = time(NULL); // définition de la variable t, de type time_t; time renvoie le nombre de seconde depuis le 1er janv 1970
	// structure stockant divers variables comme les années, les mois, le jour, l'heure précise...
  	struct tm jour_heure_actuel = *localtime(&t); // local_time prends en entrée un type time_t, et renvoie l'adresse d'une struc tm contenant l'heure locale
  	jour_actuel.jour = jour_heure_actuel.tm_mday;
  	jour_actuel.mois = jour_heure_actuel.tm_mon + 1; // les mois sont numérotés de 0 à 11, il faut ajouter 1 pour avoir le mois actuel
  	jour_actuel.annee = jour_heure_actuel.tm_year + 1900; // les années débutent au début du référencement informatique du calendrier, donc 1900
	return jour_actuel;
}

Date saisie_date(void)
{
	/*
		Nom:		saisie_date
		Finalité: 	Saisir une date avec contrôle complet de la saisie
		Description générale:
			


		Variables:
		date			variable de type Date, servant de conteneur à la fonction
		date_actuelle	variable contenant la date exacte d'aujourd'hui
		choix			variable pour valider une saisie d'informations
	*/
	Date date, date_actuelle;
	char choix = 'n';

	date_actuelle = current_date();
	
	while(choix == 'n' || choix == 'N')
	{
		printf("Saisissez le jour voulu:\t");
		scanf("%d%*c", &date.jour);
		while(date.jour < 1 || date.jour > 31)
		{
			printf("Le jour se trouve entre 1 et 31. Re-saisissez le jour voulu:\t");
			scanf("%d%*c", &date.jour);
		}

		printf("Saisissez le mois voulu:\t");
		scanf("%d%*c", &date.mois);
		while(date.mois < 1 || date.mois > 12)
		{
			printf("Le mois se trouve entre 1 et 12. Re-saisissez le mois voulu:\t");
			scanf("%d%*c", &date.mois);
		}

		printf("Saisissez l'année voulue:\t");
		scanf("%d%*c", &date.annee);
		while(date.annee < 0)
		{
			printf("L'année ne peut être négative! Saisissez l'année voulu:\t");
			scanf("%d%*c", &date.annee);
		}

		if(date.annee < 100)
		{
			date.annee += 2000;
		}
		if(date_actuelle.annee - date.annee >= 1)
		{
			printf("Êtes-vous sûr de votre saisie? La date saisie est %d ans plus tôt que la date actuelle. (o/n)\n", date_actuelle.annee - date.annee);
			scanf("%c%*c", &choix);
			while(choix != 'o' && choix != 'O' && choix != 'n' && choix != 'N')
			{
				printf("Choix non reconnu. Êtes-vous sûr de votre saisie? La date saisie est %d ans plus tôt que la date actuelle. (o/n)\n", date_actuelle.annee - date.annee);
				scanf("%c%*c", &choix);
			}
		}
		else if(date_actuelle.annee - date.annee <= -1)
		{
			printf("Êtes-vous sûr de votre saisie? La date saisie est %d ans plus tard que la date actuelle. (o/n)\n", -(date_actuelle.annee - date.annee));
			scanf("%c%*c", &choix);
			while(choix != 'o' && choix != 'O' && choix != 'n' && choix != 'N')
			{
				printf("Choix non reconnu. Êtes-vous sûr de votre saisie? La date saisie est %d ans plus tôt que la date actuelle. (o/n)\n", -(date_actuelle.annee - date.annee));
				scanf("%c%*c", &choix);
			}
		}
		else choix = 'o';
	}
	return date;
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
		str[i + 1] = '\0';
		if(str[i] == char_arret)
		{
			break;
		}
	}
	str[i] = '\0';
}

/*
	Fonction de traitement du fichier adherent.don
*/

Adherent** decaleADroite_Adherent(Adherent** tAdherent, int taille_logique, int limite)
{
	/*
		Nom:		decaleADroite_Adherent
		Finalité: 	Décale à droite à partir de l'index limite tout les éléments du tableau de pointeurs d'adhérent
		Description générale:
			du dernier pointeur du tableau jusqu'à celui avant celui spécifié par la limite:
				le pointeur de l'index courant sera égal au pointeur précédent, et pointera sur le même adhérent que celui précédent
			on retourne tAdherent une fois le traitement de décalage terminé


		Variables:
		tAdherent		tableau trié de pointeurs sur des Adhérents
		taille_logique	nombre de pointeurs dans le tableau tAdherent
		limite			index du tableau tAdherent jusqu'où le décalage se fera
		i				variable d'incrémentation pour le test de la boucle for
	*/
	int i;
	for(i = taille_logique; i > limite; i--)
	{
		tAdherent[i] = tAdherent[i - 1];
	}
	return tAdherent;
}

Adherent** decaleAGauche_Adherent(Adherent** tAdherent, int taille_logique, int debut)
{
	/*
		Nom:		decaleAGauche_Adherent
		Finalité: 	Décale à gauche à partir de l'index pos_insert tout les éléments du tableau de pointeurs d'adhérent
		Description générale:
			du pointeur à l'index indiqué par debut jusqu'au dernier pointeur:
				le pointeur de l'index courant sera égal au pointeur suivant, et pointera donc sur le même adhérent que celui suivant
			on retourne tAdherent une fois le traitement de décalage terminé


		Variables:
		tAdherent		tableau trié de pointeurs sur des Adhérents
		taille_logique	nombre de pointeurs dans le tableau tAdherent
		debut			index du tableau tAdherent jusqu'où le décalage se fera
		i				variable d'incrémentation pour le test de la boucle for
	*/
	int i;
	for(i = debut; i < taille_logique; i++)
	{
		tAdherent[i] = tAdherent[i + 1];
	}
	return tAdherent;
}

int recherchDich_Adhe(Adherent **tAdherent, int taille_logique, int *trouve, int idAdherent)
{
	/*
		Nom:		recherchDich_Adhe
		Finalité: 	retourne la position d'insertion de l'id d'adhérent, et informe si il est déjà présent ou non dans le tableau tAdherent
		Description générale:
			la borne inf prends pour valeur le premier index du tableau, sup prends pour valeur le dernier index du tableau
			trouve est mis à 0 (pour être sûr de ce qu'il y a dedans)
			tant que la borne inférieure est inférieure ou égale à la borne supérieure
				middle prends la valeur du milieu (ou arrondi à défaut) entre les deux autres bornes
				on teste si jamais l'id recherché est inférieure ou égal à l'id sur lequel le pointeur situé a l'index du milieu
					si jamais c'est le cas, on baisse la borne supérieure à celle du milieu - 1 (car l'id recherché est peut etre à gauche du la borne milieu)
				sinon l'id récherché est peut être à droite de la borne milieu, on augmente donc la borne inf  à middle + 1
				on teste si jamais l'id recherché est égal strictement à l'id sur lequel le pointeur situé à l'index du milieu
					si c'est le cas on affecte à 1 trouve (indiquant que la valeur est trouvé)
				sinon on ne fait rien, trouve reste à 0, indiquant que la valeur n'a pas été trouvé
			on retourne ensuite inf, qui est l'index soit d'insertion de la valeur, soit où la valeur à été trouvé


		Variables:
		tAdherent		tableau trié de pointeurs sur des Adhérents
		taille_logique	nombre de pointeurs dans le tableau tAdherent
		trouve			pointeur sur une adresse, indiquant si l'id recherché à été trouvé dans le tableau trié tAdherent (1 si oui, 0 sinon)
		idAdherent		valeur recherchée dans la tableau tAdherent
		inf				borne inférieure, augmentant si jamais l'id adherent du milieu est inférieur ou égal à celui recherché
		middle			borne du mileu, donc l'id adherent du pointeur dans le tableau a l'index middle sera comparé à celui recherché
		sup				borne supérieure, baissant si jamais l'id adherent du milieu est supérieur à celui recherché
	*/
	int inf = 0, middle, sup = taille_logique - 1;
	*trouve = 0;
	while(inf <= sup)
	{
		middle = (inf + sup) / 2;
		if(idAdherent <= tAdherent[middle]->idAdherent)
			sup = middle - 1;
		else inf = middle + 1;
		if(idAdherent == tAdherent[middle]->idAdherent)
			*trouve = 1;
	}
	return inf;
}

int recherche_Jeux(Jeux *tJeux, int taille_logique, int idJeu)
{
	/*
		Nom:		recherchDich_Jeux
		Finalité: 	retourne la position d'insertion de l'id de jeu, et informe si il est déjà présent ou non dans le tableau tJeux
		Description générale:
			la borne inf prends pour valeur le premier index du tableau, sup prends pour valeur le dernier index du tableau
			trouve est mis à 0 (pour être sûr de ce qu'il y a dedans)
			tant que la borne inférieure est inférieure ou égale à la borne supérieure
				middle prends la valeur du milieu (ou arrondi à défaut) entre les deux autres bornes
				on teste si jamais l'id recherché est inférieure ou égal à l'id sur lequel le pointeur situé a l'index du milieu
					si jamais c'est le cas, on baisse la borne supérieure à celle du milieu - 1 (car l'id recherché est peut etre à gauche du la borne milieu)
				sinon l'id récherché est peut être à droite de la borne milieu, on augmente donc la borne inf  à middle + 1
				on teste si jamais l'id recherché est égal strictement à l'id sur lequel le pointeur situé à l'index du milieu
					si c'est le cas on affecte à 1 trouve (indiquant que la valeur est trouvé)
				sinon on ne fait rien, trouve reste à 0, indiquant que la valeur n'a pas été trouvé
			on retourne ensuite inf, qui est l'index soit d'insertion de la valeur, soit où la valeur à été trouvé


		Variables:
		tJeux			tableau trié de pointeurs sur des Adhérents
		taille_logique	nombre de pointeurs dans le tableau tAdherent
		trouve			pointeur sur une adresse, indiquant si l'id recherché à été trouvé dans le tableau trié tAdherent (1 si oui, 0 sinon)
		idJeu			valeur recherchée dans la tableau tJeux
		inf				borne inférieure, augmentant si jamais l'id adherent du milieu est inférieur ou égal à celui recherché
		middle			borne du mileu, donc l'id adherent du pointeur dans le tableau a l'index middle sera comparé à celui recherché
		sup				borne supérieure, baissant si jamais l'id adherent du milieu est supérieur à celui recherché
	*/
	int i;
	for(i = 0; i < taille_logique; i++)
	{
		if(idJeu == tJeux[i].idJeux)
		{
			return i;
		}
	}
	return -1;
}

Adherent chargeAdherent(FILE *flot)
{
	/*
		Nom:		chargeAdherent
		Finalité:	Charger une ligne du fichier pointé par *flot dans une structure Adherent.

		Description générale:
			prends les informations d'une ligne du fichier sur lequel pointe le flot, et le met dans les champs correspondant de a
			fget permettra de prendre des noms et prénoms à espace (rares mais possibles)
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

Adherent** chargTAdherent( Adherent* tAdherent[], int *taille_logique, int *taille_physique)
{
	/*
		Nom:		chargTAdherent
		Finalité:	charger entièrement le fichier adherent.don dans le tableau de pointeurs tAdherent, ligne par ligne. Retourne la taille logique de tAdherent,
					et par adresse tAdherent.

		Description générale:
			

		Variables:
			tAdherent			tableau de pointeurs d'Adherent
			taille_physique		taille maximale physique du tableau tAdherent
			fichier_adherent	pointeur ouvrant le fichier adherent.don
			nouv_adhe			variable intermédiaire pour charger les données du fichier don , et les transmettre ensuite vers le tableau
			tNouvAdherent		tableau de pointeur, servant au realloc du tableau principal, pour augmenter sa taille
			taille_logique		nombre d'élément dans le tableau tAdherent, renvoyé par return
	*/

	FILE *fichier_adherent;
	Adherent nouv_adhe, **tNouvAdherent;
	fichier_adherent = fopen("adherent.don", "r");
	if(fichier_adherent == NULL)
	{
		printf("Erreur lors de l'ouverture du fichier\n");
		return NULL;
	}

	tAdherent = (Adherent**) malloc (*taille_physique * sizeof(Adherent*));
	// chargement dans ma variable une ligne du fichier
	nouv_adhe = chargeAdherent(fichier_adherent);
	while(!feof(fichier_adherent))
	{

		// On ajoute des espaces si jamais le nombre max d'élements du tableau est atteint
		if(*taille_logique == *taille_physique)
		{
			printf("Le tableau est trop petit, ajout de 5 espaces\n");
			tNouvAdherent = (Adherent**) realloc (tAdherent, (*taille_physique + 5) * sizeof(Adherent*));

			if(tNouvAdherent == NULL)
			{
				printf("Problème lors du realloc, la mémoire n'a pû être allouée.\n");
				return NULL;
			}
			else
			{
				tAdherent = tNouvAdherent;
				*taille_physique += 5; // on ne prends en compte le changement de taille physique que si le realloc à marché, pour garder une taille physique réelle
			}
		}

		// on alloue la place pour l'adherent
		tAdherent[*taille_logique] = (Adherent*) calloc (1, sizeof(Adherent));
		if(tAdherent[*taille_logique] == NULL)
		{
			printf("Problème de calloc, la mémoire n'a pas été allouée.\n");
			return NULL;
		}

		// on ajoute l'adherent au tableau et on incrémente le nombre d'élements dans le tableau
		*tAdherent[*taille_logique] = nouv_adhe;
		(*taille_logique) ++;

		// on recharge un nouvel adherent
		nouv_adhe = chargeAdherent(fichier_adherent);
	}
	fclose(fichier_adherent);
	return tAdherent;
}

void afficheTAdherent(Adherent* tAdherent[], int taille_logique)
{
	/*
		Nom:		afficheTAdherent
		Finalité:	afficher le contenu des pointeurs du tableau tAdherent

		Description générale:
			affiche la présentation des données
			tant qu'il n'a pas répété 
			affiche tout les adhérents du tableau tAdherent

		Variables:
			tAdherent			tableau de pointeurs d'Adherent
			taille_logique		nombre d'éléments du tableau tAdherent
			i					variable d'incrémentation pour le test de la boucle for
	*/

	int i;
	printf("idAdherent\tcivilité\tnom\tprénom\tdate d'inscription (JJ/MM/YYYY)\n");
	for(i = 0; i < taille_logique; i++)
	{
		printf("%03d\t%s\t", tAdherent[i]->idAdherent, tAdherent[i]->civilite);
		printf("%s\t%s\t", tAdherent[i]->nom, tAdherent[i]->prenom);
		printf("%02d/%02d/%02d\n", tAdherent[i]->date_inscrip.jour, tAdherent[i]->date_inscrip.mois, tAdherent[i]->date_inscrip.annee);
	}
}

Adherent** ajoutAdherent(Adherent* tAdherent[], int *taille_logique, int *taille_physique)
{
	/*
		Nom:		ajoutAdherent
		Finalité:	Insérer un adhérent dans le tableau trié tAdherent et dans le fichier adherent.don

		Description générale:
			renvoit par adresse la taille logique du tableau

		Variables:
			tAdherent			tableau de pointeurs d'Adherent
			taille_logique		nombre d'éléments du tableau tAdherent
			taille_physique		variable d'incrémentation pour le test de la boucle for
	*/

	Adherent a, **tNouvAdherent;
	int pos_insert = 0, trouve = 0;
	char validation = 'o', choix;

	// Choix de la position de l'adhérent
	printf("Saisissez d'abord un identifiant pour votre nouvel adhérent:\t");
	scanf("%d%*c", &a.idAdherent); // le choix est libre de faire une saisie de l'identifiant nous mêmes, car nous ne savons si les id sont données dans l'ordre ou non

	pos_insert = recherchDich_Adhe(tAdherent, *taille_logique, &trouve, a.idAdherent);
	while(trouve == 1)
	{
		printf("L'identifiant saisi existe déjà. Veuillez en sélectionner un nouveau:\t");
		scanf("%d%*c", &a.idAdherent);
		pos_insert = recherchDich_Adhe(tAdherent, *taille_logique, &trouve, a.idAdherent);
	}
	while(validation != 'n' && validation != 'N')
	{
		if(validation == 'q' || validation == 'Q')
		{
			printf("Annulation de la saisie d'un nouvel adherent.\n");
			return tAdherent;
		}

		printf("Quelle est la civilité (Mr / Mme) du nouvel adherent:\n");
		scanf("%s%*c", a.civilite);
		while(strcmp(a.civilite, "Mr") != 0)
		{
			if(strcmp(a.civilite, "Mme") == 0)
				break;
			printf("Civilité non valide, quelle est la civilité (Mr / Mme) du nouvel adherent:\n");
			scanf("%s%*c", a.civilite);
		}
		printf("Quel est le nom du nouvel ahdherent?\n");
		fgets(a.nom, 20, stdin);
		a.nom[strlen(a.nom) - 1] = '\0';
		printf("Quel est le prénom du nouvel ahdherent?\n");
		fgets(a.prenom, 20, stdin);
		a.prenom[strlen(a.prenom) - 1] = '\0';
		printf("Voici les informations de l'adherent %d:\n", a.idAdherent);
		printf("%s\t%s\t%s\n", a.civilite, a.nom, a.prenom);
		printf("Voulez vous ressaisir les informations? (n/N pour valider la saisie, q pour annuler)\n");
		scanf("%c%*c", &validation);
	}

	printf("Voulez-vous une date d'inscription automatique? (o/n)");
	scanf("%c%*c", &choix);
	if(choix == 'o' || choix == 'O')
		a.date_inscrip = current_date();
	else a.date_inscrip = saisie_date();


	if(*taille_logique == *taille_physique)
	{
		printf("Le tableau est trop petit, ajout d'un espace mémoire\n");
		printf("%d\n", tAdherent[*taille_logique - 1]->idAdherent);
		tNouvAdherent = (Adherent**) realloc (tAdherent, (*taille_physique + 1) * sizeof(Adherent*));
		if(tNouvAdherent == NULL)
		{
			printf("Problème lors du realloc, la mémoire n'a pû être allouée.\n");
			return NULL;
		}
		else
		{
			tAdherent = tNouvAdherent;
			(*taille_physique) ++; // on ne prends en compte le changement de taille physique que si le realloc à marché, pour garder une taille physique réelle
		}
	}
	tAdherent = decaleADroite_Adherent(tAdherent, *taille_logique, pos_insert);

	tAdherent[pos_insert] = (Adherent*) calloc (1, sizeof(Adherent));
	if(tAdherent[pos_insert] == NULL)
	{
		printf("Problème de calloc");
		return NULL;
	}

	*tAdherent[pos_insert] = a;
	(*taille_logique)++;
	return tAdherent;
}

void EnregistrerTAdherent(Adherent** tAdherent, int taille_logique)
{
	FILE *fichier_adherent;
	int i;
	fichier_adherent = fopen("adherent.don", "w");
	if(fichier_adherent == NULL)
	{
		printf("Problème lors de l'ouverture du fichier en mode écriture");
		return;
	}
	for(i = 0; i < taille_logique; i++)
	{
		fprintf(fichier_adherent, "%d\t%s\t", tAdherent[i]->idAdherent, tAdherent[i]->civilite);
		fprintf(fichier_adherent, "%s\t%s\t", tAdherent[i]->nom, tAdherent[i]->prenom);
		fprintf(fichier_adherent, "%02d/%02d/%02d\n", tAdherent[i]->date_inscrip.jour, tAdherent[i]->date_inscrip.mois, tAdherent[i]->date_inscrip.annee);
	}
	fprintf(fichier_adherent, "\n");
	fclose(fichier_adherent);
	printf("L'enregistrement s'est bien déroulé sans soucis.\n");
}

Adherent** modifAdherent(Adherent** tAdherent, int taille_logique)
{
	int pos_modif = 0, trouve = 0, idAdhe;
	char choix, choix_date;
	printf("Saisissez d'abord un identifiant pour l'adhérent modifié:\t");
	scanf("%d%*c", &idAdhe); // le choix est libre de faire une saisie de l'identifiant nous mêmes, car nous ne savons si les id sont données dans l'ordre ou non

	pos_modif = recherchDich_Adhe(tAdherent, taille_logique, &trouve, idAdhe);
	while(trouve == 0)
	{
		printf("L'identifiant saisi n'existe pas. Veuillez en sélectionner un nouveau:\t");
		scanf("%d%*c", &idAdhe);
		pos_modif = recherchDich_Adhe(tAdherent, taille_logique, &trouve, idAdhe);
	}
	printf("Voici les informations actuelles de l'adherent sélectionné:\n");
	printf("%03d\t%s\t", tAdherent[pos_modif]->idAdherent, tAdherent[pos_modif]->civilite);
	printf("%s\t%s\t", tAdherent[pos_modif]->nom, tAdherent[pos_modif]->prenom);
	printf("%02d/%02d/%02d\n", tAdherent[pos_modif]->date_inscrip.jour, tAdherent[pos_modif]->date_inscrip.mois, tAdherent[pos_modif]->date_inscrip.annee);
	printf("Voulez-vous modifier les informations? (o/n)\t");
	scanf("%c%*c", &choix);
	while(choix != 'o' && choix != 'O' && choix != 'n' && choix != 'N')
	{
		printf("Choix non reconnu. Voulez-vous modifier les informations? (o/n)\t");
		scanf("%c%*c", &choix);
	}
	if(choix == 'o' || choix == 'O')
	{
		choix = 'n';
		while(choix == 'n' || choix == 'N')
		{
			printf("Quelle est la civilité (Mr / Mme) de l'adhérent modifié:\n");
			scanf("%s%*c", tAdherent[pos_modif]->civilite);
			while(strcmp(tAdherent[pos_modif]->civilite, "Mr") != 0)
			{
				if(strcmp(tAdherent[pos_modif]->civilite, "Mme") == 0)
					break;
				printf("Civilité non valide, quelle est la civilité (Mr / Mme) de l'ahdherent modifié:\n");
				scanf("%s%*c", tAdherent[pos_modif]->civilite);
			}
			printf("Quel est le nom de l'adherent modifié?\n");
			fgets(tAdherent[pos_modif]->nom, 20, stdin);
			tAdherent[pos_modif]->nom[strlen(tAdherent[pos_modif]->nom) - 1] = '\0';
			printf("Quel est le prénom de l'adherent modifié?\n");
			fgets(tAdherent[pos_modif]->prenom, 20, stdin);
			tAdherent[pos_modif]->prenom[strlen(tAdherent[pos_modif]->prenom) - 1] = '\0';
			printf("Voici les informations de l'adhérent %d:\n", tAdherent[pos_modif]->idAdherent);
			printf("%s\t%s\t%s\n", tAdherent[pos_modif]->civilite, tAdherent[pos_modif]->nom, tAdherent[pos_modif]->prenom);
			printf("Validez-vous les modifications apportées jusque présent? (o/n)\t");
			scanf("%c%*c", &choix);
			while(choix != 'o' && choix != 'O' && choix != 'n' &&choix != 'N')
			{
				printf("Choix non reconnu. Voulez-vous modifier les informations? (o/n)\t");
				scanf("%c%*c", &choix);
			}
		}

		printf("Voulez-vous une date d'inscription automatique? (o/n)");
		scanf("%c%*c", &choix_date);
		if(choix_date == 'o' || choix_date == 'O')
			tAdherent[pos_modif]->date_inscrip = current_date();
		else tAdherent[pos_modif]->date_inscrip = saisie_date();
		printf("Voici les informations actuelles de l'adherent sélectionné:\n");
		printf("%03d\t%s\t", tAdherent[pos_modif]->idAdherent, tAdherent[pos_modif]->civilite);
		printf("%s\t%s\t", tAdherent[pos_modif]->nom, tAdherent[pos_modif]->prenom);
		printf("%02d/%02d/%02d\n", tAdherent[pos_modif]->date_inscrip.jour, tAdherent[pos_modif]->date_inscrip.mois, tAdherent[pos_modif]->date_inscrip.annee);
	}
	else printf("Modification annulée.");
	return tAdherent;
}

Adherent** supressAdherent(Adherent** tAdherent, int *taille_logique)
{
	int idAdhe, pos_supress, trouve;
	char choix_modif = 'n';
	while(choix_modif == 'n' || choix_modif == 'N')
	{
		printf("Quel numéro d'adherent voulez vous supprimer?\t");
		scanf("%d%*c", &idAdhe);

		pos_supress = recherchDich_Adhe(tAdherent, *taille_logique, &trouve, idAdhe);
		while(trouve == 0)
		{
			printf("Numéro non reconnu. Quel numéro d'adherent voulez vous supprimer?\t");
			scanf("%d%*c", &idAdhe);
			pos_supress = recherchDich_Adhe(tAdherent, *taille_logique, &trouve, idAdhe);
		}
		printf("Les informations de l'adherent à supprimer sont les suivantes:\n");
		printf("%03d\t%s\t", tAdherent[pos_supress]->idAdherent, tAdherent[pos_supress]->civilite);
		printf("%s\t%s\t", tAdherent[pos_supress]->nom, tAdherent[pos_supress]->prenom);
		printf("%02d/%02d/%02d\n", tAdherent[pos_supress]->date_inscrip.jour, tAdherent[pos_supress]->date_inscrip.mois, tAdherent[pos_supress]->date_inscrip.annee);
		printf("Est-ce que l'adhérent sélectionné est bien celui que vous souhaitez supprimer? (o/n, q pour quitter)\n");
		scanf("%c%*c", &choix_modif);
		while(choix_modif != 'o' && choix_modif != 'O' && choix_modif != 'n' && choix_modif != 'N' && choix_modif != 'q' && choix_modif != 'Q')
		{
			printf("Choix non reconnu. Voulez-vous modifier les informations? (o/n)\t");
			scanf("%c%*c", &choix_modif);
		}
		if(choix_modif == 'q' || choix_modif == 'Q')
		{
			printf("Suppression annulée\n");
			return tAdherent;
		}
	}
	tAdherent = decaleAGauche_Adherent(tAdherent, *taille_logique, pos_supress);
	(*taille_logique) --;
	return tAdherent;
}

Emprunt* ajoutEmprunt(Emprunt* e, Jeux tJeux[], int taille_logique_tJeux, int idAdh, int *idJeu, Date date_emprunt)
{
	Emprunt *e_parcours = e;
	int idEmprunt = 0, nb_emp_cours = 0, index_jeu = 0;

	// on check si l'emprunteur possède bien moins de 3 emprunts en cours
	while( e_parcours != NULL)
	{
		if(e_parcours->idAdherent == idAdh)
			nb_emp_cours ++;
		e_parcours = e_parcours->suiv;
	}
	if(nb_emp_cours >= 3)
	{
		printf("Vous avez déjà trois ou plus emprunts en cours! Vous ne pouvez plus empruntez!\n");
		return e;
	}

	// on vérifie s'il reste le jeu demandé existe, et s'il est en stock, pour continuer l'emprunt
	index_jeu =  recherche_Jeux(tJeux, taille_logique_tJeux, *idJeu);
	while(index_jeu == -1)
	{
		printf("Le jeu demandé n'existe pas. Veuillez en sélectionner un nouveau:\n");
		scanf("%d%*c", idJeu);
		index_jeu =  recherche_Jeux(tJeux, taille_logique_tJeux, *idJeu);
	}
	
	if(tJeux[index_jeu].quantite <= 0)
	{
		printf("Le jeu saisi n'est plus en stock, vous ne pouvez l'empruntez.\n");
		return e;
	}

	// la saisie est donc valide, on prends un id d'emprunt de plus 1 par rapport au dernier
	e_parcours = e;
	while(e_parcours->suiv != NULL)
	{
		e_parcours = e_parcours->suiv;
	}
	idEmprunt = e_parcours->idEmprunt + 1;
	e = inserer(e, idEmprunt, idAdh, *idJeu, date_emprunt);
	return e;
}

Date infoReserv(Adherent* tAdherent[], int taille_logique_tAdh, Jeux tJeux[], int taille_logique_tJeux, int *idAdh, int *idJeu, Date date_reserv)
{
	int trouve = 0, pos_jeu = 0;
	char choix;
	*idAdh = 0;
	*idJeu = 0;
	// contrôle de saisie de l'id de l'adherent
	printf("Quel est l'id d'adherent de la nouvelle réservation?\n");
	scanf("%d%*c", idAdh);
	// on cherche juste à savoir si l'id est trouvé, peu importe sa position
	recherchDich_Adhe(tAdherent, taille_logique_tAdh, &trouve, *idAdh);
	while(trouve == 0)
	{
		printf("L'id d'adherent saisie n'est pas référencé. Saisissez un nouvel id d'adherent:\n");
		scanf("%d%*c", idAdh);
		recherchDich_Adhe(tAdherent, taille_logique_tAdh, &trouve, *idAdh);
	}

	// contrôle de saisie de l'id du jeux
	printf("Quel est l'id du jeu de la nouvelle réservation?\n");
	scanf("%d%*c", idJeu);
	// on cherche juste à savoir si l'id est trouvé, peu importe sa position
	pos_jeu = recherche_Jeux(tJeux, taille_logique_tJeux, *idJeu);
	while(pos_jeu == -1)
	{
		printf("L'id du jeu saisie n'est pas référencé. Saisissez un nouvel id de jeu?\n");
		scanf("%d%*c", idJeu);
		pos_jeu = recherche_Jeux(tJeux, taille_logique_tJeux, *idJeu);
	}
	printf("Voulez-vous une date de réservation automatique? (o/n)");
	scanf("%c%*c", &choix);
	while(choix != 'o' && choix != 'O' && choix != 'n' && choix != 'N')
	{
		printf("Choix non reconnnu. Voulez-vous une date de réservation automatique? (o/n)");
		scanf("%c%*c", &choix);
	}
	if(choix == 'o' || choix == 'O')
		return current_date();
	else return saisie_date();
}

Reservation* ajoutReservation(Adherent* tAdherent[], int taille_logique_tAdh, Jeux tJeux[], int taille_logique_tJeux , Reservation* r)
{
	Reservation *r_parcours = r;
	int idAdh_nouv = 0, idJeux_nouv = 0, idReservation = 0;
	Date date_reservation_nouv;

	// insertion et contrôle des données de la nouvelle réservation
	date_reservation_nouv = infoReserv(tAdherent, taille_logique_tAdh, tJeux, taille_logique_tJeux, &idAdh_nouv, &idJeux_nouv, date_reservation_nouv);

	// on prends un id de réservation de plus 1 par rapport au dernier
	while(r_parcours->suiv != NULL)
	{
		r_parcours = r_parcours->suiv;
	}
	idReservation = r_parcours->idRes + 1;
	r = insererR(r, idReservation, idAdh_nouv, idJeux_nouv, date_reservation_nouv);
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

Jeux* chargeTJeux(Jeux tJeux[], int *nbJeux, int *tMax)
{
	/*
		Nom:		chargeTJeux
		Finalité:	charger entièrement le fichier jeu.don dans le tableau tJeux, ligne par ligne. Retourne le tableau tJeux.

		Description générale:
			Renvoit le tableau tJeux alloué dynamiquement en mémoire.

		Variables:
			tJeux				Tableau des Jeux disponibles.
			tMax				Taille maximale physique du tableau tJeux
			jeu_fichier			Pointeur ouvrant le fichier jeu.don
			j					Variable intermédiaire pour charger les données du fichier don , et les transmettre ensuite vers le tableau
			tNouvJeux			Tableau temporaire servant au realloc du tableau principal, pour augmenter sa taille
			nbJeux				Nombre d'élément dans le tableau tJeux
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
	tJeux = (Jeux *) malloc(*tMax * sizeof(Jeux)); //Malloc d'un tableau pour 5 éléments.
	if (tJeux == NULL)
	{
		printf("Problème malloc\n");
		return NULL;
	}
	j = chargeJeux(jeu_fichier);
	int y = 0;
	while (!feof(jeu_fichier)) // Lecture du fichier.
	{
		if (*nbJeux == *tMax) // Ajout de 5 de taille physique si tableau trop petit.
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
	int pge, i, y, z,cmp, tMax = 1, lg;
	int n = nbJeux;
	char typeTmp[15] = "TYPE";
	/*
	while (n > 1)
	{
		pge = plusGrand(tJeux, n, 2);
		echange(tJeux, pge, n-1);
		n = n-1;
	}
	
	n = nbJeux;
	*/
	while (n > 1)
	{
		pge = plusGrand(tJeux, n);
		echange(tJeux, pge, n-1);
		n = n-1;
	}

    //Logique
    printf("Jeux de logique :\n\n");
    for(i = 0; i <= nbJeux-1; i++)
    {
        cmp = strcmp(tJeux[i].type, "Logique");
        if (cmp==0)
		{
			lg = strlen(tJeux[i].nom);
            if (lg <= 7) printf("%03d\t%s\t\t%d restant(s)\n", tJeux[i].idJeux, tJeux[i].nom, tJeux[i].quantite);
			else printf("%03d\t%s\t%d restant(s)\n", tJeux[i].idJeux, tJeux[i].nom, tJeux[i].quantite);
		}
    }

    //Plateau
	printf("--------------------\n");
    printf("Jeux de plateau :\n\n");
    for(i = 0; i <= nbJeux-1; i++)
    {
        cmp = strcmp(tJeux[i].type, "Plateau");
        if (cmp==0)
		{
			lg = strlen(tJeux[i].nom);
            if (lg <= 7) printf("%03d\t%s\t\t%d restant(s)\n", tJeux[i].idJeux, tJeux[i].nom, tJeux[i].quantite);
			else printf("%03d\t%s\t%d restant(s)\n", tJeux[i].idJeux, tJeux[i].nom, tJeux[i].quantite);
		}
    }

    //Cartes
	printf("--------------------\n");
    printf("Jeux de cartes :\n\n");
    for(i = 0; i <= nbJeux-1; i++)
    {
        cmp = strcmp(tJeux[i].type, "Cartes");
        if (cmp==0)
		{
			lg = strlen(tJeux[i].nom);
            if (lg <= 7) printf("%03d\t%s\t\t%d restant(s)\n", tJeux[i].idJeux, tJeux[i].nom, tJeux[i].quantite);
			else printf("%03d\t%s\t%d restant(s)\n", tJeux[i].idJeux, tJeux[i].nom, tJeux[i].quantite);
		}
    }

    //Construction
	printf("--------------------\n");
    printf("Jeux de construction :\n\n");
    for(i = 0; i <= nbJeux-1; i++)
    {
        cmp = strcmp(tJeux[i].type, "Construction");
        if (cmp==0)
		{
			lg = strlen(tJeux[i].nom);
            if (lg <= 7) printf("%03d\t%s\t\t%d restant(s)\n", tJeux[i].idJeux, tJeux[i].nom, tJeux[i].quantite);
			else printf("%03d\t%s\t%d restant(s)\n", tJeux[i].idJeux, tJeux[i].nom, tJeux[i].quantite);
		}
    }

    //Tuiles
	printf("--------------------\n");
    printf("Jeux de tuiles :\n\n");
    for(i = 0; i <= nbJeux-1; i++)
    {
        cmp = strcmp(tJeux[i].type, "Tuiles");
        if (cmp==0)
		{
			lg = strlen(tJeux[i].nom);
            if (lg <= 7) printf("%03d\t%s\t\t%d restant(s)\n", tJeux[i].idJeux, tJeux[i].nom, tJeux[i].quantite);
			else printf("%03d\t%s\t%d restant(s)\n", tJeux[i].idJeux, tJeux[i].nom, tJeux[i].quantite);
		}
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
			tJeux: Tableau de jeux.
			nbJeux : Nombre de jeux.
			tMax : Taille physique du tableau.
			tNouvJeux : Tableau temporaire pour realloc.
			j : Tableau temporaire pour savoir si le nom et l'ID n'exsite pas déjà dans le tableau.
			i : Variable pour parcourir le tableau.
			cmp : Variable de comparaison entre deux chaînes.
			rep : Variable temporaire pour le switch.
	*/
	Jeux *tNouvJeux, j;
	int rep, i, cmp;
	printf("Nom du jeu :\n");
	fgets(j.nom,20,stdin);
	j.nom[strlen(j.nom)-1] = '\0';
	for(i = 0; i <= *nbJeux; i++) // Recherche pour savoir si le nom du jeu est déjà pris.
	{
		cmp = strcmp(tJeux[i].nom, j.nom);
		if (cmp==0)
		{
			printf("Ce jeu existe déjà.\n");
			return tJeux;
		}
	}
	printf("Type :\n\n1. Cartes\t3. Logique\t5. Tuiles\n2. Construction\t4. Plateau\n");
	scanf("%d", &rep);
	switch(rep)
	{
		case 1: strcpy(j.type, "Cartes"); break;
		case 2: strcpy(j.type, "Construction"); break;
		case 3: strcpy(j.type, "Logique"); break;
		case 4: strcpy(j.type, "Plateau"); break;
		case 5: strcpy(j.type, "Tuiles"); break;
	}
	printf("ID du jeu :\n");
	scanf(" %d%*c",&j.idJeux);
	for(i = 0; i <= *nbJeux; i++) // Recherche pour savoir si l'ID du jeu est déjà pris.
	{
		if (tJeux[i].idJeux == j.idJeux)
		{
			printf("Cet ID existe déjà.\n");
			return tJeux;
		}
	}
	printf("Quantité :\n");
	scanf(" %d%*c",&j.quantite);
	if (tJeux == NULL) //Sécurité pour malloc
	{
		printf("Problème malloc\n");
		return NULL;
	}
	if (*nbJeux == *tMax) // Allocation du jeu.
	{
		*tMax = *tMax + 5;
		tNouvJeux = ((Jeux*) realloc (tJeux, *tMax *sizeof(Jeux)));
		if (tNouvJeux == NULL)
		{
			printf("Problème lors du realloc\n");
			return tJeux;
		}
		tJeux = tNouvJeux;
	}
	tJeux[*nbJeux] = j;
	*nbJeux = *nbJeux + 1;
	saveJeux(tJeux, *nbJeux);
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
			j : Tableau temporaire
			rep : Savoir si l'élément a été trouvé + permet de supprimer au bon endroit.
			i : Variable pour parcourir le tableau.
			cmp : Variable de comparaison entre deux chaînes.
			jeu_fichier : Jeu fichier.
			tJeux: Tableau de jeux.
			nbJeux : Nombre de jeux.
			tMax : Taille physique du tableau.
	*/
	Jeux j;
	int rep, i, cmp;
	printf("ID du jeu à supprimer :\n ");
	scanf(" %d%*c",&j.idJeux);
	for(i = 0; i <= *nbJeux; i++) //Parcour du tableau jusqu'à trouver l'élément voulu.
	{
		if (tJeux[i].idJeux == j.idJeux)
		{
			rep = 1;
			break;
		}
		rep = -1;
	}
	if (rep == -1)
	{
		printf("Ce jeu n'existe pas.\n");
		return tJeux;
	}
	rep = i; //La variable "rep" prend la valeur de l'emplacement de l'élément voulu pour pouvoir supprimer au bon endroit par la suite.
	if (tJeux == NULL)
	{
		printf("Problème malloc\n");
		return NULL;
	}
	FILE *jeu_fichier;
	jeu_fichier = fopen("jeu.don","w");
	for(i = 0; i <= *nbJeux-1; i++) //Suppression dans le fichier.
	{
		if (i != rep)
			fprintf(jeu_fichier, "%d\t%s\t%s\t%d\n", tJeux[i].idJeux, tJeux[i].nom, tJeux[i].type, tJeux[i].quantite);
	}
	fclose(jeu_fichier);

	if (rep >= *nbJeux+1) //Une petite sécurité, au cas où.
		printf("Suppression impossible.");
	else
	{
		free(&tJeux[rep]);
		*nbJeux = *nbJeux - 1;
    	for (i = rep; i < *nbJeux; i++) //Décalage à droite pour supprimer du tableau.
         	tJeux[i] = tJeux[i+1];
	}
	return tJeux;
}

void retourJeux(Reservation *r, Emprunt *e, Jeux tJeux[], int nbJeux)
{
	/*
		Nom:		retourJeux
		Finalité:	 Le retour déclenche l’examen des réservations pour peut être transformer une réservation en emprunt et faire parvenir le jeu à l’adhérent l’ayant réservé. 

		Description générale:
			Modifie la quantité d'un jeu, enlève un emprunt, et transforme (si possible) une réservation en emprunt.

		Variables:
		idEmprunt : Variable pour l'ID d'emprunt.
		idAdh : Variable pour l'ID d'adhérent.
		id : Variable pour l'ID.
		z : Vérification si l'adhérent a un emprunt/une réservation.
		i : Variable pour boucle for.
		rep : Variable temporaire.
	*/
	int idEmprunt = 0, idAdh = 0, id = 0, z = 0, i = 0, rep = 0;
	Emprunt *e_parcours = e;
	Reservation *r_parcours = r;
	printf("Saisir l'ID de l'adhérent : ");
	scanf("%d%*c", &idAdh);
	printf("Les jeux empruntés par cet adhérent sont :\n");
	while (e_parcours != NULL) //Parcours de la liste emprunt et du tableau jeux pour afficher idEmprunt et nom du jeu.
	{
		if(e_parcours->idAdherent == idAdh)
		{
			for(i = 0; i <= nbJeux-1; i++)
			{
				if (tJeux[i].idJeux == e_parcours->idJeu)
				{
					printf("[%03d]\t%s\n", e_parcours->idEmprunt, tJeux[i].nom);
					z++;
				}
			}
		}
		e_parcours = e_parcours->suiv;
	}
	if (z == 0)
	{
		printf("Aucun jeu n'est emprunté par cet adhérent.\n");
		return;
	}
	e_parcours = e;
	printf("Veuillez entrer le numéro de l'emprunt à retourner :\n");
	scanf("%d", &id);
	while (e_parcours != NULL) //Parcours de la liste emprunt et du tableau jeux pour rajouter +1 à la quantité du jeu.
	{
		if(e_parcours->idEmprunt == id)
		{
			for(i = 0; i <= nbJeux-1; i++)
			{
				if (tJeux[i].idJeux == e_parcours->idJeu)
				{
					tJeux[i].quantite = tJeux[i].quantite + 1;
				}
			}
		}
		e_parcours = e_parcours->suiv;
	}
	e=supprimerEM(e,id);
	saveEmp(e);

	saveJeux(tJeux, nbJeux);
	printf("Le jeu a été retourné.\n\nRéservations en attente :\n"); z=0;
	while (r_parcours != NULL) //Parcours de la liste réservation et du tableau jeux pour afficher idReservation et nom du jeu.
	{
		if(r_parcours->idAdherent == idAdh)
		{
			for(i = 0; i <= nbJeux-1; i++)
			{
				if (tJeux[i].idJeux == r_parcours->idJeu && tJeux[i].quantite <= 0)
					printf("[%03d]\t%s\t(Rupture de stock !)\n", r_parcours->idRes, tJeux[i].nom);
				if (tJeux[i].idJeux == r_parcours->idJeu && tJeux[i].quantite > 0)
				{
					printf("[%03d]\t%s\n", r_parcours->idRes, tJeux[i].nom);
					z++;
				}
			}
		}
		r_parcours = r_parcours->suiv;
	}

	if (z == 0)
	{
		printf("Aucune réservation en attente.\n");
		return;
	}
	r_parcours = r;
	printf("\nVeuillez entrer le numéro du jeu à emprunter : ");
	scanf("%d", &id);
	
	while (r_parcours != NULL) //Parcours de la liste réservation et du tableau jeux pour enlever -1 la quantité du stock ou empêcher la transformation sur pas assez de stock.
	{
		if(r_parcours->idRes == id)
		{
			for(i = 0; i <= nbJeux-1; i++)
			{
				if (tJeux[i].idJeux == r_parcours->idJeu && tJeux[i].quantite > 0)
					tJeux[i].quantite = tJeux[i].quantite - 1;
				if (tJeux[i].idJeux == r_parcours->idJeu && tJeux[i].quantite <= 0)
				{
					printf("Ce jeu n'est plus en stock.\n");
					return;
				}
			}
		}
		r_parcours = r_parcours->suiv;
	}
	e_parcours = e;
	r_parcours = r;
    while(e_parcours->suiv != NULL) //Obtention du dernier IDEmprunt et rajout +1 pour la transformation de la réservation en emprunt.
    {
        e_parcours = e_parcours->suiv;
    }
	idEmprunt = e_parcours->idEmprunt + 1;
	while (r_parcours != NULL) //Insertion
	{
		if(r_parcours->idRes == id)
		{
			e = inserer(e, idEmprunt, r_parcours->idAdherent, r_parcours->idJeu, r_parcours->dateR);
		}
		r_parcours = r_parcours->suiv;
	}
	r=supprimer(r,id);
	saveRes(r);
	saveEmp(e);
	
	saveJeux(tJeux, nbJeux);

	printf("\nRéservation réussie\n.");
}

void saveJeux(Jeux tJeux[], int nbJeux)
{
	/*
		Nom:		saveJeux
		Finalité:	Sauvegarder le tableau jeux dans le fichier jeu.don 

		Description générale:
			Sauvegarder le tableau jeux dans le fichier jeu.don 

		Variables:
		jeu_fichier : Jeu fichier.
		i : Pour boucle for.
	*/
	FILE *jeu_fichier;
	int i = 0;
	jeu_fichier = fopen("jeu.don","w");
	for(i = 0; i <= nbJeux-1; i++)
	{
			fprintf(jeu_fichier, "%d\t%s\t%s\t%d\n", tJeux[i].idJeux, tJeux[i].nom, tJeux[i].type, tJeux[i].quantite);
	}
	fclose(jeu_fichier);
	return;
}

/*
		Nom:		Fonctions pour emprunts
		Finalité:	Supprimer, et insérer un emprunt

		Variables:
		id : Id d'un emprunt.
		a : Liste emprunt alternative.
		x : Valeur à ajouter/supprimer.
		flot : Fichier emprunt.
*/

Emprunt* suppEmp(Emprunt* a)
{
	int id;
	printf("Veuillez entrer le numéro de l'emprunt à retourner :\n");
	scanf("%d", &id);
	a=supprimerEM(a,id);
	saveEmp(a);
	return a;
}

Emprunt* supprimerEM(Emprunt *a, int x)
{
	if(a==NULL)
		return a;
	if(x < a->idEmprunt)
		return a;
	if(x==a->idEmprunt)
	{
		return suppressionEnTeteEM(a);
	}
	a->suiv=supprimerEM(a->suiv,x);
	return a;
}

Emprunt* suppressionEnTeteEM(Emprunt *a) 
{
	Emprunt *b;
	if (a==NULL) {
		printf("op interdite\n");
		exit(1);
	}
	b=a;
	a=a->suiv; 
	free(b);
	return a;
}


void saveEmp(Emprunt *a) 
{
	FILE *flot;
	flot=fopen("Emprunts.don","w");
	if (flot==NULL)
		printf("Problème d'ouverture du fichier des réservations en écriture, sauvegarde des réservations impossible\n");
	while (a!=NULL) {
		fprintf(flot, "%d\t%d\t%d\t%d/%d/%d\n", a->idEmprunt,a->idAdherent,a->idJeu,a->dateEmprunt.jour,a->dateEmprunt.mois,a->dateEmprunt.annee);
		a=a->suiv;
	}
	fclose(flot);
}


void menu(void)
{
	/*
		Nom:		menu
		Finalité:	Accéder aux fonctions nécessaires au bon fonctionnement de la gestion d'une ludothèque facilement.

		Description générale:
			Choisir une fonction en tapant un nombre.

		Variables:
			rep		Réponse de l'utilisateur
			bug		Retour d'une fonction si il y a
			get		Variable utilisé pour appuyer sur une touche pour continuer
	*/

	/* Note temporaire : Pour les noms des variables j'étais à court d'inspiration, je fixerais plus tard, ou alors si vous avez des idées vous pouvez fixe aussi */
	/* Note temporaire : Je vais trouver un autre moyen de rendre le menu un peu plus "pro" */
	int rep, bug;
	char get = '\n';
	Jeux *tJeux;
	Adherent **tAdherent;
	int taille_physique = 9, taille_logique = 0;
	char choix;
	tAdherent = chargTAdherent( tAdherent, &taille_logique, &taille_physique);
	int tMax = 100, nbJeux = 0, i = 0;
	tJeux = chargeTJeux(tJeux, &nbJeux, &tMax);
	Emprunt *e;
	Reservation *r;
	e = chargeListeEmprunts();
	r = chargeListeResa();
	while( get == '\n' )
	{
		system("@cls||clear"); //Clean de la console (fonctionne sur Windows/Linux/Mac)
		printf("Gestion d'une Ludothèque\n\n");
		printf("1. Jeux\n");
		printf("2. Adhérents\n");
		printf("3. Emprunts\n");
		printf("4. Réservations\n");
		printf("\n9. Quitter le programme\n");
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
						fflush(stdin);
						getchar();
						break;
					case 2:
						system("@cls||clear");
						if(tJeux == NULL)
							return;
						tJeux = ajouterJeux(tJeux, &nbJeux, &tMax);
						printf("\nAppuyez sur entrer pour continuer...\n");
						fflush(stdin);
						getchar();
						break;
					case 3:
						system("@cls||clear");
						retourJeux(r, e, tJeux, nbJeux);
						printf("\nAppuyez sur entrer pour continuer...\n");
						fflush(stdin);
						getchar();
						break;
					case 4:
						system("@cls||clear");
						if(tJeux == NULL)
							return;
						tJeux = supprimerJeux(tJeux, &nbJeux, &tMax);
						printf("\nAppuyez sur entrer pour continuer...\n");
						fflush(stdin);
						getchar();
						break;
					case 5:
						break;
				}
				break;
			case 2:
				system("@cls||clear");
				// Fonction affichage emprunt
				printf("\nAppuyez sur entrer pour continuer...\n");
				fflush(stdin);
				getchar();
				break;
			case 3:
				system("@cls||clear");
				// Fonction affichage emprunt
				printf("\nAppuyez sur entrer pour continuer...\n");
				fflush(stdin);
				getchar();
				break;
			case 4:
				system("@cls||clear");
				// Fonction affichage emprunt
				printf("\nAppuyez sur entrer pour continuer...\n");
				fflush(stdin);
				getchar();
				break;
			case 5:
				system("@cls||clear");
				// Fonction affichage emprunt
				printf("\nAppuyez sur entrer pour continuer...\n");
				fflush(stdin);
				getchar();
				break;
			case 6:
				system("@cls||clear");
				// Fonction affichage emprunt
				printf("\nAppuyez sur entrer pour continuer...\n");
				fflush(stdin);
				getchar();
				break;
			case 9:
				return;
			default:
				printf("\nErreur\n");
				break;
		}

	}	
}


Reservation* suppressionEnTete(Reservation *a) {
/*
nom : suppressionEnTete
finalité : supprimer la premiere réservation
description générale : la focntion prend en argument le premier maillon de la liste des réservations, la supprimer, et renvoie le maillon suivant comme étant le nouveau premier maillon. ENfin, elle renvoie la
						nouvelle liste à la fonction appelante
variable : 	*a : liste avant la suppression
			*b : liste apres la suppression du premier maillon
*/

  Reservation *b;
  if (a==NULL) {
    printf("op interdite\n");
    exit(1);
  }
  b=a;
  a=a->suiv; 
  free(b);
  return a;
}

Reservation* supprimer(Reservation *a,int x) {
/*
nom : supprimer
finalité : determiner la place d'une réservation dans une liste pour la supprimer
description générale : la fonction prend en argument la liste des réservations ainsi que l'id de la réservation à supprimer, détermine la fonction a utiliser en fonction de sa position dans la liste et 
						execute cette dite fonction. Enfin, elle renvoie la nouvelle liste à la fonction appelante.
variable : 	*a : liste des réservations
			x : id de la réservation à supprimer
*/
  if(a==NULL)
    return a;
  if(x < a -> idRes)
    return a;
  if(x==a->idRes)
    return suppressionEnTete(a);
  a->suiv=supprimer(a->suiv,x);
  return a;
}

Reservation* suppRes(Reservation *a) {
/*
nom : suppRes
finalité : supprimer la premiere réservationa liste des réservations
description générale : demande à l'utilisateur quelle réservations il/elle veut annuler, communique toutes ces informations à la bonne fonction,
						enregistre dans le fichier texte, et enfin renvoie la liste finale à la fonction qui l'a appelé.
variable : 	*a : liste des réservations
			id : identifiant de la réservation
*/
	int id;
	printf("Veuillez entrer le numéro de réservation à annuler :\n");
	scanf("%d", &id);
	a=supprimer(a,id);
	saveRes(a);
	return a;
}

void saveRes(Reservation *a) {
/*
nom : saveRes
finalité : enregistrer la liste des réservations dans un fichier
description générale : la fonction prend en argument la liste des réservations et essaye d'ouvrir le ficher de sauvegarde en mode lecture. S'il y parvient, il enregistre, sinon il previent l'utilisateur
variable : 	*a : liste des réservations
			flot : pointeur vers le fichier de sauvegarde
*/
	FILE *flot;
	flot=fopen("Reservation.don","w");
	if (flot==NULL)
		printf("Problème d'ouverture du fichier des réservations en écriture, sauvegarde des réservations impossible\n");
	while (a!=NULL) {
		fprintf(flot, "%d\t%d\t%d\t%d/%d/%d\n", a->idRes,a->idAdherent,a->idJeu,a->dateR.jour,a->dateR.mois,a->dateR.annee);
		a=a->suiv;
	}
	fclose(flot);

}

Booleen vide(Emprunt *e) {
/*
nom : vide
finalité : vérifier si une liste est vide
description générale : la fonction prend en argumentune liste et verifie si elle est vide ou non. si oui, elle renvoie vrai, sinon elle renvoie faux.
variable : 	*e : liste des réservations
*/
    if(e==NULL)
    	return vrai;
	return faux;
}

void afficherListeEmprunts(Emprunt *e, Jeux tJeux[],int taille_logique, int taille_logique_A, Adherent* tAdherent[]) {
/*
nom : afficherListeEmprunts
finalité : afficher la liste des emprunts en cours (date, nom et prenom de l'adhérent et nom du jeu)
description générale : La fonction prend en argument la liste des emprunts, le tableau des jeux et des adhrents, ainsi que leur taille logique. 
						Elle va regarder la liste des emprunts chercher le nom et prenom de l'adhérents ayant fait l'emprunts ainsi que le nom du jeu emprunté et afficher toutes ces informations.
variable : 	*e : liste des emprunts
			tJeux[] : tableau des jeux
			taille_logique : nombre d'élément dans le tableau tJeux
			taille_logique_A : nombre d'élément dans le tableau tAdherent
			tAdherent[] : tableau des adhérents 
*/
	int adherent,jeu;
	int i, trouve = 0;
	printf("\nAffichage de la liste des emprunts en cours :\n");
	printf("\nDate d'emprunt :\tId de l'emprunt\t\tNom et prénom de l'adhérent :\t\tNom du jeu :\n");
	while (!vide(e)){
		printf("%d/%d/%d\t\t\t%d\t\t",e->dateEmprunt.jour,e->dateEmprunt.mois,e->dateEmprunt.annee,e->idEmprunt);
		adherent = recherchDich_Adhe(tAdherent, taille_logique_A, &trouve, e->idAdherent);
		if (trouve == 0)
			printf("Inconnu\t\t\t");
		else
			printf("%s %s\t\t", tAdherent[adherent]->nom,tAdherent[adherent]->prenom);

		jeu = recherche_Jeux(tJeux, taille_logique, e->idJeu);
		if (jeu == -1)
			printf("Inconnu");
		else
			printf("\t%s\n",tJeux[jeu].nom);
		printf("\n");
		e=e->suiv;
	}
	printf("\n");
}


Emprunt* chargeListeEmprunts(void) {
/*
nom : chargeListeEmprunts
finalité : charger la liste des emprunts
description générale : la fonction essayer d'ouvrir le fichier des emprunts, le lire ligne par ligne et mettre tout ca en mémoire dans une liste.
variable : 	flot : pointeur vers le ficheir des emprunts
			*e : liste des Emprunts
			emprunt : identifiant de l'emprunt que la fonction est en train de charger
			adherent : identifiant de l'adhérent ayant fait l'emprunt
			jeu : identifiant du jeu emprunté
			date : date de l'emprunt
*/
	FILE *flot;
	flot=fopen("Emprunts.don","r");
	Emprunt *e;
	int emprunt,adherent,jeu;
	Date date;
	printf("\nChargement du fichier des emprunts en mémoire...\n");
	if (flot==NULL) {
		printf("Une erreur est survenue lors de l'ouverture du fichier des emprunts ! (fichier introuvable)\n");
		exit(-1);
	}
	e=listenouv();
	date=lireFichier(flot,&emprunt,&adherent,&jeu);
	e=inserer(e,emprunt,adherent,jeu,date);
	while(!feof(flot)) {
		date=lireFichier(flot,&emprunt,&adherent,&jeu);
		e=inserer(e,emprunt,adherent,jeu,date);		
	}
	printf("Chargement du fichier des emprunts en mémoire réussis !\n");
	fclose(flot);
	return e;
}

Date lireFichier(FILE *flot, int *emprunt, int *adherent, int *jeu) {
/*
nom : lireFichier
finalité : lire une ligne du fichier de sauvegarde des emprunts et la renvoie à la fonction appelante
description générale : la fonction prend en argument le pointeur vers le ficher de sauvegarde, l'adresse de la variable contenant l'identifiant de l'emprunt à charger, l'adresse de la variable contenant
						l'identifiant de l'emprunteur, l'adresse de la variable contenant l'identifiant du jeu emprunté.
						Elle lit une ligne dans le fichier de sauvegarde, renvoie l'identifiant de l'emprunt, celui de l'adhérent ainsi que celui du jeu par pointeur et charge la date d'emprunt dans une
						variable qu'elle va renvoyer.
variable : 	flot : pointeur vers le fichier de sauvegarde
			*emprunt : pointeur vers la variable de l'identifiant de l'emprunt en cours de chargement
			*adherent : pointeur vers la variable de l'identifiant de l'adherent
			*jeu : pointeur vers la variable de l'identifiant du jeu
			*d : date d'emprunt
*/
	Date d;
	fscanf(flot,"%d%d%d%d/%d/%d",emprunt,adherent,jeu,&d.jour,&d.mois,&d.annee);
	return d;
}

Emprunt* listenouv(void) {
/*
nom : listenouv
finalité : créeer une liste d'emprunt vide
description générale : la fonction créer une liste d'emprunts vide qu'elle va renvoyer à la fonction appelante.
variable : 	fe : liste des emprunts
*/
    Emprunt *e;
    e=NULL;
    return e;
}

Emprunt* insertionEnTete(Emprunt *s, int emprunt, int adherent, int jeu, Date date) {
/*
nom : insertionEnTete
finalité : insérer un nouveau maillon au début d'une liste
description générale : la fonction prend en argument le maillon dans la liste des emprunts devant suivre ce nouveau maillon, identifiant de l'emprunt, identifiant de l'adhérent ayant fait l'emprunt,
						l'identifiant du jeu emprunté, ainsi que le date d'emprunt
						Elle créer un nouveau maillon dont elle alloue la taille dynamiquement, y stock toute les valeurs nécéssaires, et la rajoute en premier place dans la liste. Enfin, elle return cette
						nouvelle liste.
variable : 	s : liste des emprunts avant l'ajout
			e : nouveau maillon à rajouter au début de la liste
			emprunt : identifiant de l'emprunt en cours de chargement
			adherent : identifiant de l'adherent
			jeu : identifiant du jeu
			date : date d'emprunt
*/
	Emprunt *e;
	e=(Emprunt *)malloc(sizeof(Emprunt));
	if (e==NULL) {
		printf("Une erreur est survenue lors de la création de la liste ! (malloc)\n");
		exit(-1);
	}
	e->idEmprunt=emprunt;
	e->idAdherent=adherent;
	e->idJeu=jeu;
	e->dateEmprunt=date;
	e->suiv=s;
	return e;
}

Emprunt* inserer(Emprunt *e, int emprunt, int adherent, int jeu, Date date) {
/*
nom : inserer
finalité : déterminer la position d'insertion du nouveau maillon dans la liste des emprunts
description générale : la fonction prend en argument la liste des emprunts, l'identifiant de l'emprunt à rajouter, l'identifiant de l'emprunteur, l'identifiant du jeu emprunté et la date d'emprunt
						Elle détermine la position d'insertion d'un emprunts et lance la bonne fonction pour l'inserer
			e : premier maillon de la liste des emprunts
			emprunt : identifiant de l'emprunt
			adherent : identifiant de l'adherent
			jeu : identifiant du jeu
			date : date d'emprunt
*/
	if (e == NULL)
		return insertionEnTete(e,emprunt,adherent,jeu,date);
	if (emprunt < e->idEmprunt)
		return insertionEnTete(e,emprunt,adherent,jeu,date);
	if (emprunt == e->idEmprunt)
		return e;
	e->suiv=inserer(e->suiv,emprunt,adherent,jeu,date);
	return e;
}


Booleen videR(Reservation *r) {
/*
nom : videR
finalité : vérifier si une liste est vide
description générale : la fonction prend en argument une liste
						Elle vérifie si une liste est vide. si oui, elle renvoie vrai, sinon elle renvoie faux
variable : 	r : premier maillon d'une liste de réservations
*/
    if(r==NULL)
    	return vrai;
	return faux;
}

void afficherListeResa(Reservation *r, Adherent* tAdherent[], int taille_logique_A, Jeux tJeux[], int taille_logique) {
/*
nom : afficherListeResa
finalité : afficher la liste des réservations pour un jeu
déscription générale : la fonction prend en argument la liste des réservations, le tableau des adhérents et celui des jeux, ainsi que leurs taille logique (donc le nombre de jeu et d'adhérent)
						Elle demande à l'utilisateur l'identifiant d'un jeu et va chercher toutes les réservations pour ce jeu. S'il y en a, elle va afficher le nom du jeu, ainsi que la date d'emprunt et le 
						nom et le prenom de l'emprunteur
variable : 	r : liste des réservations
			tAdherent : tableau des adhérents
			tJeux : tableau des jeux
			taille_logique : nombre de jeu dans le tableau
			taille_logique_A : nombre d'adhérents dans le tableau.
			id : identifiant du jeu dont on cherche la liste des réservations
			adherent : position de l'adhérent emprunteur dans le tableau des adhérents
			jeu : position du jeu emprunté dans le tableau des jeux

*/
	int id = 0, adherent = 0, jeu = 0, trouve = 0;
	printf("\nVeuillez entrer l'identifiant du jeu pour lequel vous souhaitez regarder la liste des réservations :\n");
	scanf("%d%*c",&id);
	printf("%d\n", id);
	jeu = recherche_Jeux(tJeux, taille_logique, id);
	if (jeu != -1) {
		printf("Nom du jeu : %s\n", tJeux[jeu].nom);
		printf("\nDate de réservation : \tId de la réservation :\t Nom et prénom de l'adhérent :\n");
		while (!videR(r)){
			if (r->idJeu==id) {
				printf("%d/%d/%d\t\t\t%d\t\t\t",r->dateR.jour,r->dateR.mois,r->dateR.annee,r->idRes);
				adherent = recherchDich_Adhe(tAdherent, taille_logique_A, &trouve, r->idAdherent);
				if (trouve == 0)
					printf("Inconnu\t\t\t");
				else
					printf("%s %s\t\t\n", tAdherent[adherent]->nom,tAdherent[adherent]->prenom);
			}
			r=r->suiv;
		}
		printf("\n");
	}
	else
		printf("Jeu inconnu\n");		
}

Reservation* chargeListeResa(void) {
/*
nom : chargeListeResa
finalité : charger en mémoire la liste des réservations
description générale : 	la fonction ouvre le fichier de sauvegarde des réservations, créer une liste vide et la remplie avec le contenu du fichier de sauvegarde
variable : 	flot : pointeur vers le fichier de sauvegarde
			e : liste des réservations
			resa : identifiant de la réservation en cours de chargement
			adherent : identifiant de l'adhérent ayant fait l'emprunt en cours de chargement
			jeu : identifiant du jeu
			date : date de réservation
*/
	FILE *flot;
	flot=fopen("Reservation.don","r");
	Reservation *e;
	int resa,adherent,jeu;
	Date date;
	printf("Chargement du fichier des réservations en mémoire...\n");
	if (flot==NULL) {
		printf("Une erreur est survenur lors de l'ouverture du fichier des réservations ! (fichier introuvable)\n");
		exit(-1);
	}
	e=listenouvR();
	date=lireFichierR(flot,&resa,&adherent,&jeu);
	e=insererR(e,resa,adherent,jeu,date);
	while(!feof(flot)){
		date=lireFichierR(flot,&resa,&adherent,&jeu);
		e=insererR(e,resa,adherent,jeu,date);		
	}
	printf("Chargement du fichier des réservations en mémoire réussis !\n");
	fclose(flot);
	return e;
}

Date lireFichierR(FILE *flot, int *resa, int *adherent, int *jeu) {
/*
nom : lireFichierR
finalité : lire une ligne du fichier de sauvegarde des réservations et la renvoie à la fonction appelante
description générale : la fonction prend en argument le pointeur vers le ficher de sauvegarde, l'adresse de la variable contenant l'identifiant de la réservatop, à charger, l'adresse de la variable contenant
						l'identifiant de l'adhérent, l'adresse de la variable contenant l'identifiant du jeu réservé.
						Elle lit une ligne dans le fichier de sauvegarde, renvoie l'identifiant de la réservation, celui de l'adhérent ainsi que celui du jeu par pointeur et charge la date de réservation dans
						une variable qu'elle va renvoyer.
variable : 	flot : pointeur vers le fichier de sauvegarde
			resa : identifiant de la réservation
			adherent : identifiant ayant fait la réservation
			jeu : identifiant du jeu réserver
			d : date de réservation
*/
	Date d;
	fscanf(flot,"%d%d%d%d/%d/%d",resa,adherent,jeu,&d.jour,&d.mois,&d.annee);
	return d;
}

Reservation* listenouvR(void) {
/*
nom : listenouvR
finalité : creer une nouvelle liste vide de réservations
description générale : la fonction pcréer une liste de réservation vide qu'elle return
variable : 	r : liste de réservation
*/
    Reservation *r;
    r=NULL;
    return r;
}

Reservation* insertionEnTeteR(Reservation *s, int resa, int adherent, int jeu, Date date) {
/*
nom : insertionEnTeteR
finalité : créer un maillon et l'inserer au début d'une liste de réservation
description générale : la fonction prend en argument le premier pointeur de la liste des reservations, l'identifiant de la réservation à charger, l'identifiant de l'adhérent, l'identifiant du jeu emprunté
						ainsi que la date de réservation
						Elle créer un nouveau maillon, le remplis avec les valeurs passées en arguments, le place avant le premier maillon de la liste des réservations et le return.
variable : 	s : ancien premier maillon de la liste
			resa : identifiant de la nouvelle réservation
			adherent : identifiant de l'adherent
			jeu : identifiant du jeu
			date : date de réservation
			r : nouveau maillon
*/
	Reservation *r;
	r=(Reservation *)malloc(sizeof(Reservation));
	if (r==NULL) {
		printf("Une erreur est survenue lors de la création de la liste ! (malloc)\n");
		exit(-1);
	}
	r->idRes=resa;
	r->idAdherent=adherent;
	r->idJeu=jeu;
	r->dateR=date;
	r->suiv=s;
	return r;
}

Reservation* insererR(Reservation *r, int resa, int adherent, int jeu, Date date) {
/*
nom : insererR
finalité : déterminer la place du nouveau maillon dans la liste des réservations
description générale : la fonction prend en argument le premier pointeur de la liste des reservations, l'identifiant de la réservation à charger, l'identifiant de l'adhérent, l'identifiant du jeu emprunté
						ainsi que la date de réservation
						Elle détermine la place du nouveau maillon dans la liste et charge la fonction pour l'ajouter. Enfin; elle return et résultat.
variable : 	r : premier maillon de la liste
			resa : identifiant de la nouvelle réservation
			adherent : identifiant de l'adherent
			jeu : identifiant du jeu
			date : date de réservation
*/
	if (r==NULL)
		return insertionEnTeteR(r,resa,adherent,jeu,date);
	if (resa<r->idRes)
		return insertionEnTeteR(r,resa,adherent,jeu,date);
	if (resa==r->idRes)
		return r;
	r->suiv=insererR(r->suiv,resa,adherent,jeu,date);
	return r;
}

