#include "tableaux.h"

VALEUR tableau(char * nom_fichier){

	//Code ouverture ficher + nombre de ligne + caractères	
	
	FILE* texte = NULL;	
	texte = fopen(nom_fichier, "r");

	if(!texte){ fprintf(stderr, "ERROR : cannot open file \"%s\"", nom_fichier); exit(2); }
	
	FILE* data = NULL;
	data = fopen("data.txt", "r");

	if(!data){ fprintf(stderr, "ERROR : cannot open file \"data.txt\""); exit(3); }

	
	char* check = malloc(999*sizeof(char));
	
	int nbr_ligne=0, nbr_mot=0, nbr_caracter=0;
	
	if (data != NULL){
		fgets(check, 999, data);  										//lecture des caractères de la ligne
		int i=0;
		
		char* mot_data = strtok(check, " ");    
		
		while( mot_data != NULL){										//atoi = char(entier) --> int
			if(i == 0) nbr_ligne = atoi(mot_data);						//0 et 1 car seule les chaînes de caractères sont comptés
			//if(i == 1) nbr_mot = atoi(mot_data);  //changement du programme
			if(i == 1) nbr_caracter = atoi(mot_data);
			mot_data = strtok(NULL, " ");								//strtok avance d'une chaine de caractère à chaque boucle while grâce à sa valeur NULL
			i++;
		}
		//printf("Il y a %d lignes, %d mots et %d caractères dans notre fichier\n\n",nbr_ligne, nbr_mot, nbr_caracter);
	}
	
	
	//Code des tableaux
	
	char curseur=0;
	int i=0, j=1, verif_retour_ligne=0;     				//1er caractère du texte en T[i=0] alors que L[j=1} car on commence à la ligne 1
	
	VALEUR new_VALEUR = NULL;
	new_VALEUR = malloc(sizeof(struct valeur));
	if(!new_VALEUR){fprintf(stderr, "ERROR, cannot malloc new_VALEUR"); exit(4);}

	char * T = NULL;
	T = malloc(nbr_caracter * sizeof(char));
	if(!T){fprintf(stderr, "ERROR, cannot malloc T"); exit(5);}
	
	int * L = NULL;
	L = malloc(nbr_ligne * sizeof(int));
	if(!L){fprintf(stderr, "ERROR, cannot malloc L"); exit(6);}


	while( curseur != EOF){
		curseur = fgetc(texte);
		T[i] = curseur;
		
		if((verif_retour_ligne == 1) || (i == 0)){          			//on initialise L[j] \n ou 1ere caractère
			L[j] = i;
			//printf("%d & %c=T[i]  %d=j\n", L[j], T[i], j);				//Test de L[j]
			j++;
		}
		
		verif_retour_ligne = 0;
			
		if(curseur == '\n') verif_retour_ligne = 1;		
		//if( (nbr_caracter - i) <= 100 )	printf("%c", T[i]);				//Test de T[i] sur les 100 derniers caractères
		
		i++;
	}
	//printf("\n\n");	
	
	new_VALEUR->taille_L = nbr_ligne;
	new_VALEUR->taille_T = nbr_caracter;
	new_VALEUR->nbr_mot = nbr_mot;
	new_VALEUR->L = L;
	new_VALEUR->T = T;
	
	free(check);
	return new_VALEUR;
}
