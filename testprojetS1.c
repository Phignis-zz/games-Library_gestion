#include "projetS1.h"

void testTchargeAdherent(void)
{
	FILE *test_fichier;
	char str[11];
	test_fichier = fopen("../test.txt", "r");
	if(test_fichier == NULL)
	{
		printf("Erreur lors de l'ouverture du fichier test.txt");
		return;
	}
	fgets_like(str , 11, test_fichier, 'r');
	fclose(test_fichier);
	printf("%s\n", str);
}

int main(void)
{
	testTchargeAdherent();
	return 0;
}
