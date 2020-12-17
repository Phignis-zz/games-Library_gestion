# projet-S1

# Participants:
	FOUCRAS Baptiste,
	GAUGIRARD Florian,
	POLLET Matéo

# Configuration initiale de GIT:
	-> git config [--global] user.name ["pseudo"] : git config permet de spécifier de configurer les données quand vous partagez le fichier. Ici user.name spécifie le
	pseudo sous lequel vous apparaitrez pour les fichiers que vous déposerez sur le github.
	!spécifier ces données peuvent être importants, pas ici mais en monde professionnel.
	-> git config [--global] user.email ["email"] : pareil que la précédente, mais pour spécifier ici votre email.
	"--global" permet de spécifier pour tout les fichiers, il est optionnel, et sans global, il permet de spécifier ces données pour le github dans lequel on 
	fait (et écrase le potentiel global s'il existe)
	sans la spécification de l'e-mail ou du pseudo, cela permet de check la valeur actuelle.
	-> git config --list : pour check toute la configuration actuelle
	-> git clone <lien vers le github> . : git clone va créer dans le répertoire spécifié (ici ".", donc le répertoire courant), un directory .git/ pour spécifier que le
	répertoire est lié au github dont le lien est spécifié auparavant. A faire pour utiliser les commandes pull ou push, et une file .gitignore, qui correspond à tout
	les types de fichiers, qui seront ignoré lors des commits.

# Modifier un ficher de git | localement
	Une fois le clone effectué dans un repertory local de l'ordinateur, ce dernier possède un repertory caché .git/, spécifiant que ce repertory est lié à un github,
	rendant possible les commandes de push et de pull (vu plus tard). Dès lors, tout les fichiers déjà présents dans le github sera copié en local dans le directory.
	Vous pouvez dès lors modifier, créer, supprimer tout les fichiers, cela restera uniquement en local pour l'instant. Une fois les fichiers modifiés, quelques commandes
	sont utiles pour passer à la phase en ligne:
	-> git status [-s] : permet de connaître si des fichiers ne sont pas encore commité localement, donc les fichiers à l'état "Modifié".
	"-s" permet un affichage compacté, avec l'état des fichiers, et leur noms.
	-> git -add [nom fichier] : pour faire passer le fichier spécifié dans l'état "Stagé", c'est à dire qu'ils seront pris en compte au prochain commit.
	le nom fichier peut être remplacé par ".", donc il va add tout les fichiers modifiés du répertoire courant à l'état stagé.
	-> git commit -m "message" : permet de faire passer tout les fichiers de l'était "Stagé" à l'état "Commité". -m permet de spécifier un message, il est important
	(obligatoire) pour savoir les modifications, qui l'a commité, ou bien la date, savoir le combientième de commit est-ce de la personne...
	Des commits réguliers sont utiles, car on peut retourner sur d'anciens commits.
	-> git reset --soft : tout les fichiers à l'état "Commités" redeviennent à l'état "Stagé", utile si ont veut ajouter ou supprimer des fichiers du commit
	-> git checkout nom_fichier : le fichier spécifié verra ses modifications durant l'état "Modifié" supprimé, et le rétablit au texte lors de l'état "Stagé", ou du
	dernier commit si il n'a jamais été stagé.
	->  git diff --staged : permet de voir la différence entre les fichiers lors du précédents commits, et les fichiers actuellement stagés

# Modifier un ficher de git | en ligne
	Vous avez donc au préalable commit avec la commande tout votre fichier, et la commande git status -s ne renvoie rien. Si vous avez fini les modifications, il est
	temps de mettre votre file sur github! Attention, une mise en ligne régulière de vos fichiers permettra d'éviter trop d'erreurs suite au modification des autres
	participants.
	Des commandes et une procédure et à suivre pour mettre en ligne, afin d'éviter un trop plein d'erreurs sur de très gros projets.
	
	Démarche à suivre:
	1) commencer par s'assurer que le code en local ne possède aucun bugs, avec des fonctions de test
	2) fusionner les fichiers locaux avec ceux en ligne (si quelqu'un a entretant modifié les fichiers en ligne, la fusion risque d'être manuelle) -> pull
	3) retester en local les fichiers fusionnés, pour qu'il n'y ai aucun bugs
	4) mettre en ligne le fruit de vos efforts acharnés! -> push
	
	Voici les commandes en ligne permettant cette mise en ligne:
	-> git pull : il va aller chercher les fichiers en ligne, et les comparer à ceux locaux. Si jamais les deux sont différents, une fusion des fichiers (merge) sera
	faîte, soit automatiquement si aucun conflit n'est fait, soit manuellement, si des conflits comme de l'absence de code dans le fichier local par rapport à celui en
	ligne...
	-> git push : permet d'écraser tout les fichiers distants, et de les remplacer par vos fichiers locaux
	! attention à vous assurer qu'il ne reste aucuns bugs après merge des fichiers avant d'entamer la mise en ligne

# Les branches
	Les branches sont des versions des fichiers développées en parrallèles. Elles peuvent servir à garder une version stable des programmes pour le public ou en temps que
	backup, et continuer à développer en parallèle sur une autre branche. Elle peut servir à tester des choses, comme des fonctionnalités auquelles vous pensez qu'elle ne
	marcheront pas. Une fois le développement terminé sur une branche parallèle, vous pouvez fusionner celle-ci avec la principale. La branche principale est soit nommée 
	"main", soit "master".
	-> git checkout -[brR] nom_de_la_branche: sans option, cela permet d'aller sur la branche, "-b" permet de créer la branche,
	-d permet de supprimer la branche mergé avec une autre au préalable, -D pour forcer la deletion (même si nous mergé)
	-> git merge nom_branche : fusionne (merge) la branche de la commande avec la branche courante, dans laquelle vous êtes.

# Retournez en arrière sur des commits
	Des commits réguliers sont intéressants, car git offre l'opportunité de revenir en arrière dans les versions des fichiers locaux au moment des commits.
	-> git reset : même effet que git reset --soft mais replace les fichiers "Commités" au format "Modifié", plutôt que "Stagé"
	-> git reset --hard : supprime tout les fichiers existants, et les remets à la version du dernier commitage existant.

# Supprimer le répertoire
	Pour quelques raisons, vous pourriez vouloir supprimer votre répertoire local. Sur linux, (ou sur le bash de git), il vous faudra forcer la suppression du directory,
	avec la commande " rm -rf directory, r pour récursif (on supprime tout les fichiers du repertory et le repertory), et f pour forced, pour ne pas demander de
	confirmation. Si vous ne me croyez pas pour -f, essayez sans sur un gros projet ^^.
