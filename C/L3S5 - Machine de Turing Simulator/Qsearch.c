#include "q5-search.h"

int main(int argc, char* argv[]) {

    printf("\nChoisissez le caractère 'a' que vous souhaitez chercher ainsi que son numéro de bande 'i'.");
    printf("\nPar ailleurs,  a= 0 ou 1, avec i compris entre [1,10].\n");
	int Ka=0,Ki=0;

    printf("\nChoisissez a: ");
	scanf("%d", &Ka);
    printf("Choisissez i: ");
    scanf("%d", &Ki);

    printf("Le caractère chercher est: %d\n",Ka);	
    printf("Sur la bande: %s\n", argv[Ki]);
	
	MT mt;

	MT_SEARCH(argc,&argv[1],mt, Ka, Ki);
	printf("Appuyez sur entrée pour terminer\n");
	getchar();
	return 0;
}