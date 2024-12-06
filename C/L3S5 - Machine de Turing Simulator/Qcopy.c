#include "q5-copy.h"

int main(int argc, char* argv[]) {

    printf("\nChoisissez la Bande que vous voulez copier 'i' vers celle que vous voulez coller 'j', il y a 10 bandes.");
    printf("\nPar ailleurs,  i =/= j,  i <= j, avec i et j C[1,10]\n");
	int Ki=0,Kj=0;

    printf("\nChoisissez i: ");
	scanf("%d", &Ki);
    printf("Choisissez j: ");
    scanf("%d", &Kj);

    printf("Input i: %s\n", argv[Ki+1]);	
    printf("Input j: %s\n", argv[Kj+1]);

    if(strlen(argv[Ki+1]) > strlen(argv[Kj+1])){
        printf("\nRholala l'input de i est plus long que celui de j, qu'est ce que j'avais dit !!\n");
        exit(1);
    }
	
	MT mt;

	MT_COPY(argc,&argv[1],mt, Ki, Kj);
	printf("Appuyez sur entrée pour terminer\n");
	getchar();
	return 0;
}