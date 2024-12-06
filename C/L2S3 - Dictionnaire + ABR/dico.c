#include "dico.h"


int main(int argc, char *argv[]){
	
	if(argc < 2){
		fprintf(stderr, "ERROR veuillez donner un nom de fichier");
	}

	VALEUR valeur = tableau(argv[1]);
	valeur->nbr_mot = pre_lecture(valeur->T, valeur->taille_T);

	int * tab_position =  malloc(valeur->nbr_mot*sizeof(int));
	int nbr_occurence_totale = 0, nbr_total_mot_triee = 0;

	
	char ** tableau_mot = creation_tab_mot(valeur->nbr_mot, valeur->taille_T, valeur->T, tab_position, &nbr_occurence_totale);
	nbr_total_mot_triee = ((valeur->nbr_mot)-((int)nbr_occurence_totale));

	SOMMET * tab_sommet = NULL;
	
	tab_sommet = malloc(nbr_total_mot_triee*sizeof(SOMMET));
	tab_sommet = ajouter_tab(tab_sommet, tableau_mot, tab_position, valeur->nbr_mot);
	
	
	
	for(int i=0; i<nbr_total_mot_triee; i++){							// Affichage des toutes les stuctures de mot du texte possible.
																		// Ces structs SOMMET sont équivalent à des noeuds de l'ABR A.
		printf("------SOMMET n°%d------\n", i);
		printf("Mot : %s\n", tab_sommet[i]->mot);
		printf("Nombre x d'occurences trouvées : %d\n", tab_sommet[i]->nbr_occurence);
		printf("Position des x occurences dans le texte:\n");
		liste_afficher(tab_sommet[i]->position_mot);
		printf("-----------------------\n\n");
	}
	

	//Appel du programme de tri de struct pour la construction de l'ABR
	/*

	int Tableau_final[nbr_total_mot_triee], compteur[nbr_total_mot_triee], i_compteur=0;

	for(int i=0; i<nbr_total_mot_triee; i++){
		
		Tableau_final[i] = Tableau_triee_pour_ABR(*tab_sommet, nbr_total_mot_triee, &i_compteur, compteur);
		compteur[i] = i_compteur;
	}

	*/

	printf("Il y a %d lignes, %d mots et %d caractères dans notre fichier\n", valeur->taille_L, valeur->nbr_mot, valeur->taille_T);

	printf("\nAinsi que %d d'occurences de mot ainsi que %d de nombre de mot 'SOMMET'. \n\n",nbr_occurence_totale ,nbr_total_mot_triee);

	printf("\nVeuillez configurer le Terminal pour fonctionner dans le fichier ../dico \n\n");
	printf("Si vous voullez changer le .txt à traiter, tapez ceci dans le terminal:\n");
	printf("wc -c -l 'nom_du_nouveau_texte.txt' > data.txt \n\n");

	//-w inutile car un mot = 1 chaine de caratère pouvant comprendre des caractères spéciaux
	
	

	return 0;
}
