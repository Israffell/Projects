#include "q5-copy.h"

void affichage_mt_01(MT mt){
	//printf("\n--------------------------------------");
	printf("\nSteps: %d   State: %c ",mt.steps,mt.current_state);
	int input_size = strlen(mt.input);
	char head_tab[input_size+1];
	int i;

	for(i=0;i<input_size;i++){ head_tab[i] = ' '; } 	//on initialise le tableau avec des espaces
	if(mt.steps<10){head_tab[mt.head] = '^';}
	else{head_tab[mt.head+1] = '^';}					//le symbole ^ permet d'afficher la position de la tête de lecture
	printf("%s\n",mt.input);
	printf("                    ");
	for (i=0;i<input_size;i++){printf("%c",head_tab[i]);}
	//printf("\n\n");
}




//Ouverture fichier + vérification de la viabilité des Argv
int MT_COPY(int argc, char* argv[], MT mt, int Ki, int Kj){
	
    if(argc < 4){printf("Il manque un/des argument(s).");exit(1);}          //Il y a 1 fichier txt et 2 bandes minimum 
    if(argc > 12){ printf("Il y a un/des argument(s) en trop.");exit(1);}    //Pouvant aller jusqu'à 10 (k=10)
      
    //printf("\nargc: %d\n",argc);                                                      Test nombre argc
    	
    FILE* file = NULL;
    file = fopen(argv[0], "r");    

	if (!file){
        printf("Erreur, ouverture du fichier %s impossible !\n\n",argv[0]);
        exit(1);
    }		
	int i = 0, nbr_carac= 0;
	
	//printf("\n les argv sont 1: %s,2: %s,3: %s\n",argv[0],argv[1],argv[2]);               //  test viabilité argv

	//Ouverture/lecture/fermeture fichier.txt et copiage des caractères présents
	while(fgetc(file) != EOF){ nbr_carac++;	}
	fclose(file);

	char AllChar[nbr_carac];
	file = fopen(argv[0],"r");
    //printf("\nLe nom du fichier est: %s\n",argv[0]);
    int j = 0;

    while (j < nbr_carac){
        AllChar[j] = fgetc(file);
        j++;
    }
    fclose(file);

    //Initialition du mot d'entrée pour la machine
	mt.input = argv[Kj];
	strcat(mt.input,"_"); 					//on ajoute deux _ à la fin du mot d'entrée
	int input_size = strlen(mt.input);		// taille du mot d'entrée			


	//on décale chaque caractère à droite (sauf la dernière case)
	for(int j=input_size-1; j>0;j--){ mt.input[j] = mt.input[j-1]; }
	

	// on met un '_' au début du mot pour avoir à la fin un '_' avant et après le mot d'entrée
	mt.input[0] = '__';	


	//Vérification des caractères de l'input
	for(int j=1; j<input_size-1; j++){
		if(		(mt.input[j] != '0') && (mt.input[j] != '1')	){
			printf("Erreur, le mot contient des caractères inconnus\n");
            printf("%s\n",mt.input);
			exit(1);
		}
	}


	//Sauvegarde des transitions dans le .TXT
	int count = 0;
	mt.nbr_transition = 0;
        //printf("nbr_carac = %d",nbr_carac);

	for(int j=0; j<nbr_carac; j++){
        //printf("\n le char est %c\n",AllChar[j]);                        // Test des caractères

		if((AllChar[j] == 'i') && (AllChar[j+4] == ':' )){
			mt.init = AllChar[j+6];
			count ++;
		}
		if((AllChar[j] == 'a') && (AllChar[j+6] == ':' )){
			mt.accept = AllChar[j+8];
			count ++;
		}
		if((AllChar[j] == ',') && (AllChar[j+2] == ',')){
			mt.nbr_transition ++;
		}
        //printf("\n Nbr de transitions %d et count %d\n",mt.nbr_transition, count);
	}


	//Allocation des tableaux à la bonne taille
	mt.read_state = (char*)malloc(mt.nbr_transition*sizeof(char));
	mt.read_letter= (char*)malloc(mt.nbr_transition*sizeof(char));
	mt.write_state = (char*)malloc(mt.nbr_transition*sizeof(char));
	mt.write_letter = (char*)malloc(mt.nbr_transition*sizeof(char));
	mt.shift = (char*)malloc(mt.nbr_transition*sizeof(char));
	count = 0;
	
	for(int j=0; j<nbr_carac; j++){
		if((AllChar[j] == ',') && (AllChar[j+2] == ',')){
			mt.read_state[count] = AllChar[j-6];    //printf("\n\n test read_state: %c",AllChar[j-6]);
			mt.read_letter[count] = AllChar[j-4];   //printf("\n\n test read_letter: %c",AllChar[j-4]);
			mt.write_state[count] = AllChar[j-1];   //printf("\n\n test write_state: %c",AllChar[j-1]);
			mt.write_letter[count] = AllChar[j+1];  //printf("\n\n test write_letter: %c",AllChar[j+1]);
			mt.shift[count] = AllChar[j+3];         //printf("\n\n test shift: %c",AllChar[j+3]);
			count++;                                //printf("\n\n fin transitionnnnnnnn");
		}
	}


	//Partie travail de la MT
	mt.head = 1;
	mt.steps = 0;
	mt.current_state = mt.init;
    //printf("carracter actuel = %c",mt.current_state);
	int err, lim = 0;
    int size_Ki = strlen(argv[Ki]);
    int size_Kj = strlen(argv[Kj]);

	while((mt.current_state != mt.accept) && (mt.head < strlen(mt.input))){

		for (i=0;i<mt.nbr_transition;i++){			
			err = 0;
            //printf("\n\n test%d: %c, %c, %c, %c, %d\n",i,mt.current_state, mt.read_state[i], mt.input[mt.head], mt.read_letter[i], mt.steps);
			if((mt.current_state == mt.read_state[i]) && (mt.input[mt.head] == mt.read_letter[i])){
				if (mt.input[strlen(mt.input)-1] != '_'){
					mt.input = strcat(mt.input,"_");
				}
				affichage_mt_01(mt);
				mt.current_state = mt.write_state[i];
				mt.input[mt.head] = mt.write_letter[i];
				mt.steps++;
                
				if(mt.shift[i] == '<'){
					mt.head--;
				}
				else if(mt.shift[i] == '>'){ mt.head++; }
				i = 0;
				
			}
			else{err++;}
			
			if (err == mt.nbr_transition){
				printf("Erreur, il n'existe pas de transition sur %c en l'état %c",mt.input[mt.head],mt.read_state[0]);
				exit(1);
			}
		}
		lim++;

		if(lim > 100){
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

    if(Ki != NULL){
        //On applique le copy de i par dessus j
        Ki; Kj;
        int witness = i;

        for (i=0;i<size_Ki;i++){
            if((67+i)==70){ mt.current_state = 67 +i+1;mt.head+=1;
            }else if(i == (size_Ki -1)){ mt.current_state =70; 
            }else{ mt.current_state = 67+i;}
            
            //printf("\nL'arg de i:%s\n",argv[Ki]);
            mt.input[witness-i+1] = argv[Ki][size_Ki-i-1];        

            affichage_mt_01(mt); 
            mt.steps++;
            mt.head-=1;      
        }
        printf("\nInput accepted\n\n"); 

        free(mt.read_state);
        free(mt.read_letter);
        free(mt.write_state);
        free(mt.write_letter);
        free(mt.shift);
    }

	return 0;	
}