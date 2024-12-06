#include "mt-01.h"

void affichage_mt_01(MT mt){
	printf("--------------------------------------\n");
	printf("Steps: %d   State: %c\n",mt.steps,mt.current_state);
	int input_size = strlen(mt.input);
	char head_tab[input_size];
	int i;

	for(i=0;i<input_size;i++){ head_tab[i] = ' '; } 	//on initialise le tableau avec des espaces
	head_tab[mt.head] = '^'; 							//le symbole ^ permet d'afficher la position de la tête de lecture
	printf("%s\n",mt.input);

	for (i=0;i<input_size;i++){ printf("%c",head_tab[i]); }
	printf("\n\n");
}





//(détecte mais ne supprime pas les transitions utilisées)
void unused_transitions(MT mt){
	int count = strlen(mt.shift); // nombre de transitions
/*	printf("Il y a %d transitions\n",count);
	for (int i = 0; i < count; i++){
		printf("%c,%c\n%c,%c,%c\n\n",mt.read_state[i],mt.read_letter[i],mt.write_state[i],mt.write_letter[i],mt.shift[i]);
	}*/

	int unused[count];

	for (int i = 0; i < count; i++){
		int err2 = 1;
		for (int j = 0; j< count; j++ ){
			if(i==j){ j++; }
			//printf("write_state [%d] = %c\n",j,mt.write_state[j]);
			if((mt.read_state[i] == mt.write_state[j]) || (mt.read_state[i] == mt.init)){ err2 = 0;}
		}
		if(err2 == 1){
			unused[i] = 1;
		}
	}

	for(int i = 0; i<count; i++){
		if(unused[i] == 1) {
			printf("La transition suivante:\n");
			printf("%c,%c\n%c,%c,%c",mt.read_state[i],mt.read_letter[i],mt.write_state[i],mt.write_letter[i],mt.shift[i]);
			printf(" est inutilisée\n\n");
		}
	}
}





//Ouverture fichier + vérification de la viabilité des Argv
int lecture_mt_01(int argc, char* argv[], MT mt){
		
	if (argc != 3){
		if(argc < 3) printf("Il manque un/des argument(s).");
		if(argc > 3) printf("Il y a un/des argument(s) en trop.");
		exit(1);
	}

	FILE* file = NULL;
    file = fopen(argv[0], "r");    

	if (!file){
        printf("Erreur, ouverture du fichier %s impossible !\n\n",argv[0]);
        exit(1);
    }		
	int i = 0, carac_nbr= 0;
	

	//Ouverture/lecture/fermeture fichier.txt et copiage des caractères présents
	while(fgetc(file) != EOF){ carac_nbr++;	}
		fclose(file);


	char AllChar[carac_nbr];
	file = fopen(argv[0],"r");
    int j = 0;

    while (j < carac_nbr){
        AllChar[j] = fgetc(file);
        j++;
    }
    fclose(file);

	//Initialition du mot d'entrée pour la machine
	mt.input = argv[1];
	strcat(mt.input,"__"); 					//on ajoute deux _ à la fin du mot d'entrée
	int input_size = strlen(mt.input);		// taille du mot d'entrée

	//on décale chaque caractère à droite (sauf la dernière case)
	for(int j=input_size-1; j>0;j--){ mt.input[j] = mt.input[j-1]; }
	
	// on met un '_' au début du mot pour avoir à la fin un '_' avant et après le mot d'entrée
	mt.input[0] = '_';	


	//Vérification des caractères du input

	for(int j=1; j<input_size-1; j++){
		if(		(mt.input[j] != '0') && (mt.input[j] != '1')	){
			printf("Erreur, le mot contient des caractères inconnus\n");
			exit(1);
		}
	}

	//Sauvegarde des transitions dans le .TXT
	int count = 0;
	mt.nbr_transition = 0;

	for(int j=0; j<carac_nbr; j++){

		if((AllChar[j] == 'i') && (AllChar[j+4] == ':' )){
			mt.init = AllChar[j+6];
			count ++;
		}
		if((AllChar[j] == 'a') && (AllChar[j+6] == ':' )){
			mt.accept = AllChar[j+8];
			count ++;
		}
		if((AllChar[j] == ',') && (AllChar[j-4] == ',') && (AllChar[j+2] == ',')){
			mt.nbr_transition ++;
		}
	}


	//Allocation des tableaux à la bonne taille
	mt.read_state = (char*)malloc(mt.nbr_transition*sizeof(char));
	mt.read_letter= (char*)malloc(mt.nbr_transition*sizeof(char));
	mt.write_state = (char*)malloc(mt.nbr_transition*sizeof(char));
	mt.write_letter = (char*)malloc(mt.nbr_transition*sizeof(char));
	mt.shift = (char*)malloc(mt.nbr_transition*sizeof(char));
	count = 0;
	
	for(int j=0; j<carac_nbr; j++){
		if((AllChar[j] == ',') && (AllChar[j-4] == ',') && (AllChar[j+2] == ',')){
			mt.read_state[count] = AllChar[j-5];
			mt.read_letter[count] = AllChar[j-3];
			mt.write_state[count] = AllChar[j-1];
			mt.write_letter[count] = AllChar[j+1];
			mt.shift[count] = AllChar[j+3];
			count++;
		}
	}

	unused_transitions(mt);

	//Partie travail de la MT
	mt.head = 1;
	mt.steps = 0;
	mt.current_state = mt.init;
	int err, lim = 0;

	while((mt.current_state != mt.accept) && (mt.head < strlen(mt.input))){

		for (i=0;i<mt.nbr_transition;i++){			
			err = 0;

			if((mt.current_state == mt.read_state[i]) && (mt.input[mt.head] == mt.read_letter[i])){
				affichage_mt_01(mt);
				mt.current_state = mt.write_state[i];
				mt.input[mt.head] = mt.write_letter[i];
				mt.steps++;
				if(mt.shift[i] == '<'){
					mt.head--;
				}
				else if(mt.shift[i] == '>'){ mt.head++; }
				i = 0;
				if (mt.input[strlen(mt.input)-1] != '_'){
					mt.input = strcat(mt.input,"_");
				}
			}
			else{err++;}
			
			if (err == mt.nbr_transition){
				printf("Erreur, il n'existe pas de transition sur %c en l'état %c",mt.input[mt.head],mt.read_state[0]);
				exit(1);
			}
		}
		lim++;

		if(lim > 10){
			affichage_mt_01(mt);
			printf("Input rejected\n");
			printf("Output: ");
			
			for(i=0;i<strlen(mt.input);i++){
				//On imprime des espaces au lieu des '_' s'il y en a
				if(mt.input[i] == '_'){printf(" ");}		
				else{printf("%c",mt.input[i]);}
			}

			printf("\n");
			printf("Steps: %d\n\n\n\n",mt.steps);	//la mémoire n'est pas libérée sinon
			free(mt.read_state);
			free(mt.read_letter);
			free(mt.write_state);
			free(mt.write_letter);
			free(mt.shift);
			return 0;
		}
	}
	affichage_mt_01(mt);
	printf("Input accepted\n");
	printf("Output: ");
	for(i=0;i<strlen(mt.input);i++){
		//On imprime des espaces au lieu des '_' s'il y en a
		if(mt.input[i] == '_'){ printf(" "); }		
		else{ printf("%c",mt.input[i]); }
	}


	printf("\n");
	printf("Steps: %d\n\n\n\n",mt.steps);

	free(mt.read_state);
	free(mt.read_letter);
	free(mt.write_state);
	free(mt.write_letter);
	free(mt.shift);
	return 0;
}