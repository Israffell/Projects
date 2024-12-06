#include "mt-abcd.h"

void affichage_mt_abcd(MT mt){
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



//
//Exo 10
//



int verif_argc_and_carac_number(int argc, char* argv[]){

    //Vérification des arguments
    if (argc != 3){
		if(argc < 3) printf("Il manque un/des argument(s).");
		if(argc > 3) printf("Il y a un/des argument(s) en trop.");
		exit(1);
	}

	FILE* file = NULL;
    file = fopen(argv[0], "r");

    //Vérification du bon fonctionnement du fichier cible
	if (!file){
        printf("Erreur, ouverture du fichier %s impossible !\n\n",argv[0]);
        exit(1);
    }	

	//Ouverture/lecture/fermeture fichier.txt et copiage des caractères présents
    int carac_nbr= 0;
	while(fgetc(file) != EOF){ carac_nbr++;	}
	fclose(file);    
    return(carac_nbr);    
}


int lecture_mt_abcd(int argc, char* argv[], MT mt){
		
	int j = 0;
    int carac_nbr = verif_argc_and_carac_number(argc, argv);
    char AllChar[carac_nbr];

	FILE* file = NULL;
	file = fopen(argv[0],"r");    
    while(j < carac_nbr){
        AllChar[j] = fgetc(file);
        j++;
    }
    fclose(file);

	//Initialition du mot d'entrée pour la machine
	mt.input = argv[1];
	strcat(mt.input,"__"); 					//ajout de deux _ à la fin du mot d'entrée
	int input_size = strlen(mt.input);		//taille du mot entré

	//on décale chaque caractère à droite (sauf la dernière case)
	for(int j=input_size-1; j>0;j--){ mt.input[j] = mt.input[j-1]; }
	
	//on met un _ au début du mot pour avoir à la fin un '_' avant et après le mot d'entrée
	mt.input[0] = '_';	


	//Vérification des caractères du input
	for(int j=1; j<input_size-1; j++){
		if(     (mt.input[j] != 'a') && (mt.input[j] != 'b') && (mt.input[j] != 'c') && (mt.input[j] != 'd')    ){
			printf("Erreur, le mot contient des caractères inconnus\n");
			exit(1);
		}
	}

	//Sauvegarde des transitions dans le .TXT
	mt.nbr_transition = 0;

	for(int j=0; j<carac_nbr; j++){

		if((AllChar[j] == 'i') && (AllChar[j+4] == ':' )){
			mt.init = AllChar[j+6];
		}
		if((AllChar[j] == 'a') && (AllChar[j+6] == ':' )){        
			mt.accept = AllChar[j+8];
		}
		if((AllChar[j] == ',') && (AllChar[j+2] == ',')){
			mt.nbr_transition ++;
		}
	}


	//Allocation des tableaux à la bonne taille
	mt.read_state = (char*)malloc(mt.nbr_transition*sizeof(char));
	mt.read_letter= (char*)malloc(mt.nbr_transition*sizeof(char));
	mt.write_state = (char*)malloc(mt.nbr_transition*sizeof(char));
	mt.write_letter = (char*)malloc(mt.nbr_transition*sizeof(char));
	mt.shift = (char*)malloc(mt.nbr_transition*sizeof(char));
	int count = 0;
	
	for(int j=0; j<carac_nbr; j++){
		if(     (AllChar[j] == ',') && (AllChar[j+2] == ',')   ){
			mt.read_state[count] = AllChar[j-6];
			mt.read_letter[count] = AllChar[j-4];
			mt.write_state[count] = AllChar[j-1];
			mt.write_letter[count] = AllChar[j+1];
			mt.shift[count] = AllChar[j+3];
			count++;
		}
	}










///////////////////////////////////////  C'est à refaire pour la matrice M-01 crée à partir de M-abcd ////////////////////////////////////////////////////////////
/*
    int i = 0;

	printf("Il y a %d transitions\n",mt.nbr_transition);
	for (int i = 0; i < count; i++){
		printf("%c,%c\n%c,%c,%c\n\n",mt.read_state[i],mt.read_letter[i],mt.write_state[i],mt.write_letter[i],mt.shift[i]);
	}


	//Partie travail de la MT
	mt.head = 1;
	mt.steps = 0;
	mt.current_state = mt.init;
	int err, lim = 0;

	while((mt.current_state != mt.accept) && (mt.head < strlen(mt.input))){

		for (i=0;i<mt.nbr_transition;i++){			
			err = 0;

			if((mt.current_state == mt.read_state[i]) && (mt.input[mt.head] == mt.read_letter[i])){
				affichage_mt_abcd(mt);
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

		if(lim > 500){
			affichage_mt_abcd(mt);
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
	affichage_mt_abcd(mt);
	printf("Input accepted\n");
	printf("Output: ");
	for(i=0;i<strlen(mt.input);i++){
		//On imprime des espaces au lieu des '_' s'il y en a
		if(mt.input[i] == '_'){ printf(" "); }		
		else{ printf("%c",mt.input[i]); }
	}


	printf("\n");
	printf("Steps: %d\n\n\n\n",mt.steps);
*////
	free(mt.read_state);
	free(mt.read_letter);
	free(mt.write_state);
	free(mt.write_letter);
	free(mt.shift);
	return 0;
}