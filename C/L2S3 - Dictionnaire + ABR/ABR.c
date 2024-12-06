#include "ABR.h"


ABR init_ABR(SOMMET sommet){
    ABR new_ABR = NULL;
    new_ABR = malloc(sizeof(struct abr));

    if(!new_ABR){ fprintf(stderr, "Error cannot malloc new_ABR"); return NULL; }

    new_ABR->sommet = sommet;
    new_ABR->fils_gauche = NULL;
    new_ABR->fils_droit = NULL;

	return new_ABR;
}

SOMMET init_SOMMET(char * mot, int nbr_occurence, LISTE position_mot){
    SOMMET new_SOMMET = NULL;
    new_SOMMET = malloc(sizeof(struct sommet));

    if(!new_SOMMET){ fprintf(stderr, "Error cannot malloc new_SOMMET"); return NULL; }

    new_SOMMET->mot = mot;
    new_SOMMET->nbr_occurence = nbr_occurence;
    new_SOMMET->position_mot = position_mot;

	return new_SOMMET;
}


LISTE init_LISTE(int nbr_occurence){
    LISTE new_LISTE = NULL;
    new_LISTE = malloc(sizeof(struct liste));

    if(!new_LISTE){ fprintf(stderr, "Error cannot malloc new_LISTE"); return NULL; }

    new_LISTE->nbr_occurence = nbr_occurence;
    new_LISTE->suiv = NULL;

	return new_LISTE;
}



char * mot_a_zero(char * mot, int taille_mot){
	for(int i=0; i<taille_mot; i++){
		mot[i] = 0;
	}
	return mot;
}

int pre_lecture(char * T, int taille_T){
	int cmpt_mot = 0;
	int est_passe = 0;

	for(int i=0; i<taille_T; i++){
		if(((T[i] >= 65)&&(T[i] <= 90)) || ((T[i] >= 97)&&(T[i] <= 122))){
			est_passe = 1;
		}
		else{
			if(est_passe == 1){
				cmpt_mot++;
				est_passe = 0;
			}
		}
	}

	return cmpt_mot;
}

char ** creation_tab_mot(int nbr_mot, int nbr_caracter, char* T, int * tab_position, int * nbr_occurence_totale){
	char* mot = malloc(plus_long_mot*sizeof(char));
	
	char ** tab_mot = malloc((nbr_mot)*sizeof(char *));

	for(int a=0; a<nbr_mot; a++){
		tab_mot[a] = malloc(plus_long_mot*sizeof(char));
	}

	char temp[nbr_mot][plus_long_mot];

	int cmpt=0;
	int indice_tab = 0;
	int est_passe = 0;
	

	for(int i=0; i<nbr_caracter; i++){
		if(((T[i] >= 65)&&(T[i] <= 90)) || ((T[i] >= 97)&&(T[i] <= 122))){
			est_passe = 1;
			if( (T[i] >= 65) && (T[i] <= 90) ){
				mot[cmpt] = T[i]+32;
				cmpt++;
			}else{
				mot[cmpt] = T[i];
				cmpt++;
			}
		}
		else{
			if(est_passe == 1){
				strncpy(tab_mot[indice_tab], mot, plus_long_mot);
				strncpy(temp[indice_tab], mot, plus_long_mot);
				tab_position[indice_tab] = (i-cmpt)-3;
				indice_tab++;
				mot = mot_a_zero(mot, plus_long_mot);
				est_passe = 0;
			}
			cmpt = 0;
		}
	}

	*nbr_occurence_totale = 0;
	char test = '0';

	for(int i=0; i< (nbr_mot-1); i++){

		for(int j=i+1; j<nbr_mot; j++){;

			if(strcmp(tab_mot[i], temp[j]) == 0){	//string compare 
				//printf("\n\n mot i=%s(%d)  mot i=%s (%d)\n\n", tab_mot[i], tab_position[i], temp[j], tab_position[j]);
				sprintf(temp[j],"%c",test);
				*nbr_occurence_totale = *nbr_occurence_totale +1 ;

				//printf("%d",*nbr_occurence_totale);
			}
		}
	}
	//printf("\na %s  %s\n",tab_mot[nbr_mot-1], temp[nbr_mot-1]);
	printf("\n\na %d\n\n",*nbr_occurence_totale);

	free(mot);
	return tab_mot;
	free(tab_mot);
}

SOMMET * ajouter_tab(SOMMET * tab_sommet, char ** tableau_mot, int * tab_position, int nbr_mot){

	int tab_taille = 0, est_dedans = 0;

	printf("tab_position[0] est de %d\n", tab_position[0]);
	//printf("tab_position[0] est de %d\n", tab_position[1]);

	for(int i=0; i< (nbr_mot); i++){
		est_dedans = 0;
		
		for(int j=0; j<tab_taille; j++){
			if(strcmp(tableau_mot[i], tab_sommet[j]->mot) == 0){	//string compare 
				est_dedans = 1;
				tab_sommet[j]->nbr_occurence++;
				tab_sommet[j]->position_mot = liste_ajouter(tab_sommet[j]->position_mot, tab_position[i]);
			}
		}

		if(est_dedans == 0){
			tab_sommet[tab_taille] = malloc(sizeof(struct sommet));
			tab_sommet[tab_taille]->mot = tableau_mot[i];
			tab_sommet[tab_taille]->nbr_occurence = 1;
			tab_sommet[tab_taille]->position_mot = liste_ajouter(tab_sommet[tab_taille]->position_mot, tab_position[i]);
			tab_taille++;
		}
	}
	return tab_sommet;
}

LISTE liste_ajouter(LISTE liste, int nbr_occurence){
	if(liste == NULL){
		LISTE tmp = NULL;
		tmp = malloc(sizeof(struct liste));
		tmp->nbr_occurence = nbr_occurence;
		tmp->suiv = NULL;
		return tmp;
	}
	liste->suiv = liste_ajouter(liste->suiv, nbr_occurence);
	return liste;
}

void liste_afficher(LISTE liste){
	
	LISTE tmp = liste;
	while(tmp != NULL){
		printf("%d ", tmp->nbr_occurence);
		tmp = tmp->suiv;
	}
	printf("\n");
}

void free_liste(LISTE liste){
	if(liste == NULL){
		return;
	}
	LISTE tmp = liste->suiv;
	free(liste);
	free_liste(tmp);
}


//Programme de tri faux et non finis

//Donc pas de possibilitée d'ABR


/*
char* Tableau_triee_pour_ABR(SOMMET * tab_sommet, int nbr_total_mot_triee, int *i_compteur, int compteur[]){

	int est_dedans = 0;
	char stock_plus_petit;
	char* tableau_triee = malloc(plus_long_mot*sizeof(char));

	
	for(int i=0; i<nbr_total_mot_triee; i++){
		est_dedans = 0;	

		
		if(i==0){
			stock_plus_petit = tab_sommet[i]->mot[i];
		}		
		
		for(int j=i+1;j<plus_long_mot;j++){
			
			if((stock_plus_petit < tab_sommet[i]->mot[i]) && (est_dedans == 0)){		//stock_plus_petit est plus petit que tab_somme, on s'arrête pour ce mot
				est_dedans = 1;
				*i_compteur = i;
				break;
			}

			if((stock_plus_petit == tab_sommet[i]->mot[i]) && (est_dedans == 0)){	//stock_plus_petit est égal à tab_sommet, on continue pour ce mot
				int a = i+1;
				stock_plus_petit = plus_petit_ou_plus_grand(tab_sommet, stock_plus_petit, i, &a, compteur);
				*i_compteur = a;
			}

			if((stock_plus_petit > tab_sommet[i]->mot[i]) && (est_dedans == 0)){		//stock_plus_petit est plus grand que tab_somme, stock prend la valeur nouveau mot
				stock_plus_petit = tab_sommet[i]->mot[i];
				est_dedans = 1;
				*i_compteur = i;
				break;
			}			
		}
		tableau_triee[i] = stock_plus_petit;
	}
	return tableau_triee;
	free(tableau_triee);
}


char plus_petit_ou_plus_grand(SOMMET * tab_sommet, char stock_plus_petit,int i, int *i_compteur, int compteur[]){

	for(i+=1;i<plus_long_mot;i++){
		
		if(stock_plus_petit < tab_sommet[i]->mot[i]){		//stock plus petit que tab_somme, on s'arrête pour ce mot
			return stock_plus_petit;
			*i_compteur = i;
			return stock_plus_petit;
		}

		if(stock_plus_petit == tab_sommet[i]->mot[i]){	//stock plus petit que tab_somme on continue pour ce mot
			int a = i+1;
			plus_petit_ou_plus_grand(tab_sommet, stock_plus_petit, i, &a, compteur);
			*i_compteur = a;
		}

		if(stock_plus_petit > tab_sommet[i]->mot[i]){		//stock plus petit que tab_somme, stock prend la valeur nouveau mot
			stock_plus_petit = tab_sommet[i]->mot[i];
			*i_compteur = i;
			return stock_plus_petit;
		}
	}
	return stock_plus_petit;
}
*/