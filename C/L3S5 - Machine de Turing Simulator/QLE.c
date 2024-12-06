#include "q5-copy.h"

int main(int argc, char* argv[]) {

    printf("\nChoisissez le numéro de bande avec lequel intéragir 'j'.");
    printf("\nPar ailleurs j est compris [1,10].\n");
	int Ki=0,Kj=0;


    printf("Choisissez j: ");
    scanf("%d", &Kj);
    printf("La bande rechercher est: %d\n",Kj);	
	
	MT mt;

	MT_COPY(argc,&argv[1],mt, Ki, Kj);
	printf("Appuyez sur entrée pour terminer\n");
	getchar();
	return 0;
}